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
		virtual bool setHeavyKeyMin(double val) = 0;

		virtual double getHeavyKeyMax() = 0;
		virtual bool setHeavyKeyMax(double val) = 0;

		virtual double getLightKeyMin() = 0;
		virtual bool setLightKeyMin(double val) = 0;

		virtual double getLightKeyMax() = 0;
		virtual bool setLightKeyMax(double val) = 0;

		virtual double getDeltaInstrumentMin() = 0;
		virtual bool setDeltaInstrumentMin(double val) = 0;

		virtual double getDeltaInstrumentMax() = 0;
		virtual bool setDeltaInstrumentMax(double val) = 0;

		virtual double getRefluxMin() = 0;
		virtual bool setRefluxMin(double val) = 0;

		virtual double getRefluxMax() = 0;
		virtual bool setRefluxMax(double val) = 0;

		virtual double getFeedMin() = 0;
		virtual bool setFeedMin(double val) = 0;

		virtual double getFeedMax() = 0;
		virtual bool setFeedMax(double val) = 0;

		virtual double getHeatingMediumFlowMin() = 0;
		virtual bool setHeatingMediumFlowMin(double val) = 0;

		virtual double getHeatingMediumFlowMax() = 0;
		virtual bool setHeatingMediumFlowMax(double val) = 0;

		virtual double getOperatingPressureMin() = 0;
		virtual bool setOperatingPressureMin(double val) = 0;

		virtual double getOperatingPressureMax() = 0;
		virtual bool setOperatingPressureMax(double val) = 0;

		virtual double getPressureControllerMin() = 0;
		virtual bool setPressureControllerMin(double val) = 0;

		virtual double getPressureControllerMax() = 0;
		virtual bool setPressureControllerMax(double val) = 0;

		enum class RefluxLimitType {
			REFLUX_FEED, REFLUX
		};

		virtual const RefluxLimitType& getRefluxLimitType() = 0;
		virtual void setRefluxLimitType(const RefluxLimitType& type) = 0;

	};

}

#endif
