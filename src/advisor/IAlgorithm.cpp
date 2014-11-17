//
//  Algorithm1.cpp
//  Distillation Advisor
//
//  Created by Aaron Cody on 6/30/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#include "stdafx.h"

#include "IAlgorithm.h"
#include "ITower.h"
#include "ITowerConfig.h"
#include "ITowerReport.h"
#include "IReportItem.h"
#include "IBottoms.h"
#include "IReboiler.h"
#include "IOverhead.h"
#include "IExternalReflux.h"
#include "IFeed.h"
#include "IColumn.h"
#include "IAdvice.h"

#include "ScenarioIncomplete.h"
#include "ScenarioInactive.h"
#include "ScenarioUnstable.h"
#include "SecondaryAdviceForPressure.h"
#include "Scenario1.h"
#include "Scenario2.h"
#include "Scenario3.h"
#include "Scenario4.h"
#include "Scenario5.h"
#include "Scenario6.h"
#include "Scenario7.h"
#include "Scenario8.h"
#include "Scenario9.h"
#include "ScenarioNoAdvice.h"

namespace dacore {

	static double RANGE_HIGH = 1.2;     //TODO - pull from config
	static double RANGE_LOW = -0.2;     //TODO - pull from config

	const std::string ScenarioIncomplete::mID = "Incomplete";
	const std::string ScenarioInactive::mID = "Inactive";
	const std::string ScenarioUnstable::mID = "Unstable";
	const std::string SecondaryAdviceForPressure::mID = "TODO";
	const std::string Scenario1::mID = "1. High Impurities Both Ends; High Loading";
	const std::string Scenario2::mID = "2. High Impurities Both Ends; Low or Normal Loading";
	const std::string Scenario3::mID = "3. Impurities Below Minimum Both Ends; Sufficient Loading";
	const std::string Scenario4::mID = "4. High Heavies In OH; Lights In Base Less Than 'Almost High'; Sufficient Loading";
	const std::string Scenario5::mID = "5. High Heavies In OH; Lights In Base Less Than Max; Load Less Than Min; Or, Base Lights Greater Than Almost High And Load Ok";
	const std::string Scenario6::mID = "6. High Lights In Base; Heavies In Overhead Less Than Almost High; Sufficient Loading";
	const std::string Scenario7::mID = "7. High Lights In Base; Heavies In Overhead Less Than Max; Load Less Than Min; Or, Heavies in Overhead Greater Than Almost High And Load OK";
	const std::string Scenario8::mID = "8. Heavies in Overhead Below Min; Lights in Base Above Min; Sufficient Loading";
	const std::string Scenario9::mID = "9. Lights In Base Below Min; Heavies in Overhead Less Than Max; Sufficient Loading";
	const std::string ScenarioNoAdvice::mID = "No Advice";

	bool IAlgorithm::impur(ITower* tower){

		ITowerConfig* config = tower->getConfig();
		ITowerReport* report = tower->getReport();

		if (isHeavyKeyStatusHigh(tower) || isHeavyKeyStatusAlmostHigh(tower))
			return false;

		IBottoms* base = config->getBottoms();

		ITowerReport::Status lightKeyStatus = report->getLightKey()->getStatus();

		if (lightKeyStatus == base->getEffectiveStatus(ITowerReport::Status::LOW)
			|| lightKeyStatus == base->getEffectiveStatus(ITowerReport::Status::ALMOST_LOW)
			)
			return false;

		if (getVaporLoadingStatus(tower) == ITowerReport::Status::HIGH)
			return false;

		if (getLiquidLoadingStatus(tower) == ITowerReport::Status::HIGH)
			return false;

		if ((isHeavyKeyStatusLow(tower) || isHeavyKeyStatusAlmostLow(tower))
			&& config->getOverhead()->getExternalReflux()->getLevelControl()
			)
			return false;

		if ((lightKeyStatus == base->getEffectiveStatus(ITowerReport::Status::HIGH)
			|| lightKeyStatus == base->getEffectiveStatus(ITowerReport::Status::ALMOST_HIGH))
			&& base->getReboiler()->getLevelControl()
			)
			return false;

		return true;
	}

	bool IAlgorithm::lightsHiHi(ITower* tower){

		ITowerConfig* config = tower->getConfig();

		//IFeed* feed0 = config->getFeeds()->getFeed(0);   // using default feed0

		if (tower->getConfig()->getBottoms()->getComposition()->getLightKey().empty())  //AC CHECKME
			return false;

		//TODO: if (config->getType() == ITower::Type::AMINE_ABSORBER)
		//	return false;

		double lightKeyRange = tower->getReport()->getLightKey()->getRange();

		if (ITowerReport::Status::HIGH == config->getBottoms()->getEffectiveStatus(ITowerReport::Status::HIGH)
			&& lightKeyRange > RANGE_HIGH)
			return true;

		if (ITowerReport::Status::HIGH != config->getBottoms()->getEffectiveStatus(ITowerReport::Status::HIGH)
			&& lightKeyRange < RANGE_LOW)
			return true;

		return false;
	}

