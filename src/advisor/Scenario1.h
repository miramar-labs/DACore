//
//  Scenario1.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef __Distillation_Advisor__Scenario1__
#define __Distillation_Advisor__Scenario1__

#include "stdafx.h"

#include "IAlgorithm.h"
#include "ITower.h"
#include "ITowerConfig.h"
#include "AdviceMessage.h"

namespace dacore {

	class Scenario1 : public IAlgorithm {

	public:
		static const std::string mID;

		virtual ~Scenario1(){}

	protected:

		virtual bool doAlgorithm(ITower* tower, IAdvice* advice){

			// - hkStatus is High (or Low if reversing logic of OH composition)
			if (!isHeavyKeyStatusHigh(tower))
				return true;

			// - one or more of the following is High:
			// - deltaStatus
			// - refluxStatus
			// - feedStatus
			// - heatingStatus

			ITowerReport* report = tower->getReport();

			if (report->getDelta()->getStatus() != ITowerReport::Status::HIGH
				&& report->getReflux()->getStatus() != ITowerReport::Status::HIGH
				&& report->getFeed()->getStatus() != ITowerReport::Status::HIGH
				&& report->getHeating()->getStatus() != ITowerReport::Status::HIGH) {
				return true;
			}

			if (tower->getConfig()->getBottoms()->getEffectiveStatus(ITowerReport::Status::LOW) == report->getLightKey()->getStatus()) {

				std::string messagePrefix;

				if (tower->getConfig()->isMaximizingFeed())
					messagePrefix = "Decrease feed. If not possible, consider trying: ";
				//else
				//	messagePrefix = "Consider trying: ";

				AdviceMessage m(tower);
				std::string msg = messagePrefix + m.getMessage(IAdvice::MessageType::DECREASE_BOTH_REBOIL_AND_REFLUX);

				advice->setPrimaryMessage(msg);
				advice->setPrimaryMessageType(IAdvice::MessageType::DECREASE_BOTH_REBOIL_AND_REFLUX);
				advice->setAlgorithmId(mID);
				advice->setSeverity(IAdvice::Severity::RED);

				return false;
			}

			return true;
		}
	};

}

#endif /* defined(__Distillation_Advisor__Scenario1__) */
