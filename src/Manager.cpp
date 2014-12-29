//
//  Manager.cpp
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/26/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#include "stdafx.h"

#include "Manager.h"

#include "TowerFactory.h"
#include "HistorianFactory.h"
#include "Advisor.h"

#include "ITower.h"
#include "ITowerConfig.h"

extern "C" DACORE_API const char* DACORE_APIENTRY TowerTypeStr(dacore::ITower::Type t) { return dacore::DistillationTower::typeStr(t); }
extern "C" DACORE_API const char* DACORE_APIENTRY HistorianTypeStr(dacore::IHistorian::Type t){ return dacore::HistorianBase::typeStr(t); }

namespace dacore{

	static std::map<TowerId, ITower*>          mTowers;
	static std::map<HistorianId, IHistorian*>  mHistorians;

	static Manager gManager;		//TODO - singleton class and smart pointers etc...

	extern "C" DACORE_API dacore::IManager* DACORE_APIENTRY getManager(){
		return &gManager;
	}

	//TODO: exception handling, template paramaterization

	static const char *TOWER_DATA_DIR = ".\\data\\towers\\";
	static const char *HISTORIAN_DATA_DIR = ".\\data\\historians\\";

	const std::string Manager::towerFilename(ITower* tower){
		std::ostringstream sstrm;
		sstrm << TOWER_DATA_DIR << "tower-" << std::to_string(tower->getId()) << ".json";
		return sstrm.str();
	}

	const std::string Manager::historianFilename(IHistorian* historian){
		std::ostringstream sstrm;
		sstrm << HISTORIAN_DATA_DIR << "historian-" << std::to_string(historian->getId()) << ".json";
		return sstrm.str();
	}

	static void removeTowerFile(TowerId tid);

	static void removeHistorianFile(HistorianId hid);

	Manager::~Manager(){

		for (std::map<TowerId, ITower*>::iterator it = mTowers.begin(); it != mTowers.end(); ++it){
			ITower* tower = (*it).second;
			delete tower;
		}
		mTowers.empty();

		for (std::map<HistorianId, IHistorian*>::iterator it = mHistorians.begin(); it != mHistorians.end(); ++it){
			IHistorian* historian = (*it).second;
			delete historian;
		}
		mHistorians.empty();

	}

	IAdvice* Manager::getAdvice(TowerId id){
		IAdvice* advice = nullptr;
		ITower* tower = getTower(id);
		if (tower){
			Advisor engine;
			advice = engine.getAdvice(tower);
		}
		return advice;
	}

	//========================================================================================================================

	void Manager::loadTowers(){
		boost::filesystem::path dataDir(TOWER_DATA_DIR);
		boost::filesystem::directory_iterator end_iter;
		if (boost::filesystem::exists(TOWER_DATA_DIR) && boost::filesystem::is_directory(TOWER_DATA_DIR))
		{
			for (boost::filesystem::directory_iterator dir_iter(dataDir); dir_iter != end_iter; ++dir_iter)
			{
				if (boost::filesystem::is_regular_file(dir_iter->status()))
				{
					boost::property_tree::ptree pt;
					std::string fname = dir_iter->path().string();
					const std::string prefix = std::string(TOWER_DATA_DIR) + "tower-";
					const std::string postfix = ".json";
					if (boost::starts_with(fname, prefix) &&
						boost::ends_with(fname, postfix)){
						read_json(fname, pt);
						ITower* tower = TowerFactory::create();
						tower->deserialize(pt);

						std::map<TowerId, ITower*>::iterator it = mTowers.find(tower->getId());
						if (it == mTowers.end())
							mTowers.insert(std::pair<TowerId, ITower*>(tower->getId(), tower));
						else{
							delete (*it).second;
							mTowers[tower->getId()] = tower;
						}
					}
				}
			}
		}
	}

	void Manager::saveTowers(){
		for (std::map<TowerId, ITower*>::iterator it = mTowers.begin(); it != mTowers.end(); ++it)
			saveTower((*it).first);
	}

	bool Manager::saveTower(TowerId id){
		std::cout << boost::filesystem::current_path() << std::endl;
		ITower* tower = getTower(id);
		if (tower){
			boost::property_tree::ptree pt;
			tower->serialize(pt);
			if (!(boost::filesystem::exists(TOWER_DATA_DIR) && boost::filesystem::is_directory(TOWER_DATA_DIR))){
				if (!boost::filesystem::create_directory(TOWER_DATA_DIR))
					return false;
			}
			write_json(towerFilename(tower), pt, std::locale(), false);
		}
		return true;
	}

