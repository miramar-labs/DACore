//
//  Advisor.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 6/30/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef __Distillation_Advisor__Advisor__
#define __Distillation_Advisor__Advisor__

#include "stdafx.h"

#include "ITower.h"
#include "IAdvice.h"
#include "IAlgorithm.h"

namespace dacore {

	class Advisor {

	public:

		Advisor();
		virtual ~Advisor();

		virtual IAdvice*     getAdvice(ITower* tower);

	private:
		std::vector<IAlgorithm*>    mAlgorithms;

	};

}
#endif /* defined(__Distillation_Advisor__Advisor__) */