	bool IAlgorithm::heaviesHiHi(ITower* tower){

		ITowerConfig* config = tower->getConfig();

		//IFeed* feed0 = config->getFeeds()->getFeed(0);   // using default feed0

		if (tower->getConfig()->getBottoms()->getComposition()->getHeavyKey().empty())  //?AC CHECKME
			return false;

		//TODO: if (config->getType() == ITower::Type::AMINE_ABSORBER)
		//	return false;

		bool reversed = config->getOverhead()->isCompositionLogicReversed();

		double heavyKeyRange = tower->getReport()->getHeavyKey()->getRange();

		if (reversed == false && heavyKeyRange > RANGE_HIGH)
			return true;

		if (reversed == true && heavyKeyRange < RANGE_LOW)
			return true;

		return false;
	}

	bool IAlgorithm::isHeavyKeyStatusHigh(ITower* tower){
		ITowerConfig* config = tower->getConfig();
		ITowerReport* report = tower->getReport();
		return checkStatus(config->getOverhead(),
			report->getHeavyKey()->getStatus(),
			ITowerReport::Status::HIGH, ITowerReport::Status::LOW);
	}

	bool IAlgorithm::isHeavyKeyStatusAlmostHigh(ITower* tower){
		ITowerConfig* config = tower->getConfig();
		ITowerReport* report = tower->getReport();
		return checkStatus(config->getOverhead(),
			report->getHeavyKey()->getStatus(),
			ITowerReport::Status::ALMOST_HIGH, ITowerReport::Status::ALMOST_LOW);
	}

	bool IAlgorithm::isHeavyKeyStatusLow(ITower* tower){
		ITowerConfig* config = tower->getConfig();
		ITowerReport* report = tower->getReport();
		return checkStatus(config->getOverhead(),
			report->getHeavyKey()->getStatus(),
			ITowerReport::Status::LOW, ITowerReport::Status::ALMOST_HIGH);
	}

	bool IAlgorithm::isHeavyKeyStatusAlmostLow(ITower* tower){
		ITowerConfig* config = tower->getConfig();
		ITowerReport* report = tower->getReport();
		return checkStatus(config->getOverhead(),
			report->getHeavyKey()->getStatus(),
			ITowerReport::Status::ALMOST_LOW, ITowerReport::Status::HIGH);
	}

	ITowerReport::Status IAlgorithm::getLiquidLoadingStatus(ITower* tower){
		ITowerConfig* config = tower->getConfig();
		ITowerReport* report = tower->getReport();

		if (report->getDelta()->getStatus() == ITowerReport::Status::HIGH
			|| report->getDelta()->getStatus() == ITowerReport::Status::ALMOST_HIGH
			|| report->getReflux()->getStatus() == ITowerReport::Status::HIGH
			|| report->getFeed()->getStatus() == ITowerReport::Status::HIGH
			|| (config->getColumn()->isUsingOverheadKeyToDetermineTowerLoading() && isHeavyKeyStatusHigh(tower))) {
			return ITowerReport::Status::HIGH;
		}

		if (report->getDelta()->getStatus() == ITowerReport::Status::LOW
			|| report->getDelta()->getStatus() == ITowerReport::Status::ALMOST_LOW
			|| report->getReflux()->getStatus() == ITowerReport::Status::LOW
			|| report->getFeed()->getStatus() == ITowerReport::Status::LOW
			|| (config->getColumn()->isUsingOverheadKeyToDetermineTowerLoading() && isHeavyKeyStatusLow(tower))) {
			return ITowerReport::Status::LOW;
		}
		return ITowerReport::Status::OK;
	}

	ITowerReport::Status IAlgorithm::getVaporLoadingStatus(ITower* tower){
		ITowerConfig* config = tower->getConfig();
		ITowerReport* report = tower->getReport();

		if (report->getDelta()->getStatus() == ITowerReport::Status::HIGH
			|| report->getDelta()->getStatus() == ITowerReport::Status::ALMOST_HIGH
			|| report->getHeating()->getStatus() == ITowerReport::Status::HIGH
			|| (config->getColumn()->isUsingOverheadKeyToDetermineTowerLoading() && isHeavyKeyStatusHigh(tower))) {
			return ITowerReport::Status::OK;
		}

		if (report->getDelta()->getStatus() == ITowerReport::Status::LOW
			|| report->getDelta()->getStatus() == ITowerReport::Status::ALMOST_LOW
			|| report->getHeating()->getStatus() == ITowerReport::Status::LOW
			|| (config->getColumn()->isUsingOverheadKeyToDetermineTowerLoading() && isHeavyKeyStatusLow(tower))) {
			return ITowerReport::Status::OK;
		}

		return ITowerReport::Status::OK;
	}

	//---- private -----
	bool IAlgorithm::checkStatus(IHasComposition* composition, ITowerReport::Status observed, ITowerReport::Status actual, ITowerReport::Status reversed) {
		if (composition->isCompositionLogicReversed())
			return observed == reversed;
		return observed == actual;
	}

}//namespace