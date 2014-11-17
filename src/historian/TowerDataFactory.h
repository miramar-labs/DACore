//
//  TowerDataFactory.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/19/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_TowerDataFactory_h
#define Distillation_Advisor_TowerDataFactory_h

#include "stdafx.h"

#include "OverridesData.h"
#include "TowerData.h"
#include "InstrumentsData.h"
#include "LabResultsData.h"

namespace dacore{

	class TowerDataFactory {

		friend class TowerFactory;

	private:

		static ITowerData* create(){
			return TowerDataFactory::createSkeleton();
		}

		static ITowerData* createDTPrime() {

			ITowerData* d = TowerDataFactory::create();

			d->setPrimaryInstruments(TowerDataFactory::createInstrumentsData(96.15, 95.68, 96.35, 2.79, 2.68, 2.65, 2.10));
			d->setReflux(146000.0);
			d->setFeedFlow1(277234.0);
			d->setHeatingMediumFlow1(45060.0);
			d->setOperatingPressure(6.0);
			d->setOutputOnPIC(77.0);

			d->setSecondaryInstruments(createInstrumentsData()); //TODO

			d->setLabResults(createLabResultsData());   //TODO

			IOverridesData* od = new OverridesData();
			od->setPreventsPressureDecrease(16.00);
			d->setOverrides(od);

			return d;
		}

		//helpers:
		static IOverridesData* createOverrides(double prevDecInReboil = 0.0,
			double prevIncInReboil = 0.0,
			double prevDecInReflux = 0.0,
			double prevIncInReflux = 0.0){
			IOverridesData* item = new OverridesData();
			item->setPreventsDecreaseInReboil(prevDecInReboil);
			item->setPreventsIncreaseInReboil(prevIncInReboil);
			item->setPreventsDecreaseInReflux(prevDecInReflux);
			item->setPreventsIncreaseInReflux(prevIncInReflux);
			return item;
		}

		static IInstrumentsData* createInstrumentsData(double hkCurrent = 0.0,
			double hkMinus20 = 0.0,
			double hkMinus40 = 0.0,
			double lkCurrent = 0.0,
			double lkMinus20 = 0.0,
			double lkMinus40 = 0.0,
			double delta = 0.0
			){
			IInstrumentsData* item = new InstrumentsData();
			item->setHeavyKeyCurrent(hkCurrent);
			item->setHeavyKeyMinus20(hkMinus20);
			item->setHeavyKeyMinus40(hkMinus40);
			item->setLightKeyCurrent(lkCurrent);
			item->setLightKeyMinus20(lkMinus20);
			item->setLightKeyMinus40(lkMinus40);
			item->setTowerDeltaPressureOrTemperature(delta);
			return item;
		}

		static ILabResultsData* createLabResultsData(double hk = 0.0,
			double lk = 0.0
			){
			ILabResultsData* item = new LabResultsData();

			item->setHeavyKeyLabResult(hk);
			item->setLightKeyLabResult(lk);

			return item;
		}


		static ITowerData* createSkeleton(){

			ITowerData* data = new TowerData();

			data->setOverrides(createOverrides());

			data->setPrimaryInstruments(createInstrumentsData());

			data->setSecondaryInstruments(createInstrumentsData()); //TODO

			data->setLabResults(createLabResultsData());   //TODO

			return data;
		}

	};

}

#endif


