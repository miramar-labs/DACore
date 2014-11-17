//
//  ITowerConfig.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 6/30/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_ITowerConfig_h
#define Distillation_Advisor_ITowerConfig_h

#include "dacommon.h"

namespace dacore {

	class IBottoms;
	class IOverhead;
	class IFeed;
	class IFeeds;
	class IColumn;
	class IOverrides;
	class IControlLimits;

	class DACORE_API ITowerConfig : public ISerialize {

	public:
		virtual ~ITowerConfig(){}

		virtual IBottoms* getBottoms() = 0;

		virtual IOverhead* getOverhead() = 0;

		virtual ITower::Type getType() = 0;
		virtual void setType(const ITower::Type& type) = 0;

		virtual IFeeds* getFeeds() = 0;

		virtual IColumn* getColumn() = 0;

		virtual bool isIncomplete() = 0;
		virtual void setIsIncomplete(bool incomplete) = 0;

		virtual bool isInactive() = 0;
		virtual void setIsInactive(bool inactive) = 0;

		virtual bool isMaximizingFeed() = 0;
		virtual void setIsMaximizingFeed(bool isMaximizing) = 0;

		virtual IOverrides* getOverrides() = 0;

		virtual std::string getName() = 0;
		virtual void setName(const std::string& name) = 0;

		virtual IControlLimits* getControlLimits() = 0;

		//extended config:
		virtual bool hasAbsoluteControlOfOH() = 0;
		virtual bool hasAbsoluteControlOfBase() = 0;
		virtual bool isBaseControlledAt10to90Percent() = 0;

	//TODO:private:
		virtual void setBottoms(IBottoms* base) = 0;
		virtual void setOverhead(IOverhead* overhead) = 0;
		virtual void setFeeds(IFeeds* feeds) = 0;
		virtual void setColumn(IColumn* column) = 0;
		virtual void setOverrides(IOverrides* overrides) = 0;
		virtual void setControlLimits(IControlLimits* limits) = 0;
	};

}

#endif
