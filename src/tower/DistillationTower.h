//
//  DistillationTower.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 6/30/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef __Distillation_Advisor__DistillationTower__
#define __Distillation_Advisor__DistillationTower__

#include "stdafx.h"

#include "ITower.h"

#include "ITowerData.h"
#include "ITowerConfig.h"
#include "ITowerReport.h"

namespace dacore {

	class DistillationTower : public ITower {

		friend class TowerFactory;

		DistillationTower(TowerId id = 0):mID(id){
			Validate::registerStrPattern(ITower_name, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
		}

	public:
		virtual ~DistillationTower(){ delete mTowerData; delete mTowerConfig; delete mTowerReport; }

		const char* ITower_name = "Tower.name";
		virtual std::string     getName(){ return mName; }
		virtual void            setName(const std::string& name){
			Validate::validate(ITower_name, name); mName = name;
		}

		const char* ITower_data = "Tower.Data";
		virtual ITowerData*     getData(){ return mTowerData; }
		virtual void            setData(ITowerData* data){ mTowerData = data; }

		const char* ITower_config = "Tower.Config";
		virtual ITowerConfig*   getConfig(){ return mTowerConfig; }
		virtual void            setConfig(ITowerConfig* config){ mTowerConfig = config; }

		const char* ITower_report = "Tower.Report";
		virtual ITowerReport*   getReport(){ return mTowerReport; }
		virtual void            setReport(ITowerReport* report){ mTowerReport = report; }

		virtual TowerId   getId(){ return mID; }

		virtual ITower::Type getType(){ return mType; }
		virtual void setType(ITower::Type type){ mType = type; }

		static const char* typeStr(Type m){
			switch (m){
			case DISTILLATION:
				return "DISTILLATION";
//			case AMINE_ABSORBER:
//				return "AMINE_ABSORBER";
#ifdef UNIT_TESTING
			case DTPRIME:
				return "DTPRIME";
#endif
			default:
				return "...";
			}
		}

	private:
		virtual void    setId(unsigned long id){ mID = id; }

	protected:
		ITower::Type	mType;
		TowerId			mID;
		std::string     mName;
		ITowerData*     mTowerData;
		ITowerConfig*   mTowerConfig;
		ITowerReport*   mTowerReport;

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			ISerialize::serializeObj(pt, ITower_data, mTowerData);
			ISerialize::serializeObj(pt, ITower_config, mTowerConfig);
			ISerialize::serializeObj(pt, ITower_report, mTowerReport);
			pt.put(ITower_name, mName);
			pt.put("Tower.id", mID);
			pt.put("Tower.type", mType);

		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			ISerialize::deserializeObj(pt, ITower_data, mTowerData);
			ISerialize::deserializeObj(pt, ITower_config, mTowerConfig);
			ISerialize::deserializeObj(pt, ITower_report, mTowerReport);
			mName = pt.get<std::string>(ITower_name);
			mID = pt.get<TowerId>("Tower.id");
			mType = (ITower::Type)pt.get<int>("Tower.type");
		}

	};

}

#endif /* defined(__Distillation_Advisor__DistillationTower__) */
