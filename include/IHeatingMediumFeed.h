//
//  IHeatingMediumFeed.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 8/16/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IHeatingMediumFeed_h
#define Distillation_Advisor_IHeatingMediumFeed_h

#include "dacommon.h"
#include "IFeed.h"

namespace dacore {

	class DACORE_API IHeatingMediumFeed : public IFeed {

	public:
		virtual ~IHeatingMediumFeed(){}

		virtual double   getBtuPerUnit() = 0;
		virtual void     setBtuPerUnit(double val) = 0;

	};

}

#endif
