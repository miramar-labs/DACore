//
//  Advisor.cpp
//  Distillation Advisor
//
//  Created by Aaron Cody on 6/30/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#include "stdafx.h"

#include "Advisor.h"
#include "Advice.h"
#include "ScenarioIncomplete.h"
#include "ScenarioInactive.h"
#include "ScenarioUnstable.h"
#include "SecondaryAdviceForPressure.h"

#include "Scenario1.h"
#include "Scenario2.h"
#include "Scenario3.h"
#include "Scenario4.h"
#include "Scenario5.h"
#include "Scenario6.h"
#include "Scenario7.h"
#include "Scenario8.h"
#include "Scenario9.h"

#include "ScenarioNoAdvice.h"

namespace dacore {

	Advisor::Advisor(){
		mAlgorithms.push_back(new ScenarioIncomplete());
		mAlgorithms.push_back(new ScenarioInactive());
		mAlgorithms.push_back(new ScenarioUnstable());
		mAlgorithms.push_back(new SecondaryAdviceForPressure());
		mAlgorithms.push_back(new Scenario1());
		mAlgorithms.push_back(new Scenario2());
		mAlgorithms.push_back(new Scenario3());
		mAlgorithms.push_back(new Scenario4());
		mAlgorithms.push_back(new Scenario5());
		mAlgorithms.push_back(new Scenario6());
		mAlgorithms.push_back(new Scenario7());
		mAlgorithms.push_back(new Scenario8());
		mAlgorithms.push_back(new Scenario9());
		mAlgorithms.push_back(new ScenarioNoAdvice());
	}

	Advisor::~Advisor(){
		for (unsigned int i = 0; i < mAlgorithms.size(); i++)
			delete mAlgorithms[i];
		mAlgorithms.clear();
	}

	IAdvice*  Advisor::getAdvice(ITower* tower){
		IAdvice* advice = new Advice();
		for (unsigned int i = 0; i < mAlgorithms.size(); i++){
			if (!mAlgorithms[i]->run(tower, advice))
				break;  // drop out as soon as an algorithm returns false... 
		}
		advice->setTimestamp();
		return advice;
	}

}

extern "C" DACORE_API const char* DACORE_APIENTRY PreventTargetStr(dacore::IOverride::PreventTarget t) { 
	return dacore::Override::preventTargetStr(t); 
}
