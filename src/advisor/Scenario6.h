//
//  Scenario6.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Scenario6_h
#define Distillation_Advisor_Scenario6_h

#include "stdafx.h"

#include "IAlgorithm.h"
#include "ITower.h"
#include "ITowerConfig.h"
#include "IReboiler.h"
#include "IOverridesData.h"

namespace dacore {

	class Scenario6 : public IAlgorithm {

	public:
		static const std::string mID;

		virtual ~Scenario6(){}

	protected:

		virtual bool doAlgorithm(ITower* tower, IAdvice* advice){

			ITowerConfig* config = tower->getConfig();
			ITowerReport* report = tower->getReport();

			// __NO__ if `{Impur.}` AND isMaximizingFeed
			if (impur(tower) && config->isMaximizingFeed())
				return true;

			// otherwise, these conditions must be met:

			// - hkStatus is not High (or Low if reversing logic of OH composition)
			if (isHeavyKeyStatusHigh(tower))
				return true;

			// - hkStatus is not ~Hi (or ~Lo if reversing logic of OH composition)
			if (isHeavyKeyStatusAlmostHigh(tower))
				return true;

			// - Vapor Loading is not Low
			if (getVaporLoadingStatus(tower) == ITowerReport::Status::LOW)
				return true;

			// - Liquid Loading is not Low
			if (getLiquidLoadingStatus(tower) == ITowerReport::Status::LOW)
				return true;

			// - either:
			// - lk is monitored by analysis and lkStatus is high
			// - *or* lk is monitored by temperature and lkStatus is low
			if (config->getBottoms()->getEffectiveStatus(ITowerReport::Status::LOW) == report->getLightKey()->getStatus()) {
				IAdvice::MessageType type;

				if ((tower->getConfig()->getOverrides()->willTripFor(IOverride::PreventTarget::REBOIL_DECREASE, tower->getData()->getOverrides()->getPreventsDecreaseInReboil())
					|| config->getBottoms()->getReboiler()->getLevelControl()
					|| lightsHiHi(tower))
					&& getVaporLoadingStatus(tower) != ITowerReport::Status::HIGH)
					type = IAdvice::MessageType::INCREASE_REBOIL;
				else if (config->getOverhead()->getExternalReflux()->getConfigured() == false)
					type = IAdvice::MessageType::INCREASE_REBOIL;
				else if (config->getBottoms()->getComposition()->isManipulatedSetPoint()
					&& getVaporLoadingStatus(tower) != ITowerReport::Status::HIGH)
					type = IAdvice::MessageType::INCREASE_REBOIL;
				else
					type = IAdvice::MessageType::DECREASE_REFLUX;

				AdviceMessage m(tower);
				advice->setPrimaryMessage(m.getMessage(type));
				advice->setPrimaryMessageType(type);
				advice->setAlgorithmId(mID);
				advice->setSeverity(IAdvice::Severity::RED);
				return false;
			}

			return true;
		}

	};

}

#endif
