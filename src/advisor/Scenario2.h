//
//  Scenario2.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef __Distillation_Advisor__Scenario2__
#define __Distillation_Advisor__Scenario2__

#include "stdafx.h"

#include "IAlgorithm.h"
#include "ITower.h"
#include "ITowerConfig.h"

namespace dacore {

	class Scenario2 : public IAlgorithm {

	public:
		static const std::string mID;

		virtual ~Scenario2(){}

	protected:

		virtual bool doAlgorithm(ITower* tower, IAdvice* advice){

			// - hkStatus is High (or Low if reversing logic of OH composition)
			if (!isHeavyKeyStatusHigh(tower))
				return true;

			// - Liquid Loading is not High
			if (getLiquidLoadingStatus(tower) == ITowerReport::Status::HIGH)
				return true;

			// - Vapor Loading is not High
			if (getVaporLoadingStatus(tower) == ITowerReport::Status::HIGH)
				return true;

			// - either:
			// - lk is monitored by analysis and lkStatus is High
			// - *or* lk is monitored by temperature and lkStatus is Low
			if (tower->getConfig()->getBottoms()->getEffectiveStatus(ITowerReport::Status::LOW) == tower->getReport()->getLightKey()->getStatus()) {
				ITowerConfig* config = tower->getConfig();
				if (config->isMaximizingFeed() && impur(tower)) {
					advice->setPrimaryMessage("Increase feed (to prevent feed rate suggestions configure tower to 'Optimize Only').");
				}
				else {
					AdviceMessage m(tower);
					advice->setPrimaryMessage(m.getMessage(IAdvice::MessageType::INCREASE_BOTH_REBOIL_AND_REFLUX));
					advice->setPrimaryMessageType(IAdvice::MessageType::INCREASE_BOTH_REBOIL_AND_REFLUX);
				}

				advice->setAlgorithmId(mID);
				advice->setSeverity(IAdvice::Severity::RED);
				return false;
			}

			return true;
		}

	};

}

#endif /* defined(__Distillation_Advisor__Scenario2__) */
