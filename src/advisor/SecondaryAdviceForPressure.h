//
//  SecondaryAdviceForPressure.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef __Distillation_Advisor__SecondaryAdviceForPressure__
#define __Distillation_Advisor__SecondaryAdviceForPressure__

#include "stdafx.h"

#include "IAlgorithm.h"

namespace dacore {

	class SecondaryAdviceForPressure : public IAlgorithm {

	public:
		static const std::string mID;

		virtual ~SecondaryAdviceForPressure(){}

	protected:
		virtual bool doAlgorithm(ITower* tower, IAdvice* advice){ return true; }

	};

}

#endif /* defined(__Distillation_Advisor__SecondaryAdviceForPressure__) */
