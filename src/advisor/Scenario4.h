//
//  Scenario4.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Scenario4_h
#define Distillation_Advisor_Scenario4_h

#include "stdafx.h"

#include "IAlgorithm.h"
#include "ITower.h"
#include "ITowerConfig.h"
#include "ITowerReport.h"
#include "IExternalReflux.h"
#include "IOverride.h"
#include "ITowerData.h"
#include "IOverridesData.h"

namespace dacore {

	class Scenario4 : public IAlgorithm {

	public:
		static const std::string mID;

		virtual ~Scenario4(){}

	protected:

		virtual bool doAlgorithm(ITower* tower, IAdvice* advice){

			ITowerConfig* config = tower->getConfig();
			ITowerReport* report = tower->getReport();

			// __NO__ if `{Impur.}` AND isMaximizingFeed
			if (impur(tower) && config->isMaximizingFeed())
				return true;

			// Otherwise, all of the following:

			// - hkStatus is High (or low if reversing logic of OH composition)
			if (!isHeavyKeyStatusHigh(tower))
				return true;

			// - neither:
			// - lk is monitored by analysis and lkStatus is high or ~hi
			// - *or* lk is monitored by temperature and lkStatus is low or ~lo
			ITowerReport::Status lkStatus = report->getLightKey()->getStatus();
			if (config->getBottoms()->getEffectiveStatus(ITowerReport::Status::LOW) == lkStatus
				|| config->getBottoms()->getEffectiveStatus(ITowerReport::Status::ALMOST_LOW) == lkStatus)
				return true;

			// - Vapor Loading is not low
			if (getVaporLoadingStatus(tower) == ITowerReport::Status::LOW)
				return true;

			AdviceMessage m(tower);
			IAdvice::MessageType messageType;

			if (getLiquidLoadingStatus(tower) != ITowerReport::Status::HIGH
				&& (config->getOverrides()->willTripFor(IOverride::PreventTarget::REBOIL_DECREASE, tower->getData()->getOverrides()->getPreventsDecreaseInReboil())
				|| config->getOverhead()->getExternalReflux()->getLevelControl()
				|| heaviesHiHi(tower))
				) {
				messageType = IAdvice::MessageType::INCREASE_REFLUX;
			}
			else {
				messageType = IAdvice::MessageType::DECREASE_REBOIL;
			}
			advice->setPrimaryMessage(m.getMessage(messageType));
			advice->setPrimaryMessageType(messageType);
			advice->setAlgorithmId(mID);
			advice->setSeverity(IAdvice::Severity::RED);

			return false;
		}
	};
}
#endif
