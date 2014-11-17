//
//  IExternalReflux.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IExternalReflux_h
#define Distillation_Advisor_IExternalReflux_h

#include "dacommon.h"

namespace dacore {

	class DACORE_API IExternalReflux : public ISerialize {

	public:
		virtual ~IExternalReflux(){}

		enum IncreaseMethod { REFLUX_INC_METHOD_NOT_SET, DEC_DIST_FLOW, INC_REFLUX_FLOW, DEC_OH_TEMP, DEC_DF_RATIO, DEC_RF_RATIO, REFLUX_INC_METHOD_OTHER };

		enum DecreaseMethod { REFLUX_DEC_METHOD_NOT_SET, INC_DIST_FLOW, DEC_REFLUX_FLOW, INC_OH_TEMP, INC_DF_RATIO, INC_RF_RATIO, REFLUX_DEC_METHOD_OTHER };

		virtual bool getLevelControl() = 0;
		virtual void setLevelControl(bool val) = 0;

		virtual bool getConfigured() = 0;
		virtual void setConfigured(bool val) = 0;

		virtual IncreaseMethod getIncreaseMethod() = 0;
		virtual void setIncreaseMethod(const IncreaseMethod& method) = 0;

		virtual std::string getIncreaseMethodOther() = 0;
		virtual void setIncreaseMethodOther(const std::string& other) = 0;

		virtual DecreaseMethod getDecreaseMethod() = 0;
		virtual void setDecreaseMethod(const DecreaseMethod& method) = 0;

		virtual std::string getDecreaseMethodOther() = 0;
		virtual void setDecreaseMethodOther(const std::string& other) = 0;

		virtual std::string getFlowTag() = 0;
		virtual void setFlowTag(const std::string& tag) = 0;

		virtual std::string getFlowUnit() = 0;
		virtual void setFlowUnit(const std::string& unit) = 0;

		virtual double getFlowFactor() = 0;
		virtual void setFlowFactor(double factor) = 0;

	};

}
	extern "C" DACORE_API const char* DACORE_APIENTRY RefluxIncMethodStr(dacore::IExternalReflux::IncreaseMethod m);
	extern "C" DACORE_API const char* DACORE_APIENTRY RefluxDecMethodStr(dacore::IExternalReflux::DecreaseMethod m);

#endif
