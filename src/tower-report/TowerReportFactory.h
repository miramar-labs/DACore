//
//  TowerReportFactory.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/19/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_TowerReportFactory_h
#define Distillation_Advisor_TowerReportFactory_h

#include "stdafx.h"

#include "TowerReport.h"

namespace dacore {

	class TowerReportFactory {

		friend class TowerFactory;

	private:

		static ITowerReport* create(ITowerConfig* config, ITowerData* data){
			return TowerReportFactory::createDefault(config, data);
		}

		//helpers:
		static ITowerReport* createDefault(ITowerConfig* config, ITowerData* data){
			return new TowerReport(config, data);
		}

	};

}

#endif
