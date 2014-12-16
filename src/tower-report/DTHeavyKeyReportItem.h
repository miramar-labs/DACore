//
//  DTHeavyKeyReportItem.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 8/9/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_DTHeavyKeyReportItem_h
#define Distillation_Advisor_DTHeavyKeyReportItem_h

#include "stdafx.h"

#include "ReportItem.h"

namespace dacore {

	class DTHeavyKeyReportItem : public ReportItem {

	public:
		DTHeavyKeyReportItem(ITowerConfig* config, ITowerData* data)
			:ReportItem(config, data){
			isManualInput = config->getOverhead()->getComposition()->isManualLab();
		}

		virtual ~DTHeavyKeyReportItem(){}

		virtual double getMin(){
			mMin = mConfig->getControlLimits()->getHeavyKeyMin();
			return mMin;
		}

		virtual double getMax(){
			mMax = mConfig->getControlLimits()->getHeavyKeyMax();
			return mMax;
		}

		virtual double getCurrent(){
			if (isManualInput) {
				if (mData->getLabResults() == nullptr)
					mCurrent = 0.0;
				else
					mCurrent = mData->getLabResults()->getHeavyKeyLabResult();
			}
			else if (mData->getSecondaryInstruments() == nullptr) {
				mCurrent = mData->getPrimaryInstruments()->getHeavyKeyCurrent();
			}
			else {
				mCurrent = mData->getPrimaryInstruments()->getHeavyKeyCurrent()
					- mData->getSecondaryInstruments()->getHeavyKeyCurrent();
			}
			return mCurrent;
		}

		virtual double getPrior20(){
			if (mConfig->getOverhead()->getComposition()->getMonitorMethod() == IComposition::MonitorMethod::LAB_RESULT)
				mPrior20 = 0.0; //CHECKME
			else
				mPrior20 = mData->getPrimaryInstruments()->getHeavyKeyMinus20();
			return mPrior20;
		}

		virtual double getPrior40(){
			if (mConfig->getOverhead()->getComposition()->getMonitorMethod() == IComposition::MonitorMethod::LAB_RESULT)
				mPrior40 = 0.0; //CHECKME
			else
				mPrior40 = mData->getPrimaryInstruments()->getHeavyKeyMinus40();
			return mPrior40;
		}

		virtual ITowerReport::Status getStatus(){
			if (getRange() == 0) {
				mStatus = ITowerReport::Status::OK;
				return mStatus;
			}

			if (getRange() > getHighRangeLimit()) {
				mStatus = ITowerReport::Status::HIGH;
				return mStatus;
			}

			if (getRange() > getHighRangeLimit() - 0.1) {
				mStatus = ITowerReport::Status::ALMOST_HIGH;
				return mStatus;
			}

			if (getRange() < getLowRangeLimit()) {
				mStatus = ITowerReport::Status::LOW;
				return mStatus;
			}

			if (getRange() < getLowRangeLimit() + 0.1) {
				mStatus = ITowerReport::Status::ALMOST_LOW;
				return mStatus;
			}

			if (!mConfig->getOverhead()->isCompositionLogicReversed()) {
				if (getPrior40() != 0 && getCurrentOrProjected() > getPrior40()
					&& getRange() > 0.65) {
					mStatus = ITowerReport::Status::ALMOST_HIGH;
					return mStatus;
				}
			}

			if (mConfig->getOverhead()->isCompositionLogicReversed()) {
				if ((getPrior40() != 0 && getCurrentOrProjected() < getPrior40())
					|| getPrior20() == 0) {
					mStatus = ITowerReport::Status::ALMOST_LOW;
					return mStatus;
				}
			}

			mStatus = ITowerReport::Status::OK;

			return mStatus;
		}

		virtual double getNext20(){ mNext20 = generateNext(20); return mNext20; }

		virtual double getNext40(){ mNext40 = generateNext(40); return mNext40; }

		virtual double getRange(){
			if (getMin() < 0 || getMax() < 0 || (getMin() == getMax()))
				mRange = 0;
			else
				mRange = (getCurrentOrProjected() - getMin()) / (getMax() - getMin());
			return mRange;
		}

	private:

		bool isManualInput;

		double getHighRangeLimit() {
			if (mConfig->hasAbsoluteControlOfOH()
				&& mConfig->getOverhead()->getComposition()->isManipulatedSetPoint())
				return 0.65;
			return 0.9;
		}

		double getLowRangeLimit() {
			if (mConfig->isBaseControlledAt10to90Percent())
				return 0.1;

			if (getHighRangeLimit() == 0.65)
				return 0.35;

			if (mConfig->getOverhead()->getComposition()->isManipulatedSetPoint()
				&& getHighRangeLimit() == 0.9)
				return 0.6;

			return 0.1;
		}

		/**
		 * Corresponds to A!$W$108 in DM. Returns either heavyKeyCurrent or
		 * projected, depending on conditions.
		 */
		double getCurrentOrProjected() {
			if (mConfig->getOverhead()->getComposition()->isManipulatedSetPoint()
				|| mConfig->getOverhead()->getComposition()->getMonitorMethod() == IComposition::MonitorMethod::LAB_RESULT)
				return getCurrent();

			switch (mConfig->getColumn()->getForecastingTimeline()) {
			case IColumn::ForecastingTimeline::FORTY_MINUTE:
				return getNext40();
			case IColumn::ForecastingTimeline::TWENTY_MINUTE:
				return getNext20();
			default:
				break;
			}
			return getCurrent();
		}
	};

}
#endif