	ITower* Manager::getTower(TowerId id){
		if (mTowers.find(id) == mTowers.end())
			return NULL;
		else{
			std::map<TowerId, ITower*>::iterator it = mTowers.find(id);
			return (*it).second;
		}
	}

	void Manager::enumerateTowers(std::vector<TowerId>& tids){
		tids.clear();
		for (std::map<TowerId, ITower*>::iterator it = mTowers.begin(); it != mTowers.end(); ++it)
			tids.push_back((*it).first);
	}

	TowerId Manager::createTower(HistorianId hid, ITower::Type type){
		ITower* tower = TowerFactory::create(type);
		std::vector<TowerId> tids;
		enumerateTowers(tids);
		TowerId maxid = 0;
		for (std::vector<TowerId>::iterator it = tids.begin(); it != tids.end(); ++it){
			if (*it > maxid)
				maxid = *it;
		}
		tower->setId(maxid + 1);
		mTowers.insert(std::pair<int, ITower*>(tower->getId(), tower));

		IHistorian* ph = getHistorian(hid);
		ITowers* pt = ph->getTowers();
		pt->add(tower->getId());

		saveTower(tower->getId());	// save changes to fs
		saveHistorian(hid);			// save changes to fs

		return tower->getId();
	}

	//NOTES: deleting a tower should fail if it is referenced by a historian
	bool Manager::deleteTower(HistorianId hid, TowerId tid){
		std::map<TowerId, ITower*>::iterator tit = mTowers.find(tid);
		if (tit == mTowers.end())
			return false;
		//check for refs in the historians...
		for (std::map<HistorianId, IHistorian*>::iterator it = mHistorians.begin(); it != mHistorians.end(); ++it){
			IHistorian* historian = (*it).second;
			if (historian){
				ITowers* towers = historian->getTowers();
				std::vector<TowerId> tids;
				towers->enumerate(tids);

				for (std::vector<TowerId>::iterator it = tids.begin(); it != tids.end(); ++it){
					if (*it == tid)
						return false;   // found a ref .. bail...
				}
			}
		}
		// no refs found, so safe to delete
		delete (*tit).second;
		mTowers.erase(tit);

		saveHistorian(hid);			// save changes to fs
		removeTowerFile(tid);		// save changes to fs

		return true;
	}

	static void removeTowerFile(TowerId tid){
		const std::string prefix = std::string(TOWER_DATA_DIR) + "tower-";
		const std::string sID = boost::lexical_cast<std::string>(tid);
		const std::string postfix = ".json";

		boost::filesystem::path towerFile(prefix+sID+postfix);
		if (boost::filesystem::exists(towerFile)){
			boost::filesystem::remove(towerFile);
		}
	}

	//========================================================================================================================

	void Manager::loadHistorians(){
		boost::filesystem::path dataDir(HISTORIAN_DATA_DIR);
		boost::filesystem::directory_iterator end_iter;
		if (boost::filesystem::exists(HISTORIAN_DATA_DIR) && boost::filesystem::is_directory(HISTORIAN_DATA_DIR))
		{
			for (boost::filesystem::directory_iterator dir_iter(dataDir); dir_iter != end_iter; ++dir_iter)
			{
				if (boost::filesystem::is_regular_file(dir_iter->status()))
				{
					boost::property_tree::ptree pt;
					std::string fname = dir_iter->path().string();
					const std::string prefix = std::string(HISTORIAN_DATA_DIR) + "historian-";
					const std::string postfix = ".json";
					if (boost::starts_with(fname, prefix) &&
						boost::ends_with(fname, postfix)){
						read_json(fname, pt);
						IHistorian* historian = HistorianFactory::create();
						historian->deserialize(pt);
						std::map<HistorianId, IHistorian*>::iterator it = mHistorians.find(historian->getId());
						if (it == mHistorians.end())
							mHistorians.insert(std::pair<HistorianId, IHistorian*>(historian->getId(), historian));
						else{
							delete (*it).second;
							mHistorians[historian->getId()] = historian;
						}
					}
				}
			}
		}
	}

	void Manager::saveHistorians(){
		for (std::map<HistorianId, IHistorian*>::iterator it = mHistorians.begin(); it != mHistorians.end(); ++it)
			saveHistorian((*it).first);
	}

