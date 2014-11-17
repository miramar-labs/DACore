//
//  IOverridesData.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/11/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IOverridesData_h
#define Distillation_Advisor_IOverridesData_h

#include "dacommon.h"

namespace dacore {

	class DACORE_API IOverridesData : public ISerialize {

	public:
		virtual ~IOverridesData(){}

		virtual double getPreventsDecreaseInReboil() = 0;
		virtual void setPreventsDecreaseInReboil(double val) = 0;

		virtual double getPreventsIncreaseInReboil() = 0;
		virtual void setPreventsIncreaseInReboil(double val) = 0;

		virtual double getPreventsDecreaseInReflux() = 0;
		virtual void setPreventsDecreaseInReflux(double val) = 0;

		virtual double getPreventsIncreaseInReflux() = 0;
		virtual void setPreventsIncreaseInReflux(double val) = 0;

		virtual double getPreventsPressureDecrease() = 0;
		virtual void setPreventsPressureDecrease(double val) = 0;

		virtual double getPreventsPressureIncrease() = 0;
		virtual void setPreventsPressureIncrease(double val) = 0;
	};

}

#endif

