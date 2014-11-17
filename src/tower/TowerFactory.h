//
//  TowerFactory.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/9/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_TowerFactory_h
#define Distillation_Advisor_TowerFactory_h

#include "stdafx.h"

#include "DistillationTower.h"

#include "TowerConfigFactory.h"
#include "TowerDataFactory.h"
#include "TowerReportFactory.h"

namespace dacore {

	class TowerFactory {

		friend class IManager;
		friend class UnitTests;
		friend class AlgorithmUnitTests;

	public:

		static ITower* create(ITower::Type type = ITower::Type::DISTILLATION, TowerId id = 0){
			switch (type){
			case ITower::Type::DISTILLATION:
				return TowerFactory::createDT(id);
#ifdef UNIT_TESTING
			case ITower::Type::DTPRIME:
				return TowerFactory::createDTPrime(id);
#endif
			default:
				return nullptr;
			}
		}

		//helpers:
		static ITower* createDT(TowerId id = 0){

			ITower* tower = new DistillationTower(id);

			ITowerData*  data = TowerDataFactory::create();
			tower->setData(data);

			ITowerConfig* config = TowerConfigFactory::create();
			tower->setConfig(config);

			ITowerReport*  report = TowerReportFactory::create(config, data);
			tower->setReport(report);

			return tower;
		}

		static ITower* createDTPrime(TowerId id = 0){

			ITower* tower = new DistillationTower(id);

			ITowerData*  data = TowerDataFactory::createDTPrime();
			tower->setData(data);

			ITowerConfig* config = TowerConfigFactory::createDTPrime();
			tower->setConfig(config);

			ITowerReport*  report = TowerReportFactory::create(config, data);
			tower->setReport(report);

			return tower;
		}

	};

}

#endif