	bool Manager::saveHistorian(HistorianId id){
		std::cout << boost::filesystem::current_path() << std::endl;
		if (mHistorians.find(id) == mHistorians.end())
			return false;
		std::map<HistorianId, IHistorian*>::iterator it = mHistorians.find(id);
		boost::property_tree::ptree pt;
		IHistorian* historian = (*it).second;
		historian->serialize(pt);
		if (!(boost::filesystem::exists(HISTORIAN_DATA_DIR) && boost::filesystem::is_directory(HISTORIAN_DATA_DIR))){
			if (!boost::filesystem::create_directory(HISTORIAN_DATA_DIR))
				return false;
		}
		write_json(historianFilename(historian), pt, std::locale(), false);
		return true;
	}

	IHistorian* Manager::getHistorian(HistorianId id){
		if (mHistorians.find(id) == mHistorians.end())
			return NULL;
		else{
			std::map<HistorianId, IHistorian*>::iterator it = mHistorians.find(id);
			return (*it).second;
		}
	}

	void Manager::enumerateHistorians(std::vector<HistorianId>& hids){
		hids.clear();
		for (std::map<HistorianId, IHistorian*>::iterator it = mHistorians.begin(); it != mHistorians.end(); ++it)
			hids.push_back((*it).first);
	}

	IHistorian* Manager::getHistorianOfTower(TowerId id){
		if (mTowers.find(id) == mTowers.end()){
			return NULL;
		}
		else{
			for (std::map<HistorianId, IHistorian*>::iterator it = mHistorians.begin(); it != mHistorians.end(); ++it){
				IHistorian* h = getHistorian((*it).first);
				ITowers* towers = h->getTowers();
				std::vector<TowerId> sub;
				towers->enumerate(sub);
				for (std::vector<TowerId>::iterator it2 = sub.begin(); it2 != sub.end(); ++it2){
					if (*it2 == id)
						return h;
				}
			}
			return nullptr;
		}
	}

	HistorianId Manager::createHistorian(IHistorian::Type type){
		IHistorian* historian = HistorianFactory::create(type);
		std::vector<HistorianId> hids;
		enumerateHistorians(hids);
		HistorianId maxid = 0;
		for (std::vector<HistorianId>::iterator it = hids.begin(); it != hids.end(); ++it){
			if (*it > maxid)
				maxid = *it;
		}
		historian->setId(maxid + 1);
		mHistorians.insert(std::pair<int, IHistorian*>(historian->getId(), historian));

		saveHistorian(historian->getId());			// save changes to fs

		return historian->getId();
	}

	bool Manager::deleteHistorian(HistorianId hid){
		std::map<HistorianId, IHistorian*>::iterator it = mHistorians.find(hid);
		if (it == mHistorians.end())
			return false;
		IHistorian* ph = (*it).second;
		ITowers* pt = ph->getTowers();
		if (pt->count() > 0)
			return false;
		delete (*it).second;
		mHistorians.erase(hid);		

		removeHistorianFile(hid);		// save changes to fs
		
		return true;
	}

	bool Manager::removeTowerFromHistorian(HistorianId hid, TowerId tid)  
	{
		IHistorian* h = getHistorianOfTower(tid);
		if (h != nullptr){
			h->getTowers()->remove(tid);

			saveHistorian(hid);			// save changes to fs

			return true;
		}
		return false;
	}

	bool Manager::addTowerToHistorian(HistorianId hid, TowerId tid) 
	{
		// this should fail if the tower is already referenced by another historian (1-1 rule)
		IHistorian* h = getHistorianOfTower(tid);
		if (h == nullptr){
			h = getHistorian(hid);
			if (h == nullptr)
				return false; // no such historian
			h->getTowers()->add(tid);

			saveHistorian(hid);			// save changes to fs

			return true;
		}
		// already in use...
		return false;
	}

	static void removeHistorianFile(HistorianId hid){
		const std::string prefix = std::string(HISTORIAN_DATA_DIR) + "historian-";
		const std::string sID = boost::lexical_cast<std::string>(hid);
		const std::string postfix = ".json";

		boost::filesystem::path historianFile(prefix + sID + postfix);
		if (boost::filesystem::exists(historianFile)){
			boost::filesystem::remove(historianFile);
		}
	}

}// namespace