//
//  DTOperatingPressureReportItem.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 8/9/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_DTOperatingPressureReportItem_h
#define Distillation_Advisor_DTOperatingPressureReportItem_h

#include "stdafx.h"

#include "ReportItem.h"

namespace dacore {

	class DTOperatingPressureReportItem : public ReportItem {

	public:
		DTOperatingPressureReportItem(ITowerConfig* config, ITowerData* data)
			:ReportItem(config, data){}

		virtual ~DTOperatingPressureReportItem(){}

		const double HIGH_RANGE_LIMIT = 0.995;
		const double LOW_RANGE_LIMIT = 0.005;
		const double RANGE_LIMIT_BUFFER = 0.02;

		virtual double getMin(){
			mMin = mConfig->getControlLimits()->getOperatingPressureMin();
			return mMin;
		}

		virtual double getMax(){
			mMax = mConfig->getControlLimits()->getOperatingPressureMax();
			return mMax;
		}

		virtual double getCurrent(){
			mCurrent = mData->getOperatingPressure();
			return mCurrent;
		}

		virtual double getPrior20(){ return mPrior20; }//NA

		virtual double getPrior40(){ return mPrior40; }//NA

		virtual ITowerReport::Status getStatus(){
			if (getRange() == 0) {
				mStatus = ITowerReport::Status::OK;
				return mStatus;
			}

			if (getRange() > HIGH_RANGE_LIMIT) {
				mStatus = ITowerReport::Status::HIGH;
				return mStatus;
			}

			if (getRange() > HIGH_RANGE_LIMIT - RANGE_LIMIT_BUFFER) {
				mStatus = ITowerReport::Status::ALMOST_HIGH;
				return mStatus;
			}

			if (getRange() < LOW_RANGE_LIMIT) {
				mStatus = ITowerReport::Status::LOW;
				return mStatus;
			}

			if (getRange() < LOW_RANGE_LIMIT + RANGE_LIMIT_BUFFER) {
				mStatus = ITowerReport::Status::ALMOST_LOW;
				return mStatus;
			}

			mStatus = ITowerReport::Status::OK;

			return mStatus;
		}

		virtual double getNext20(){ return mNext20; }//NA

		virtual double getNext40(){ return mNext40; }//NA

		virtual double getRange(){
			if (getMin() == 0 || getMax() < 0 || (getMin() == getMax()))
				mRange = 0;
			else
				mRange = (getCurrent() - getMin()) / (getMax() - getMin());
			return mRange;
		}

	};

}

#endif
