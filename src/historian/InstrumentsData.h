//
//  InstrumentsData.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/20/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_InstrumentsData_h
#define Distillation_Advisor_InstrumentsData_h

#include "stdafx.h"

#include "IInstrumentsData.h"

namespace dacore {

	class InstrumentsData : public IInstrumentsData {

	public:
		virtual ~InstrumentsData(){}

		virtual double getHeavyKeyCurrent(){ return heavyKeyCurrent; }
		virtual void setHeavyKeyCurrent(double val){ heavyKeyCurrent = val; }

		virtual double getHeavyKeyMinus20(){ return heavyKeyMinus20; }
		virtual void setHeavyKeyMinus20(double val){ heavyKeyMinus20 = val; }

		virtual double getHeavyKeyMinus40(){ return heavyKeyMinus40; }
		virtual void setHeavyKeyMinus40(double val){ heavyKeyMinus40 = val; }

		virtual double getLightKeyCurrent(){ return lightKeyCurrent; }
		virtual void setLightKeyCurrent(double val){ lightKeyCurrent = val; }

		virtual double getLightKeyMinus20(){ return lightKeyMinus20; }
		virtual void setLightKeyMinus20(double val){ lightKeyMinus20 = val; }

		virtual double getLightKeyMinus40(){ return lightKeyMinus40; }
		virtual void setLightKeyMinus40(double val){ lightKeyMinus40 = val; }

		virtual double getTowerDeltaPressureOrTemperature(){ return towerDeltaPressureOrTemperature; }
		virtual void setTowerDeltaPressureOrTemperature(double val){ towerDeltaPressureOrTemperature = val; }

	protected:
		double heavyKeyCurrent;
		double heavyKeyMinus20;
		double heavyKeyMinus40;
		double lightKeyCurrent;
		double lightKeyMinus20;
		double lightKeyMinus40;
		double towerDeltaPressureOrTemperature;

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			pt.put("InstrumentsData.hkCurrent", heavyKeyCurrent);
			pt.put("InstrumentsData.hkMinus20", heavyKeyMinus20);
			pt.put("InstrumentsData.hkMinus40", heavyKeyMinus40);
			pt.put("InstrumentsData.lkCurrent", lightKeyCurrent);
			pt.put("InstrumentsData.lkMinus20", lightKeyMinus20);
			pt.put("InstrumentsData.lkMinus40", lightKeyMinus40);
			pt.put("InstrumentsData.deltaPorT", towerDeltaPressureOrTemperature);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			heavyKeyCurrent = pt.get<double>("InstrumentsData.hkCurrent");
			heavyKeyMinus20 = pt.get<double>("InstrumentsData.hkMinus20");
			heavyKeyMinus40 = pt.get<double>("InstrumentsData.hkMinus40");
			lightKeyCurrent = pt.get<double>("InstrumentsData.lkCurrent");
			lightKeyMinus20 = pt.get<double>("InstrumentsData.lkMinus20");
			lightKeyMinus40 = pt.get<double>("InstrumentsData.lkMinus40");
			towerDeltaPressureOrTemperature = pt.get<double>("InstrumentsData.deltaPorT");

		}
	};

}

#endif
