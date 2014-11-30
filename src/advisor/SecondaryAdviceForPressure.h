//
//  SecondaryAdviceForPressure.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef __Distillation_Advisor__SecondaryAdviceForPressure__
#define __Distillation_Advisor__SecondaryAdviceForPressure__

#include "stdafx.h"

#include "IAlgorithm.h"
#include "ITower.h"
#include "ITowerReport.h"
#include "IColumn.h"
#include "IOverrides.h"
#include "ITowerData.h"
#include "IOverridesData.h"
#include "IValidate.h"

namespace dacore {

	class SecondaryAdviceForPressure : public IAlgorithm {

	public:
		static const std::string mID;

		virtual ~SecondaryAdviceForPressure(){}

	private:
		std::string getG45Message(ITower* tower) {
			ITowerReport* r = tower->getReport();
			bool reverseActing = tower->getConfig()->getColumn()->isPressureReverseActing();

			if (tower->getConfig()->getColumn()->isSuggestChanges() == false)
				return "";

			IBottoms* base = tower->getConfig()->getBottoms();

			if (!isHeavyKeyStatusHigh(tower)
				&& !isHeavyKeyStatusAlmostHigh(tower)
				&& !(r->getDelta()->getStatus() == ITowerReport::Status::HIGH)
				&& !(r->getDelta()->getStatus() == ITowerReport::Status::ALMOST_HIGH)
				&& !(r->getOperatingPressure()->getStatus() == ITowerReport::Status::LOW)
				&& !(r->getOperatingPressure()->getStatus() == ITowerReport::Status::ALMOST_LOW)
				&& ((reverseActing && !(r->getOutputOnPIC()->getStatus() == ITowerReport::Status::HIGH || r
				->getOutputOnPIC()->getStatus() == ITowerReport::Status::ALMOST_HIGH)) || (!reverseActing && !(r
				->getOutputOnPIC()->getStatus() == ITowerReport::Status::LOW || r
				->getOutputOnPIC()->getStatus() == ITowerReport::Status::ALMOST_LOW)))) {
				return getE56Message(tower);
			}
			else if (!(base->getEffectiveStatus(ITowerReport::Status::LOW) == r
				->getLightKey()->getStatus() || base
				->getEffectiveStatus(ITowerReport::Status::ALMOST_LOW) == r
				->getLightKey()->getStatus())
				&& r->getDelta()->getStatus() == ITowerReport::Status::HIGH
				&& !(r->getOperatingPressure()->getStatus() == ITowerReport::Status::HIGH || r
				->getOperatingPressure()->getStatus() == ITowerReport::Status::ALMOST_HIGH)
				&& ((!reverseActing && !(r->getOutputOnPIC()->getStatus() == ITowerReport::Status::HIGH || r
				->getOutputOnPIC()->getStatus() == ITowerReport::Status::ALMOST_HIGH)) || (reverseActing && !(r
				->getOutputOnPIC()->getStatus() == ITowerReport::Status::LOW || r
				->getOutputOnPIC()->getStatus() == ITowerReport::Status::ALMOST_LOW)))) {
				return getE55Message(tower);
			}
			else if (r->getOutputOnPIC()->getStatus() == ITowerReport::Status::HIGH
				&& !reverseActing) {
				return "The output on the PIC (pressure controller) is exceeding the maximum operating parameter.";
			}
			else if (r->getOutputOnPIC()->getStatus() == ITowerReport::Status::LOW
				&& reverseActing) {
				return "The output on the PIC (pressure controller) is below the minimum operating parameter.";
			}

			return "";
		}

		std::string getE55Message(ITower* tower) {
			IOverride* adviceOverride = tower->getConfig()->getOverrides()
				->get(IOverride::PreventTarget::PRESSURE_INCREASE);
			bool activated = adviceOverride == nullptr ? false : adviceOverride->willTripFor(tower->getData()->getOverrides()
				->getPreventsPressureIncrease());

			if (activated) {
				return "Suggestion, \"It may be necessary to raise operating"	\
					 " pressure,\" disabled by \"" + adviceOverride->getName() + "\" override.";
			}
			else {
				return "It may be necessary to raise operating pressure "		\
					 "(may also require an increase in temperature parameters).";
			}

		}

		std::string getE56Message(ITower* tower) {
			IOverride* adviceOverride = tower->getConfig()->getOverrides()->get(IOverride::PreventTarget::PRESSURE_DECREASE);
			bool activated = adviceOverride == nullptr ? false : adviceOverride->willTripFor(tower->getData()->getOverrides()
				->getPreventsPressureDecrease());

			if (activated) {
				return "Suggestion, \"It may be possible to drop operating"		\
					" pressure,\" disabled by \"" + adviceOverride->getName() + "\" override.";
			}
			else {
				return "It may be possible to drop operating pressure "			\
					"(may also require a drop in temperature parameters).";
			}
		};

		std::string getG46Message(ITower* tower) {
			ITowerReport::Status vapor = getVaporLoadingStatus(tower);
			ITowerReport::Status liquid = getLiquidLoadingStatus(tower);

			if ((vapor == ITowerReport::Status::HIGH && liquid == ITowerReport::Status::LOW)
				|| (vapor == ITowerReport::Status::LOW && liquid == ITowerReport::Status::HIGH)) {
				return "ERROR - Bad instrumentation (feed, reflux, or steam), abnormal "	\
					"feed composition, or incorrect operating parameters.";
			}

			ITowerReport* r = tower->getReport();
			IColumn::DeltaOption deltaOption = tower->getConfig()->getColumn()->getUsePressureOrTemperatureDelta();
			if (r->getDelta()->getRange() > r->getFeed()->getRange() + 0.5) {
				if (deltaOption == IColumn::DeltaOption::TEMPERATURE)
					return "ERROR - Delta Temperature is reading too high for current "		\
					 "load on column, negatively impacting some decisions.";
				else if (deltaOption == IColumn::DeltaOption::PRESSURE)
					return "ERROR - Delta Pressure is reading too high for current "		\
					 "load on column, negatively impacting some decisions.";
			}
			else if (r->getDelta()->getRange() < r->getFeed()->getRange() - 0.5) {
				if (deltaOption == IColumn::DeltaOption::TEMPERATURE)
					return "ERROR - Delta Temperature is reading low high for current "		\
					 "load on column, negatively impacting some decisions.";
				else if (deltaOption == IColumn::DeltaOption::PRESSURE)
					return "ERROR- Delta Pressure is reading too low for current "			\
					 "load on column, negatively impacting some decisions.";
			}

			return "";
		}

	protected:
		virtual bool doAlgorithm(ITower* tower, IAdvice* advice){ 
			ITowerReport* r = tower->getReport();

			if (r->getFeed()->getMax() == Validate::INVALID_DBL)
				return true;

			std::string message;

			if (r->getDelta()->getRange() == Validate::INVALID_DBL || 
				r->getFeed()->getRange() == Validate::INVALID_DBL) {
				message = getG45Message(tower);
			}
			else {
				message = getG46Message(tower);
				if (message == "")
					message = getG45Message(tower);
			}

			if (message != "")
				advice->setSecondaryMessage(message);

			return true;
		}

	};

}

#endif /* defined(__Distillation_Advisor__SecondaryAdviceForPressure__) */
