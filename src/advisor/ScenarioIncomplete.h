//
//  ScenarioIncomplete.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef __Distillation_Advisor__ScenarioIncomplete__
#define __Distillation_Advisor__ScenarioIncomplete__

#include "stdafx.h"

#include "IAlgorithm.h"
#include "ITowerConfig.h"

namespace dacore {

	class ScenarioIncomplete : public IAlgorithm {

	public:
		static const std::string mID;

		virtual ~ScenarioIncomplete(){}

	protected:
		virtual bool doAlgorithm(ITower* tower, IAdvice* advice){
			if (tower->getConfig()->isIncomplete()) {
				advice->setAlgorithmId(mID);
				advice->setSeverity(IAdvice::Severity::YELLOW);
				advice->setPrimaryMessage("The tower has an incomplete configuration.");
				return false;
			}
			return true;
		}

	};

}
#endif /* defined(__Distillation_Advisor__ScenarioIncomplete__) */
