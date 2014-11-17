//
//  AdvisorFactory.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/20/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_AdvisorFactory_h
#define Distillation_Advisor_AdvisorFactory_h

#include "stdafx.h"

#include "Override.h"

namespace dacore {

	class AdvisorFactory {

	public:

		static IOverride* create(OverrideId id = 0){
			return new Override(id);
		}
	};

}
#endif
