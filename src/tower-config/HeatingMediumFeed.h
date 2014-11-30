//
//  HeatingMediumFeed.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 8/16/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_HeatingMediumFeed_h
#define Distillation_Advisor_HeatingMediumFeed_h

#include "stdafx.h"

#include "IHeatingMediumFeed.h"

namespace dacore {

	class HeatingMediumFeed : public IHeatingMediumFeed {

	public:
		HeatingMediumFeed(FeedId id = 0) :mID(id){

			mFactor = Validate::INVALID_DBL;
			mBtuPerUnit = Validate::INVALID_DBL;

			Validate::registerStrPattern(IHeatingMediumFeed_name, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(IHeatingMediumFeed_instrumentTag, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(IHeatingMediumFeed_engUnit, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerNumPattern(IHeatingMediumFeed_factor, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
			Validate::registerNumPattern(IHeatingMediumFeed_btuPerUnit, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
		}

		virtual ~HeatingMediumFeed(){}

		//IFeed:
		const char* IHeatingMediumFeed_name = "HeatingMediumFeed.name";
		virtual std::string     getName(){ return mName; }
		virtual void            setName(const std::string& name){
			Validate::validate(IHeatingMediumFeed_name, name);
			mName = name;
		}

		const char* IHeatingMediumFeed_instrumentTag = "HeatingMediumFeed.instrumentTag";
		virtual std::string     getInstrumentTag(){ return mInstTag; }
		virtual void            setInstrumentTag(const std::string& tag){
			Validate::validate(IHeatingMediumFeed_instrumentTag, tag);
			mInstTag = tag;
		}

		const char* IHeatingMediumFeed_engUnit = "HeatingMediumFeed.engUnit";
		virtual std::string     getEngUnit(){ return mEngUnit; }       //TODO enum class
		virtual void            setEngUnit(const std::string& val){
			Validate::validate(IHeatingMediumFeed_engUnit, val);
			mEngUnit = val;
		}

		const char* IHeatingMediumFeed_factor = "HeatingMediumFeed.factor";
		virtual double          getFactor(){ return mFactor; }
		virtual void            setFactor(double val){
			Validate::validate(IHeatingMediumFeed_factor, val);
			mFactor = val;
		}

		//IHeatingMediumFeed:
		const char* IHeatingMediumFeed_btuPerUnit = "HeatingMediumFeed.btuPerUnit";
		virtual double   getBtuPerUnit(){ return mBtuPerUnit; }
		virtual void     setBtuPerUnit(double val){
			Validate::validate(IHeatingMediumFeed_btuPerUnit, val);
			mBtuPerUnit = val;
		}

		virtual FeedId   getId(){ return mID; }

		virtual IFeed::Type getType(){ return mType; }
		virtual void setType(IFeed::Type type){ mType = type; }

	protected:
		Type			mType;
		FeedId			mID;
		std::string     mName;
		std::string     mInstTag;
		std::string     mEngUnit;
		double          mFactor;
		double          mBtuPerUnit;

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			pt.put("HeatingMediumFeed.id", mID);
			pt.put(IHeatingMediumFeed_name, mName);
			pt.put(IHeatingMediumFeed_instrumentTag, mInstTag);
			pt.put(IHeatingMediumFeed_engUnit, mEngUnit);
			pt.put(IHeatingMediumFeed_factor, mFactor);
			pt.put(IHeatingMediumFeed_btuPerUnit, mBtuPerUnit);
			pt.put("Feed.type", mType);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			mID = pt.get<FeedId>("HeatingMediumFeed.id");
			mName = pt.get<std::string>(IHeatingMediumFeed_name);
			mInstTag = pt.get<std::string>(IHeatingMediumFeed_instrumentTag);
			mEngUnit = pt.get<std::string>(IHeatingMediumFeed_engUnit);
			mFactor = pt.get<double>(IHeatingMediumFeed_factor);
			mBtuPerUnit = pt.get<double>(IHeatingMediumFeed_btuPerUnit);
			mType = (Type)pt.get<int>("Feed.type");
		}
	};

}

#endif
