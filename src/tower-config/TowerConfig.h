//
//  TowerConfig.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/9/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_TowerConfig_h
#define Distillation_Advisor_TowerConfig_h

#include "stdafx.h"

#include "ITowerConfig.h"
#include "IBottoms.h"
#include "IOverhead.h"
#include "IFeeds.h"
#include "IColumn.h"
#include "IOverrides.h"
#include "IControlLimits.h"

namespace dacore {

	class IFeed;

	class TowerConfig : public ITowerConfig {

	public:
		TowerConfig(){
			Validate::registerStrPattern(ITowerConfig_name, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
		}

		virtual ~TowerConfig(){ delete mBottoms; delete mOverhead; delete mColumn; delete mOverrides; }

		const char* ITowerConfig_bottoms = "TowerConfig.Bottoms";
		virtual IBottoms* getBottoms(){ return mBottoms; }
		
		const char* ITowerConfig_overhead = "TowerConfig.Overhead";
		virtual IOverhead* getOverhead(){ return mOverhead; }
		
		const char* ITowerConfig_type = "TowerConfig.type";
		virtual ITower::Type getType(){ return mType; }
		
		const char* ITowerConfig_feeds = "TowerConfig.Feeds";
		virtual IFeeds* getFeeds(){ return mBottoms->getHeatingMediumFeeds(); }
		
		const char* ITowerConfig_column = "TowerConfig.Column";
		virtual IColumn* getColumn(){ return mColumn; }
		
		//const char* ITowerConfig_isIncomplete = "TowerConfig.isIncomplete";
		virtual bool isIncomplete(){ 
			//TODO - implementation ... recursively scan all config props for INVALID_ values... return true if any found
			return false; 
		}

		const char* ITowerConfig_isInactive = "TowerConfig.isInactive";
		virtual bool isInactive(){ return mInactive; }
		virtual void setIsInactive(bool val){
			Notify::notify(ITowerConfig_isInactive);
			mInactive = val;
		}

		const char* ITowerConfig_isMaximizingFeed = "TowerConfig.isMaximizingFeed";
		virtual bool isMaximizingFeed(){ return mIsMaximizingFeed; }
		virtual void setIsMaximizingFeed(bool val){
			Notify::notify(ITowerConfig_isMaximizingFeed);
			mIsMaximizingFeed = val;
		}

		const char* ITowerConfig_overrides = "TowerConfig.Overrides";
		virtual IOverrides* getOverrides(){ return mOverrides; }
		
		const char* ITowerConfig_name = "TowerConfig.name";
		virtual std::string getName(){ return mName; }
		virtual bool setName(const std::string& val){
			try{
				Validate::validate(ITowerConfig_name, val);
				mName = val;
				return true;
			}
			catch (std::exception& e){
				//TODO: logging and mechachanism to pass info across DLL boundary...
				return false;
			}
		}

		const char* ITowerConfig_controlLimits = "TowerConfig.ControlLimits";
		virtual IControlLimits* getControlLimits(){ return mControlLimits; }
		
		//extended config:
		virtual bool hasAbsoluteControlOfOH() { return false; }
		virtual bool hasAbsoluteControlOfBase() { return false; }
		virtual bool isBaseControlledAt10to90Percent() { return true; }

	private:
		virtual void setOverrides(IOverrides* overrides){ mOverrides = overrides; }
		virtual void setColumn(IColumn* column){ mColumn = column; }
		virtual void setFeeds(IFeeds* feeds){ mBottoms->setHeatingMediumFeeds(feeds); }
		virtual void setType(const ITower::Type& type){ mType = type; }
		virtual void setOverhead(IOverhead* overhead){ mOverhead = overhead; }
		virtual void setBottoms(IBottoms* bottoms){ mBottoms = bottoms; }
		virtual void setControlLimits(IControlLimits* limits){ mControlLimits = limits; }

	protected:
		ITower::Type   mType;
		std::string mName;
		//bool        mIncomplete;
		bool        mInactive;
		bool        mIsMaximizingFeed;
		IBottoms*   mBottoms;
		IOverhead*  mOverhead;
		//IFeeds*     mFeeds;
		IColumn*    mColumn;
		IOverrides* mOverrides;
		IControlLimits* mControlLimits;

	public://TODO: protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){

			ISerialize::serializeObj(pt, ITowerConfig_bottoms, mBottoms);
			ISerialize::serializeObj(pt, ITowerConfig_overhead, mOverhead);
			//ISerialize::serializeObj(pt, ITowerConfig_feeds, mFeeds);
			ISerialize::serializeObj(pt, ITowerConfig_column, mColumn);
			ISerialize::serializeObj(pt, ITowerConfig_overrides, mOverrides);
			ISerialize::serializeObj(pt, ITowerConfig_controlLimits, mControlLimits);

			pt.put(ITowerConfig_type, (int)mType);
			//pt.put(ITowerConfig_isIncomplete, mIncomplete);
			pt.put(ITowerConfig_isInactive, mInactive);
			pt.put(ITowerConfig_isMaximizingFeed, mIsMaximizingFeed);
			pt.put(ITowerConfig_name, mName);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){

			ISerialize::deserializeObj(pt, ITowerConfig_bottoms, mBottoms);
			ISerialize::deserializeObj(pt, ITowerConfig_overhead, mOverhead);
			//ISerialize::deserializeObj(pt, ITowerConfig_feeds, mFeeds);
			ISerialize::deserializeObj(pt, ITowerConfig_column, mColumn);
			ISerialize::deserializeObj(pt, ITowerConfig_overrides, mOverrides);
			ISerialize::deserializeObj(pt, ITowerConfig_controlLimits, mControlLimits);

			mType = (ITower::Type)pt.get<int>(ITowerConfig_type);
			//mIncomplete = pt.get<bool>(ITowerConfig_isIncomplete);
			mInactive = pt.get<bool>(ITowerConfig_isInactive);
			mIsMaximizingFeed = pt.get<bool>(ITowerConfig_isMaximizingFeed);
			mName = pt.get<std::string>(ITowerConfig_name);
		}

	};

}

#endif
