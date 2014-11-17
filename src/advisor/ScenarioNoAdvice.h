//
//  ScenarioNoAdvice.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_ScenarioNoAdvice_h
#define Distillation_Advisor_ScenarioNoAdvice_h

#include "stdafx.h"

#include "IAlgorithm.h"

namespace dacore {

	class ScenarioNoAdvice : public IAlgorithm {

	public:
		static const std::string mID;

		virtual ~ScenarioNoAdvice(){}

	protected:
		virtual bool doAlgorithm(ITower* tower, IAdvice* advice){
			advice->setAlgorithmId(mID);
			advice->setSeverity(IAdvice::Severity::GREEN);
			advice->setPrimaryMessage("No advice at this time.");
			return false;
		}

	};

}

#endif
