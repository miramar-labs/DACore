//
//  HistorianFactory.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/27/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_HistorianFactory_h
#define Distillation_Advisor_HistorianFactory_h

#include "stdafx.h"

#include "HistorianBase.h"
#include "Towers.h"

#include "IHistorian.h"

namespace dacore {

	class HistorianFactory {

		friend class Manager;
		friend class UnitTests;
		friend class AlgorithmUnitTests;

	private:

		static IHistorian* create(IHistorian::Type type = IHistorian::Type::PI){
			switch (type){
			case IHistorian::Type::PI:
				return HistorianFactory::createPI();
			default:
				return nullptr;
			}
		}

		//helpers:
		static IHistorian* createPI(){

			IHistorian* historian = new HistorianBase();     //TODO - no subclasses yet, use base for now !!

			ITowers* towers = new Towers();
			historian->setTowers(towers);

			return historian;
		}

	};

}
#endif
