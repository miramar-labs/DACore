//
//  IControlLimits.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/20/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IControlLimits_h
#define Distillation_Advisor_IControlLimits_h

#include "dacommon.h"

namespace dacore {

	class DACORE_API IControlLimits : public ISerialize {

	public:
		virtual ~IControlLimits(){}

		virtual double getHeavyKeyMin() = 0;
		virtual void setHeavyKeyMin(double val) = 0;

		virtual double getHeavyKeyMax() = 0;
		virtual void setHeavyKeyMax(double val) = 0;

		virtual double getLightKeyMin() = 0;
		virtual void setLightKeyMin(double val) = 0;

		virtual double getLightKeyMax() = 0;
		virtual void setLightKeyMax(double val) = 0;

		virtual double getDeltaInstrumentMin() = 0;
		virtual void setDeltaInstrumentMin(double val) = 0;

		virtual double getDeltaInstrumentMax() = 0;
		virtual void setDeltaInstrumentMax(double val) = 0;

		virtual double getRefluxMin() = 0;
		virtual void setRefluxMin(double val) = 0;

		virtual double getRefluxMax() = 0;
		virtual void setRefluxMax(double val) = 0;

		virtual double getFeedMin() = 0;
		virtual void setFeedMin(double val) = 0;

		virtual double getFeedMax() = 0;
		virtual void setFeedMax(double val) = 0;

		virtual double getHeatingMediumFlowMin() = 0;
		virtual void setHeatingMediumFlowMin(double val) = 0;

		virtual double getHeatingMediumFlowMax() = 0;
		virtual void setHeatingMediumFlowMax(double val) = 0;

		virtual double getOperatingPressureMin() = 0;
		virtual void setOperatingPressureMin(double val) = 0;

		virtual double getOperatingPressureMax() = 0;
		virtual void setOperatingPressureMax(double val) = 0;

		virtual double getPressureControllerMin() = 0;
		virtual void setPressureControllerMin(double val) = 0;

		virtual double getPressureControllerMax() = 0;
		virtual void setPressureControllerMax(double val) = 0;

		enum class RefluxLimitType {
			REFLUX_FEED, REFLUX
		};

		virtual const RefluxLimitType& getRefluxLimitType() = 0;
		virtual void setRefluxLimitType(const RefluxLimitType& type) = 0;

	};

}

#endif
