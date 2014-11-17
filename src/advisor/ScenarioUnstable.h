//
//  ScenarioUnstable.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef __Distillation_Advisor__ScenarioUnstable__
#define __Distillation_Advisor__ScenarioUnstable__

#include "stdafx.h"

#include "IAlgorithm.h"
#include "IReportItem.h"

#include "ITowerReport.h"
#include "ITowerConfig.h"
#include "ITower.h"
#include "IAdvice.h"
#include "IOverhead.h"
#include "IBottoms.h"
#include "IComposition.h"

namespace dacore {

	class ScenarioUnstable : public IAlgorithm {

	public:
		static const std::string mID;

		virtual ~ScenarioUnstable(){}

	protected:
		virtual bool doAlgorithm(ITower* tower, IAdvice* advice){

			ITowerReport* report = tower->getReport();
			ITowerConfig* config = tower->getConfig();

			bool heavyKeyUnstable = isUnstable(report->getHeavyKey(),
				OVERHEAD_COMPOSITION(tower)->isManipulatedSetPoint(),
				OVERHEAD_COMPOSITION(tower)->getInstabilityValPercent());
			bool lightKeyUnstable = isUnstable(report->getLightKey(),
				BOTTOMS_COMPOSITION(tower)->isManipulatedSetPoint(),
				BOTTOMS_COMPOSITION(tower)->getInstabilityValPercent());

			if (heavyKeyUnstable || lightKeyUnstable) {
				advice->setAlgorithmId(mID);
				advice->setSeverity(IAdvice::Severity::RED);
				if (!heavyKeyUnstable) {
					advice->setPrimaryMessage("Bottoms composition unstable. No advice at this time.");
				}
				else if (!lightKeyUnstable) {
					advice->setPrimaryMessage("Overhead composition unstable. No advice at this time.");
				}
				else {
					advice->setPrimaryMessage("Overhead and Bottoms compositions unstable. No advice at this time.");
				}
				return false;
			}

			return true;
		}

	private:
		bool isUnstable(IReportItem* r, bool isManipulatedSetpoint, double instability) {

			double deltaMinMaxOrMin = std::max(r->getMax() - r->getMin(), r->getMin());

			if (
				std::max(r->getCurrent(), std::max(r->getPrior20(), r->getPrior40()))
				- std::min(r->getCurrent(), std::min(r->getPrior20(), r->getPrior40())
				)
				<= deltaMinMaxOrMin * 0.25)
				return false;

			if (r->getPrior40() < 0.05 * deltaMinMaxOrMin)
				return false;

			if (r->getPrior20() < 0.05 * deltaMinMaxOrMin)
				return false;

			if (r->getCurrent() < 0.05 * deltaMinMaxOrMin)
				return false;

			if (r->getCurrent() < r->getPrior20() * (1 - instability))
				return true;
			if (r->getPrior20() < r->getPrior40() * (1 - instability))
				return true;
			if (r->getCurrent() > r->getPrior20() * (1 + instability))
				return true;
			if (r->getPrior20() > r->getPrior40() * (1 + instability))
				return true;

			return false;
		}

	};

}

#endif /* defined(__Distillation_Advisor__ScenarioUnstable__) */
