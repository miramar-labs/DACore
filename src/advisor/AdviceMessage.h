//
//  AdviceMessage.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/11/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_AdviceMessage_h
#define Distillation_Advisor_AdviceMessage_h

#include "stdafx.h"

#include "IExternalReflux.h"
#include "IReboiler.h"
#include "ITower.h"
#include "ITowerData.h"
#include "IOverridesData.h"

#include "Overrides.h"

namespace dacore {

	class AdviceMessage {

	public:
		AdviceMessage(ITower* tower)
			:mTower(tower){}
		virtual ~AdviceMessage(){}

		virtual std::string getMessage(IAdvice::MessageType type){
			std::string msg;
			switch (type){
			case IAdvice::MessageType::DECREASE_REBOIL:
				return decreaseReboil();
			case IAdvice::MessageType::INCREASE_REBOIL:
				return increaseReboil();
			case IAdvice::MessageType::DECREASE_BOTH_REBOIL_AND_REFLUX:
				return decreaseRefluxAndReboil();
			case IAdvice::MessageType::INCREASE_BOTH_REBOIL_AND_REFLUX:
				return increaseRefluxAndReboil();
			case IAdvice::MessageType::INCREASE_REFLUX:
				return increaseReflux();
			case IAdvice::MessageType::DECREASE_REFLUX:
				return decreaseReflux();
			default:
				//TODO: throw exception....
				break;
			}
			return msg;
		}

	private:
		ITower*     mTower;

		std::string increaseReflux(){
			if (REFLUX(mTower)->getIncreaseMethod() == IExternalReflux::IncreaseMethod::REFLUX_INC_METHOD_OTHER)
				return REFLUX(mTower)->getIncreaseMethodOther();
			return RefluxIncMethodStr(REFLUX(mTower)->getIncreaseMethod());
		}

		std::string increaseReboil(){
			std::string message;
			IOverride* increaseReboil = mTower->getConfig()->getOverrides()->get(IOverride::PreventTarget::REBOIL_INCREASE);
			if (REBOILER(mTower)->getIncreaseMethod() == IReboiler::IncreaseMethod::REBOIL_INC_METHOD_OTHER)
				message = REBOILER(mTower)->getIncreaseMethodOther();
			else
				message = ReboilerIncMethodStr(REBOILER(mTower)->getIncreaseMethod());

			if (increaseReboil != NULL
				&& increaseReboil->willTripFor(mTower->getData()->getOverrides()->getPreventsIncreaseInReboil())) {
				message = increaseReboil->getMessage(message);
			}

			return message;
		}

		std::string increaseRefluxAndReboil(){
			if (!mTower->getConfig()->getOverhead()->getExternalReflux()->getConfigured())
				return increaseReboil();

			IOverride* increaseRefluxOverride = mTower->getConfig()->getOverrides()->get(IOverride::PreventTarget::REFLUX_INCREASE);
			IOverride* increaseReboilOverride = mTower->getConfig()->getOverrides()->get(IOverride::PreventTarget::REBOIL_INCREASE);

			bool refluxActivated = increaseRefluxOverride == NULL ? false
				: increaseRefluxOverride->willTripFor(mTower->getData()->getOverrides()->getPreventsIncreaseInReflux());
			bool reboilActivated = increaseReboilOverride == NULL ? false
				: increaseReboilOverride->willTripFor(mTower->getData()->getOverrides()->getPreventsIncreaseInReboil());

			if (refluxActivated && reboilActivated) {
				return "Suggestion to increase both reboil and reflux disabled by \""
					+ increaseRefluxOverride->getName()
					+ "\" and \""
					+ increaseReboilOverride->getName() + "\" overrides.";
			}
			else if (refluxActivated) {
				return "Suggestion to increase both reboil and reflux disabled by \""
					+ increaseRefluxOverride->getName() + "\" override.";
			}
			else if (reboilActivated) {
				return "Suggestion to increase both reboil and reflux disabled by \""
					+ increaseReboilOverride->getName() + "\" override.";
			}

			std::string increaseReflux = this->increaseReflux();
			/* TODO if (increaseReflux.length() > 0) {
				increaseReflux = increaseReflux.substring(0, 1).toLowerCase()
				+ increaseReflux.substring(1);
				}*/

			return increaseReboil() + " and " + increaseReflux;
		}

		std::string decreaseReflux(){
			if (REFLUX(mTower)->getDecreaseMethod() == IExternalReflux::DecreaseMethod::REFLUX_DEC_METHOD_OTHER) {
				return REFLUX(mTower)->getDecreaseMethodOther();
			}
			return RefluxDecMethodStr(REFLUX(mTower)->getDecreaseMethod());
		}

		std::string decreaseReboil(){
			IOverride* decreaseReboilOverride = mTower->getConfig()->getOverrides()->get(IOverride::PreventTarget::REBOIL_DECREASE);
			std::string message;
			if (REBOILER(mTower)->getDecreaseMethod() == IReboiler::DecreaseMethod::REBOIL_DEC_METHOD_OTHER) {
				message = REBOILER(mTower)->getDecreaseMethodOther();
			}
			else {
				message = ReboilerDecMethodStr(REBOILER(mTower)->getDecreaseMethod());
			}

			if (decreaseReboilOverride != NULL
				&& decreaseReboilOverride->willTripFor(mTower->getData()->getOverrides()->getPreventsDecreaseInReboil())) {
				message = "Suggestion \"" + message + "\" disabled by \""
					+ decreaseReboilOverride->getName() + "\" override.";
			}
			return message;
		}

		std::string decreaseRefluxAndReboil(){
			if (!mTower->getConfig()->getOverhead()->getExternalReflux()->getConfigured())
				return decreaseReboil();

			IOverride* decreaseRefluxOverride = mTower->getConfig()->getOverrides()->get(IOverride::PreventTarget::REFLUX_DECREASE);
			IOverride* decreaseReboilOverride = mTower->getConfig()->getOverrides()->get(IOverride::PreventTarget::REBOIL_DECREASE);

			bool refluxActivated = decreaseRefluxOverride == NULL ? false
				: decreaseRefluxOverride->willTripFor(mTower->getData()->getOverrides()->getPreventsDecreaseInReflux());
			bool reboilActivated = decreaseRefluxOverride == NULL ? false
				: decreaseReboilOverride->willTripFor(mTower->getData()->getOverrides()->getPreventsDecreaseInReboil());

			if (refluxActivated && reboilActivated) {
				return "Suggestion to decrease both reboil and reflux disabled by \""
					+ decreaseRefluxOverride->getName()
					+ "\" and \""
					+ decreaseReboilOverride->getName() + "\" overrides.";
			}
			else if (refluxActivated) {
				return "Suggestion to decrease both reboil and reflux disabled by \""
					+ decreaseRefluxOverride->getName() + "\" override.";
			}
			else if (reboilActivated) {
				return "Suggestion to decrease both reboil and reflux disabled by \""
					+ decreaseReboilOverride->getName() + "\" override.";
			}

			std::string decreaseReflux = this->decreaseReflux();

			/* TODO if (decreaseReflux.length() > 0) {
				decreaseReflux = decreaseReflux.substring(0, 1).toLowerCase()
				+ decreaseReflux.substring(1);
				}*/

			return decreaseReboil() + " and " + decreaseReflux;
		}

	};

}

#endif
