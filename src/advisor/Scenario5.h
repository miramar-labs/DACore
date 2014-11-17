//
//  Scenario5.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Scenario5_h
#define Distillation_Advisor_Scenario5_h

#include "stdafx.h"

#include "IAlgorithm.h"
#include "ITower.h"
#include "ITowerConfig.h"
#include "IExternalReflux.h"

namespace dacore {

	class Scenario5 : public IAlgorithm {

	public:
		static const std::string mID;

		virtual ~Scenario5(){}

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
			// - lk is monitored by analysis and lkStatus is high
			// - _or_ lk is monitored by temperature and lkStatus is low
			if (config->getBottoms()->getEffectiveStatus(ITowerReport::Status::LOW) == report->getLightKey()->getStatus())
				return true;

			// - Liquid Loading is not High

			if (getLiquidLoadingStatus(tower) == ITowerReport::Status::HIGH)
				return true;

			// - either (one or more):
			// - Vapor Loading is Low
			// - _or_ lk is monitored by analysis and lkStatus is ~hi
			// - _or_ lk is monitored by temperature and lkStatus is ~lo
			if (getVaporLoadingStatus(tower) == ITowerReport::Status::LOW
				|| config->getBottoms()->getEffectiveStatus(ITowerReport::Status::ALMOST_LOW) == report->getLightKey()->getStatus()) {
				AdviceMessage m(tower);
				if (tower->getConfig()->getOverhead()->getExternalReflux()->getConfigured()) {
					advice->setPrimaryMessage(m.getMessage(IAdvice::MessageType::INCREASE_REFLUX));
					advice->setPrimaryMessageType(IAdvice::MessageType::INCREASE_REFLUX);
				}
				else {
					// Produces blank advice in DM if no external reflux.
					advice->setPrimaryMessage("No advice at this time.");
				}
				advice->setAlgorithmId(mID);
				advice->setSeverity(IAdvice::Severity::RED);
				return false;
			}

			return true;

		}

	};

}

#endif
