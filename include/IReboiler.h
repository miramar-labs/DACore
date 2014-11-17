//
//  IReboiler.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IReboiler_h
#define Distillation_Advisor_IReboiler_h

#include "dacommon.h"

namespace dacore {

	class DACORE_API IReboiler : public ISerialize {

	public:
		virtual ~IReboiler(){}

		enum IncreaseMethod { REBOIL_INC_METHOD_NOT_SET, INC_BASE_TEMP, DEC_BASE_FLOW, INC_HM_FEED_RATIO, INC_HM_FLOW, DEC_BOTTOMS_FEED_RATIO, REBOIL_INC_METHOD_OTHER };//TODO check enum issue

		enum DecreaseMethod { REBOIL_DEC_METHOD_NOT_SET, DEC_BASE_TEMP, INC_BASE_FLOW, DEC_HM_FEED_RATIO, DEC_HM_FLOW, INC_BOTTOMS_FEED_RATIO, REBOIL_DEC_METHOD_OTHER };

		virtual bool getLevelControl() = 0;
		virtual void setLevelConrol(bool val) = 0;

		virtual IncreaseMethod getIncreaseMethod() = 0;
		virtual void setIncreaseMethod(const IncreaseMethod& method) = 0;

		virtual std::string getIncreaseMethodOther() = 0;
		virtual void setIncreaseMethodOther(const std::string& other) = 0;

		virtual DecreaseMethod getDecreaseMethod() = 0;
		virtual void setDecreaseMethod(const DecreaseMethod& method) = 0;

		virtual std::string getDecreaseMethodOther() = 0;
		virtual void setDecreaseMethodOther(const std::string& other) = 0;
	};

}//namespace

extern "C" DACORE_API const char* DACORE_APIENTRY ReboilerIncMethodStr(dacore::IReboiler::IncreaseMethod m);
extern "C" DACORE_API const char* DACORE_APIENTRY ReboilerDecMethodStr(dacore::IReboiler::DecreaseMethod m);

#endif
