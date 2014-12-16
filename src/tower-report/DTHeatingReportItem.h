//
//  DTHeatingReportItem.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 8/9/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_DTHeatingReportItem_h
#define Distillation_Advisor_DTHeatingReportItem_h

#include "stdafx.h"

#include "ReportItem.h"

namespace dacore {

	class DTHeatingReportItem : public ReportItem {

	public:
		DTHeatingReportItem(ITowerConfig* config, ITowerData* data)
			:ReportItem(config, data){}

		virtual ~DTHeatingReportItem(){}

		const double HIGH_RANGE_LIMIT = 0.995;
		const double LOW_RANGE_LIMIT = 0.005;
		const double RANGE_LIMIT_BUFFER = 0.02;

		virtual double getMin(){
			mMin = mConfig->getControlLimits()->getHeatingMediumFlowMin();
			return mMin;
		}

		virtual double getMax(){
			mMax = mConfig->getControlLimits()->getHeatingMediumFlowMax();
			return mMax;
		}

		virtual double getCurrent(){

			//TODO rework this for N feeds - quite a bit more to do here

			double flowFactors[] = { 1.0, 0.0, 0.0 };

			IFeeds* hmfeeds = mConfig->getBottoms()->getHeatingMediumFeeds();

			// calculate total energy input
			if (mConfig->getBottoms()->getHeatingMedium() == Bottoms::HeatingMedium::OTHER) {

				std::vector<FeedId> fs;
				hmfeeds->enumerate(fs);
				std::vector<FeedId>::iterator it;
				for (it = fs.begin(); it != fs.end(); it++){

					std::string unit = hmfeeds->get(*it)->getEngUnit();//TODO .toUpperCase(Locale.US);

					/*TODO
					 if (unit.empty()){
					 flowFactors[i] = 0.0;
					 continue;
					 }

					 double timeComponent;
					 if (unit.endsWith("M"))
					 timeComponent = 60;
					 else if (unit.endsWith("H"))
					 timeComponent = 1.0;
					 else
					 timeComponent = 0.04166666;

					 double orderOfMagComponent;
					 if (unit.startsWith("MM"))
					 orderOfMagComponent = 1000000.0;
					 else if (unit.startsWith("K") || unit.startsWith("M"))
					 orderOfMagComponent = 1000.0;
					 else
					 orderOfMagComponent = 1.0;

					 flowFactors[i] = timeComponent * orderOfMagComponent / 1000000;
					 */
				}


			}
			else {
				/*TODO
				 if (flows.length > 1 && flows[1].getFactor() != null)
				 flowFactors[1] = flows[1].getFactor();

				 if (flows.length > 2 && flows[2].getFactor() != null)
				 flowFactors[2] = flows[2].getFactor();
				 */
			}

			mCurrent = mData->getHeatingMediumFlow1() * flowFactors[0]
				//TODO + maxWithZero(towerData.getHeatingMediumFlow2()) * flowFactors[1]
				//TODO + maxWithZero(towerData.getHeatingMediumFlow3()) * flowFactors[2]
				;


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
