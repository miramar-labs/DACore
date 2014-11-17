//
//  Scenario9.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Scenario9_h
#define Distillation_Advisor_Scenario9_h

#include "stdafx.h"
#include "IAlgorithm.h"
#include "ITower.h"
#include "ITowerConfig.h"

namespace dacore {

	class Scenario9 : public IAlgorithm {

	public:
		static const std::string mID;

		virtual ~Scenario9(){}

	protected:

		virtual bool doAlgorithm(ITower* tower, IAdvice* advice){

			ITowerConfig* config = tower->getConfig();
			ITowerReport* report = tower->getReport();

			// - hkStatus is not High (or Low if reversing logic of OH composition)
			if (isHeavyKeyStatusHigh(tower))
				return true;

			// - Vapor Loading is not Low
			if (getVaporLoadingStatus(tower) == ITowerReport::Status::LOW)
				return true;

			// - either:
			// - lk is monitored by analysis and lkStatus is low
			// - *or* lk is monitored by temperature and lkStatus is high
			if (config->getBottoms()->getEffectiveStatus(ITowerReport::Status::HIGH) == report->getLightKey()->getStatus()) {
				std::string primaryMessage;

				if (config->isMaximizingFeed() && impur(tower)) {
					primaryMessage = "Increase feed. If not possible, ";
				}

				AdviceMessage m(tower);
				primaryMessage += m.getMessage(IAdvice::MessageType::DECREASE_REBOIL);
				advice->setPrimaryMessage(primaryMessage);
				advice->setPrimaryMessageType(IAdvice::MessageType::DECREASE_REBOIL);
				advice->setAlgorithmId(mID);
				advice->setSeverity(IAdvice::Severity::RED);
				return false;
			}

			return true;
		}
	};

}

#endif
