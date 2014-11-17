//
//  Scenario7.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Scenario7_h
#define Distillation_Advisor_Scenario7_h

#include "stdafx.h"

#include "IAlgorithm.h"
#include "ITower.h"
#include "ITowerConfig.h"

namespace dacore {

	class Scenario7 : public IAlgorithm {

	public:
		static const std::string mID;

		virtual ~Scenario7(){}

	protected:

		virtual bool doAlgorithm(ITower* tower, IAdvice* advice){

			// __NO__ if `{Impur.}` AND isMaximizingFeed
			if (impur(tower) && tower->getConfig()->isMaximizingFeed())
				return true;

			// otherwise, these conditions must be met:

			// - hkStatus is not High (or Low if reversing logic of OH composition)
			if (isHeavyKeyStatusHigh(tower))
				return true;

			// - Vapor Loading is not High
			if (getVaporLoadingStatus(tower) == ITowerReport::Status::HIGH)
				return true;

			// - either:
			// - lk is monitored by analysis and lkStatus is high
			// - *or* lk is monitored by temperature and lkStatus is low
			if (!(tower->getConfig()->getBottoms()->getEffectiveStatus(ITowerReport::Status::LOW) == tower->getReport()->getLightKey()->getStatus()))
				return true;

			// - one or more of:
			// - Liquid Loading is low
			// - Vapor Loading is low
			// - hkStatus is ~Hi (or ~Lo if reversing logic of OH composition)
			if (getLiquidLoadingStatus(tower) == ITowerReport::Status::LOW
				|| getVaporLoadingStatus(tower) == ITowerReport::Status::LOW
				|| isHeavyKeyStatusAlmostHigh(tower)) {
				AdviceMessage m(tower);
				advice->setPrimaryMessage(m.getMessage(IAdvice::MessageType::INCREASE_REBOIL));
				advice->setPrimaryMessageType(IAdvice::MessageType::INCREASE_REBOIL);
				advice->setAlgorithmId(mID);
				advice->setSeverity(IAdvice::Severity::RED);
				return false;
			}

			return true;
		}
	};

}

#endif
