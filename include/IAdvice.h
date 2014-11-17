//
//  IAdvice.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 6/30/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IAdvice_h
#define Distillation_Advisor_IAdvice_h

#include "dacommon.h"

namespace dacore {

	class DACORE_API IAdvice {

	public:

		virtual ~IAdvice(){}

		enum MessageType {
			INCREASE_REFLUX,
			DECREASE_REFLUX,
			INCREASE_REBOIL,
			DECREASE_REBOIL,
			DECREASE_BOTH_REBOIL_AND_REFLUX,
			INCREASE_BOTH_REBOIL_AND_REFLUX,
			INCREASE_PRESSURE,
			DECREASE_PRESSURE
		};

		virtual MessageType     getPrimaryMessageType() = 0;
		virtual void            setPrimaryMessageType(MessageType type) = 0;

		virtual std::string     getPrimaryMessage() = 0;
		virtual void            setPrimaryMessage(const std::string& msg) = 0;

		virtual std::string     getSecondaryMessage() = 0;

		virtual std::string     getTertiaryMessage() = 0;

		virtual int             getTowerId() = 0;

		virtual std::string     getAlgorithmId() = 0;
		virtual void            setAlgorithmId(const std::string& id) = 0;

		enum Severity {
			RED,
			YELLOW,
			GREEN,
			CLEAR
		};

		virtual Severity        getSeverity() = 0;
		virtual void            setSeverity(Severity s) = 0;

		virtual std::string     getTimestamp() = 0;
		virtual void            setTimestamp() = 0;

	};

}
#endif
