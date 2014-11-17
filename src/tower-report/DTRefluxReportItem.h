//
//  DTRefluxReportItem.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 8/9/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_DTRefluxReportItem_h
#define Distillation_Advisor_DTRefluxReportItem_h

#include "stdafx.h"

#include "ReportItem.h"

namespace dacore {

	class DTRefluxReportItem : public ReportItem {

	public:
		DTRefluxReportItem(ITowerConfig* config, ITowerData* data)
			:ReportItem(config, data){}

		virtual ~DTRefluxReportItem(){}

		const double HIGH_RANGE_LIMIT = 0.995;
		const double LOW_RANGE_LIMIT = 0.005;
		const double RANGE_LIMIT_BUFFER = 0.02;

		virtual double getMin(){
			mMin = mConfig->getControlLimits()->getRefluxMin();
			return mMin;
		}

		virtual double getMax(){
			mMax = mConfig->getControlLimits()->getRefluxMax();
			return mMax;
		}

		virtual double getCurrent(){

			if (!mConfig->getOverhead()->getExternalReflux()->getConfigured()) {
				mCurrent = 0.0; // tower has no reflux...
				return mCurrent;
			}

			double secondFeedFlowFactor = 0.0, thirdFeedFlowFactor = 0.0, refluxFactor = 0.0;

			if (mConfig->getOverhead()->getExternalReflux()->getFlowFactor() != 0)  //CHECKME was NULL
				refluxFactor = mConfig->getOverhead()->getExternalReflux()->getFlowFactor();

			//TODO - extend this code to handle N feeds

			IFeeds* feeds = mConfig->getFeeds();
			if (feeds){
				// get additional feed flow factors...  TODO
			}

			if (mConfig->getControlLimits()->getRefluxLimitType() == IControlLimits::RefluxLimitType::REFLUX_FEED) {
				mCurrent = mData->getReflux()
					* refluxFactor
					/ (mData->getFeedFlow1()
					//TODO + (mData->getFeedFlow2() * secondFeedFlowFactor)
					//TODO + (mData->getFeedFlow3() * thirdFeedFlowFactor)
					// ... N
					);
			}
			else {
				mCurrent = mData->getReflux() * refluxFactor;

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
			if (getMin() == 0 || getMax() < 0)
				mRange = 0;
			else
				mRange = (getCurrent() - getMin()) / (getMax() - getMin());
			return mRange;
		}
	};

}

#endif
