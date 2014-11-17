//
//  Towers.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/31/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Towers_h
#define Distillation_Advisor_Towers_h

#include "stdafx.h"

#include "ITower.h"
#include "ITowers.h"

#include "Manager.h"

namespace dacore {

extern Manager gManager;

	class Towers : public ITowers {

	public:
		virtual ~Towers(){
			mTowers.clear();
		}

		virtual TowerId count(){
			return mTowers.size();
		}

		virtual ITower* get(TowerId id){
			return gManager.getTower(id);
		}

		virtual void enumerate(std::vector<TowerId>& towers){
			towers.clear();
			for (std::set<TowerId>::iterator it = mTowers.begin(); it != mTowers.end(); ++it)
				towers.push_back(*it);
		}

	private:
		virtual TowerId add(TowerId tid){
			mTowers.insert(tid);
			return tid;
		}

		virtual void remove(TowerId tid){
			mTowers.erase(tid);			
		}

		//ISerialize:
	public:
		virtual void serialize(boost::property_tree::ptree& pt){
			std::ostringstream sstrm;
			for (std::set<TowerId>::iterator it = mTowers.begin(); it != mTowers.end(); ++it){
				sstrm << std::to_string(*it) << " ";
			}
			pt.put("Towers.list", sstrm.str());
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			std::string ids = pt.get<std::string>("Towers.list");
			boost::tokenizer<> tok(ids);
			for (boost::tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg)
				mTowers.insert(boost::lexical_cast<TowerId>(*beg));
		}

	private:
		std::set<TowerId>    mTowers;
	};

}

#endif
