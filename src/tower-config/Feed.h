//
//  Feed.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/9/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Feed_h
#define Distillation_Advisor_Feed_h

#include "stdafx.h"

#include "IFeed.h"

namespace dacore {

	class Feed : public IFeed {

	public:
		Feed(FeedId id = 0):mID(id){

			mFactor = Validate::INVALID_DBL;

			Validate::registerStrPattern(IFeed_name, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(IFeed_instrumentTag, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(IFeed_engUnit, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerNumPattern(IFeed_factor, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
		}
		virtual ~Feed(){}

		//IFeed:
		const char* IFeed_name = "Feed.name";
		virtual std::string     getName(){ return mName; }
		virtual void            setName(const std::string& name){
			Validate::validate(IFeed_name, name);
			mName = name;
		}

		const char* IFeed_instrumentTag = "Feed.instrumentTag";
		virtual std::string     getInstrumentTag(){ return mInstTag; }
		virtual void            setInstrumentTag(const std::string& tag){
			Validate::validate(IFeed_instrumentTag, tag);
			mInstTag = tag;
		}

		const char* IFeed_engUnit = "Feed.engUnit";
		virtual std::string     getEngUnit(){ return mEngUnit; }       //TODO enum class
		virtual void            setEngUnit(const std::string& val){
			Validate::validate(IFeed_engUnit, val);
			mEngUnit = val;
		}

		const char* IFeed_factor = "Feed.factor";
		virtual double          getFactor(){ return mFactor; }
		virtual void            setFactor(double val){
			Validate::validate(IFeed_factor, val);
			mFactor = val;
		}

		virtual FeedId   getId(){ return mID; }

		virtual IFeed::Type getType(){ return mType; }
		virtual void setType(IFeed::Type type){ mType = type; }

	private:
		Type			mType;
		FeedId			mID;
		std::string     mName;
		std::string     mInstTag;
		std::string     mEngUnit;
		double          mFactor;

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			pt.put("Feed.id", mID);
			pt.put(IFeed_name, mName);
			pt.put(IFeed_instrumentTag, mInstTag);
			pt.put(IFeed_engUnit, mEngUnit);
			pt.put(IFeed_factor, mFactor);
			pt.put("Feed.type", mType);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			mID = pt.get<unsigned long>("Feed.id");
			mName = pt.get<std::string>(IFeed_name);
			mInstTag = pt.get<std::string>(IFeed_instrumentTag);
			mEngUnit = pt.get<std::string>(IFeed_engUnit);
			mFactor = pt.get<double>(IFeed_factor);
			mType = (Type)pt.get<int>("Feed.type");
		}
	};

}

#endif
