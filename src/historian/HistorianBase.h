//
//  HistorianBase.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/26/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_HistorianBase_h
#define Distillation_Advisor_HistorianBase_h

#include "stdafx.h"

#include "IHistorian.h"
#include "ITowers.h"

namespace dacore {

	class HistorianBase : public IHistorian {

	public:
		virtual ~HistorianBase(){}	//TODO cleanup

		//IHistorian:
		virtual IHistorian::Type getType(){ return mType; }
		virtual void setType(IHistorian::Type type){ mType = type; }

		virtual std::string getServer(){ return mServer; }
		virtual void setServer(const std::string& server){ mServer = server; }

		virtual ITowers* getTowers(){ return mTowers; }
		virtual void setTowers(ITowers* towers){ mTowers = towers; }

		//TODO virtual std::string getDataSource() = 0;

		//TODO	HistorianQueryResult query(HistorianQuery query) throws HistorianException;

		virtual unsigned long   getId(){ return mID; }

		static const char* typeStr(Type m){//FILE_DEMO, PI, IP21
			switch (m){
			case FILE_DEMO:
				return "FILE_DEMO";
			case PI:
				return "PI";
			case IP21:
				return "IP21";
			default:
				return "...";
			}
		}

	private:
		virtual void            setId(unsigned long id){ mID = id; }

	private:
		HistorianId			mID;
		IHistorian::Type	mType;
		std::string			mServer;
		ITowers*			mTowers;
		//TODO std::string     mDataSource;

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			pt.put("Historian.id", mID);
			pt.put("Historian.type", mType);
			pt.put("Historian.server", mServer);
			ISerialize::serializeObj(pt, "Historian.towers", mTowers);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			mID = pt.get<HistorianId>("Historian.id");
			mServer = pt.get<std::string>("Historian.server");
			mType = (IHistorian::Type)pt.get<int>("Historian.type");
			ISerialize::deserializeObj(pt, "Historian.towers", mTowers);
		}
	};

}

#endif
