//
//  ILabResultsData.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 8/9/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_ILabResultsData_h
#define Distillation_Advisor_ILabResultsData_h

#include "dacommon.h"

namespace dacore {

	class DACORE_API ILabResultsData : public ISerialize {		//TODO: CHECKME - do we really need to serialize this?

	public:
		virtual ~ILabResultsData(){}

		virtual double getHeavyKeyLabResult() = 0;
		virtual void setHeavyKeyLabResult(double val) = 0;

		virtual double getLightKeyLabResult() = 0;
		virtual void setLightKeyLabResult(double val) = 0;

		virtual std::string getTimeStamp() = 0; 

	};

}

#endif
