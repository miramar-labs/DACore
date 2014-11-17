//
//  IAlgorithm.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 6/30/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IAlgorithm_h
#define Distillation_Advisor_IAlgorithm_h

#include "stdafx.h"

#include "ITower.h"
#include "ITowerReport.h"
#include "ITowerConfig.h"
#include "IAdvice.h"

namespace dacore {

	class IHasComposition;

	class IAlgorithm {

	public:
		virtual ~IAlgorithm(){}

		virtual bool run(ITower* tower, IAdvice* advice){
			switch (tower->getConfig()->getType()){
			case ITower::Type::DISTILLATION:
				return doAlgorithm(tower, advice);
			//case ITower::Type::AMINE_ABSORBER:
			//	break;//TODO..
			default:
				break;
			}
			return true;
		}

	protected:

		virtual bool doAlgorithm(ITower* tower, IAdvice* advice) = 0;

	protected:

		bool impur(ITower* tower);

		bool lightsHiHi(ITower* tower);

		bool heaviesHiHi(ITower* tower);

		bool isHeavyKeyStatusHigh(ITower* tower);

		bool isHeavyKeyStatusAlmostHigh(ITower* tower);

		bool isHeavyKeyStatusLow(ITower* tower);

		bool isHeavyKeyStatusAlmostLow(ITower* tower);

		ITowerReport::Status getLiquidLoadingStatus(ITower* tower);

		ITowerReport::Status getVaporLoadingStatus(ITower* tower);

		std::string getMessage(ITower* tower, IAdvice::MessageType type);

	private:
		bool checkStatus(IHasComposition* composition,
			ITowerReport::Status observed,
			ITowerReport::Status actual,
			ITowerReport::Status reversed);
	};

}

#endif
