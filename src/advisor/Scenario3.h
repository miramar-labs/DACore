//
//  Scenario3.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Scenario3_h
#define Distillation_Advisor_Scenario3_h

#include "stdafx.h"

#include "IAlgorithm.h"
#include "ITower.h"
#include "ITowerConfig.h"
#include "ITowerReport.h"

namespace dacore {

	class Scenario3 : public IAlgorithm {

	public:
		static const std::string mID;

		virtual ~Scenario3(){}

	protected:

		virtual bool doAlgorithm(ITower* tower, IAdvice* advice){

			ITowerConfig* config = tower->getConfig();
			ITowerReport* report = tower->getReport();

			// - hkStatus is Low (or High if reversing logic of OH composition)
			if (!isHeavyKeyStatusLow(tower))
				return true;

			// - Liquid Loading is not Low
			if (getLiquidLoadingStatus(tower) == ITowerReport::Status::LOW)
				return true;

			// - Vapor Loading is not Low
			if (getVaporLoadingStatus(tower) == ITowerReport::Status::LOW)
				return true;

			if (config->isMaximizingFeed() && impur(tower)) {
				advice->setPrimaryMessage("Increase feed. (To prevent feed rate suggestions set the tower to Optimize Only.)");
				return true;
			}

			// - either:
			// - lk is monitored by analysis and lkStatus is Low
			// - *or* lk is monitored by temperature and lkStatus is High

			if (config->getBottoms()->getEffectiveStatus(ITowerReport::Status::HIGH) == report->getLightKey()->getStatus()) {
				AdviceMessage m(tower);
				advice->setPrimaryMessage(m.getMessage(IAdvice::MessageType::DECREASE_BOTH_REBOIL_AND_REFLUX));
				advice->setPrimaryMessageType(IAdvice::MessageType::DECREASE_BOTH_REBOIL_AND_REFLUX);
				advice->setAlgorithmId(mID);
				advice->setSeverity(IAdvice::Severity::RED);
				return false;
			}

			return true;
		}

	};

}

#endif
