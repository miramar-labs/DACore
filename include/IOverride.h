//
//  IOverride.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/11/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IOverride_h
#define Distillation_Advisor_IOverride_h

#include "dacommon.h"

namespace dacore {

	typedef unsigned long OverrideId;

	class DACORE_API IOverride : public ISerialize {

		friend class IOverrides;

	public:
		virtual ~IOverride(){}

		enum PreventTarget { PRESSURE_INCREASE, PRESSURE_DECREASE, REFLUX_INCREASE, REFLUX_DECREASE, REBOIL_INCREASE, REBOIL_DECREASE };

		enum TripPointOperator { GREATER_THAN, LESS_THAN, EQUALS };

		virtual bool willTripFor(double value) = 0;

		virtual std::string getMessage(const std::string& method) = 0;

		virtual std::string getName() = 0;

		virtual void setTripPoint(double val) = 0;

		virtual double getTripPoint() = 0;

		virtual void setTripPointOp(TripPointOperator op) = 0;

		virtual TripPointOperator getTripPointOp() = 0;

		virtual void setPreventTarget(PreventTarget op) = 0;

		virtual PreventTarget getPreventTarget() = 0;

		virtual bool isEnabled() = 0;

		virtual void setEnabled(bool bEnabled) = 0;

		virtual OverrideId		getId() = 0;

	};

}

extern "C" DACORE_API const char* DACORE_APIENTRY PreventTargetStr(dacore::IOverride::PreventTarget t);

#endif
