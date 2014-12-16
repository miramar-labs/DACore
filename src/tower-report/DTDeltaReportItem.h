//
//  DTDeltaReportItem.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 8/9/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_DTDeltaReportItem_h
#define Distillation_Advisor_DTDeltaReportItem_h

#include "stdafx.h"

#include "ReportItem.h"

namespace dacore {

	class DTDeltaReportItem : public ReportItem {

	public:
		DTDeltaReportItem(ITowerConfig* config, ITowerData* data)
			:ReportItem(config, data){}

		virtual ~DTDeltaReportItem(){}

		const double HIGH_RANGE_LIMIT = 0.975;
		const double LOW_RANGE_LIMIT = 0.025;
		const double RANGE_LIMIT_BUFFER = 0.025;

		virtual double getMin(){
			mMin = mConfig->getControlLimits()->getDeltaInstrumentMin();
			return mMin;
		}

		virtual double getMax(){
			mMax = mConfig->getControlLimits()->getDeltaInstrumentMax();
			return mMax;
		}

		virtual double getCurrent(){
			if (mData->getSecondaryInstruments() == nullptr) {
				mCurrent = mData->getPrimaryInstruments()->getTowerDeltaPressureOrTemperature();
			}
			else {
				mCurrent = mData->getPrimaryInstruments()->getTowerDeltaPressureOrTemperature()
					- mData->getSecondaryInstruments()->getTowerDeltaPressureOrTemperature();
			}
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
