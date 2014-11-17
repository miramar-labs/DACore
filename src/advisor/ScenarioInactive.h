//
//  ScenarioInactive.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef __Distillation_Advisor__ScenarioInactive__
#define __Distillation_Advisor__ScenarioInactive__

#include "stdafx.h"

#include "IAlgorithm.h"
#include "ITowerConfig.h"

namespace dacore {

	class ScenarioInactive : public IAlgorithm {

	public:
		static const std::string mID;

		virtual ~ScenarioInactive(){}

	protected:
		virtual bool doAlgorithm(ITower* tower, IAdvice* advice){
			if (tower->getConfig()->isInactive()) {
				advice->setAlgorithmId(mID);
				advice->setSeverity(IAdvice::Severity::YELLOW);
				advice->setPrimaryMessage("The tower is not active.");
				return false;
			}
			return true;
		}

	};

}

#endif /* defined(__Distillation_Advisor__ScenarioInactive__) */
