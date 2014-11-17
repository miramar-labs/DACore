//
//  Advice.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 6/30/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef __Distillation_Advisor__Advice__
#define __Distillation_Advisor__Advice__

#include "stdafx.h"

#include "IAdvice.h"

namespace dacore {

	class Advice : public IAdvice {

	public:

		Advice()
			:mTimestamp("bad advice..."){}
		virtual ~Advice(){}

		virtual MessageType         getPrimaryMessageType(){ return mType; }
		virtual void                setPrimaryMessageType(MessageType type){ mType = type; }

		virtual std::string         getPrimaryMessage(){ return mMsg1; }
		virtual void                setPrimaryMessage(const std::string& msg){ mMsg1 = msg; }

		virtual std::string         getSecondaryMessage(){ return mMsg2; }

		virtual std::string         getTertiaryMessage(){ return mMsg3; }

		virtual int                 getTowerId(){ return mTowerId; }

		virtual std::string         getAlgorithmId(){ return mAlgorithmId; }
		virtual void                setAlgorithmId(const std::string& id){ mAlgorithmId = id; }

		virtual Severity            getSeverity(){ return mSeverity; }
		virtual void                setSeverity(Severity s){ mSeverity = s; }

		virtual std::string         getTimestamp(){ return mTimestamp; }

	private:
		virtual void                setTimestamp(){
			boost::local_time::local_date_time currentTime(boost::posix_time::second_clock::local_time(),
				boost::local_time::time_zone_ptr());
			std::stringstream ss;
			ss << currentTime.local_time();
			mTimestamp = ss.str();
		}

	private:
		MessageType             mType;
		std::string             mMsg1;
		std::string             mMsg2;
		std::string             mMsg3;
		int                     mTowerId;
		std::string             mAlgorithmId;
		Severity                mSeverity;
		std::string             mTimestamp;
	};

}

#endif /* defined(__Distillation_Advisor__Advice__) */
