//
//  IInstrumentsData.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/20/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IInstrumentsData_h
#define Distillation_Advisor_IInstrumentsData_h

#include "dacommon.h"

namespace dacore {

	class DACORE_API IInstrumentsData : public ISerialize {	//TODO: CHECKME - do we really need to serialize this?

	public:
		virtual ~IInstrumentsData(){}

		virtual double getHeavyKeyCurrent() = 0;
		virtual void setHeavyKeyCurrent(double val) = 0;

		virtual double getHeavyKeyMinus20() = 0;
		virtual void setHeavyKeyMinus20(double val) = 0;

		virtual double getHeavyKeyMinus40() = 0;
		virtual void setHeavyKeyMinus40(double val) = 0;

		virtual double getLightKeyCurrent() = 0;
		virtual void setLightKeyCurrent(double val) = 0;

		virtual double getLightKeyMinus20() = 0;
		virtual void setLightKeyMinus20(double val) = 0;

		virtual double getLightKeyMinus40() = 0;
		virtual void setLightKeyMinus40(double val) = 0;

		virtual double getTowerDeltaPressureOrTemperature() = 0;
		virtual void setTowerDeltaPressureOrTemperature(double val) = 0;

	};

}

#endif
