//
//  IFeed.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IFeed_h
#define Distillation_Advisor_IFeed_h

#include "dacommon.h"

namespace dacore {

	typedef unsigned long FeedId;

	class DACORE_API IFeed : public ISerialize {

	public:
		virtual ~IFeed(){}

		enum Type { DEFAULT, HEATINGMEDIUM };

		virtual IFeed::Type getType() = 0;
		virtual void setType(IFeed::Type type) = 0;

		virtual std::string     getName() = 0;
		virtual void            setName(const std::string& name) = 0;

		virtual std::string     getInstrumentTag() = 0;
		virtual void            setInstrumentTag(const std::string& tag) = 0;

		virtual std::string     getEngUnit() = 0;       //TODO enum 
		virtual void            setEngUnit(const std::string& val) = 0;

		virtual double          getFactor() = 0;
		virtual void            setFactor(double val) = 0;

		virtual FeedId			getId() = 0;

	};

}

#endif
