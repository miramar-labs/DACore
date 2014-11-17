//
//  Scenario8.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Scenario8_h
#define Distillation_Advisor_Scenario8_h

#include "stdafx.h"

#include "IAlgorithm.h"
#include "ITower.h"
#include "ITowerConfig.h"

namespace dacore {

	class Scenario8 : public IAlgorithm {

	public:
		static const std::string mID;

		virtual ~Scenario8(){}

	protected:

		virtual bool doAlgorithm(ITower* tower, IAdvice* advice){

			ITowerConfig* config = tower->getConfig();
			ITowerReport* report = tower->getReport();

			// - neither:
			// - lk is monitored by analysis and lkStatus is high
			// - *or* lk is monitored by temperature and lkStatus is low
			if (config->getBottoms()->getEffectiveStatus(ITowerReport::Status::LOW) == report->getLightKey()->getStatus())
				return true;

			// - hkStatus is Low (or High if reversing logic of OH composition)
			if (!isHeavyKeyStatusLow(tower))
				return true;

			// - Liquid Loading is not Low
			if (getLiquidLoadingStatus(tower) == ITowerReport::Status::LOW)
				return true;

			// - Vapor Loading is not Low
			if (getVaporLoadingStatus(tower) == ITowerReport::Status::LOW)
				return true;

			std::string primaryMessage;
			AdviceMessage m(tower);
			if (tower->getConfig()->getOverhead()->getExternalReflux()->getConfigured()) {
				if (tower->getConfig()->isMaximizingFeed()
					&& impur(tower)) {
					primaryMessage = "Increase feed. If not possible, ";
				}
				primaryMessage += m.getMessage(IAdvice::MessageType::DECREASE_REFLUX);
				advice->setPrimaryMessageType(IAdvice::MessageType::DECREASE_REFLUX);
			}
			else {
				if (tower->getConfig()->isMaximizingFeed()
					&& impur(tower)) {
					primaryMessage = "Increase feed.";
				}
				else {
					primaryMessage = "No advice at this time.";
				}
			}
			advice->setPrimaryMessage(primaryMessage);
			advice->setAlgorithmId(mID);
			advice->setSeverity(IAdvice::Severity::RED);
			return false;
		}

	};

}
#endif
