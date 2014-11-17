//
//  IOverrides.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/11/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IAdviceOverrides_h
#define Distillation_Advisor_IAdviceOverrides_h

#include "IOverride.h"

//TODO: check this .. assumes 1 override per prevent target

namespace dacore {

	class IOverrides : public ISerialize {

	public:
		virtual ~IOverrides(){}

		virtual OverrideId count() = 0;

		virtual IOverride* get(OverrideId id) = 0;

		virtual void enumerate(std::vector<OverrideId>& ovr) = 0;

		virtual OverrideId add() = 0;

		virtual void remove(OverrideId id) = 0;

	//helpers:
		virtual bool willTripFor(IOverride::PreventTarget target, double value) = 0;

		virtual IOverride* find(IOverride::PreventTarget target) = 0;	
	};

}

#endif
