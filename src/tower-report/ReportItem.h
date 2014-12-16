//
//  ReportItem.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/11/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_ReportItem_h
#define Distillation_Advisor_ReportItem_h

#include "stdafx.h"

#include "IReportItem.h"

namespace dacore {

	class ReportItem : public IReportItem {

	public:

		ReportItem()
			:mMin(IValidate::INVALID_DBL), 
			mMax(IValidate::INVALID_DBL), 
			mCurrent(IValidate::INVALID_DBL), 
			mPrior20(IValidate::INVALID_DBL),
			mPrior40(IValidate::INVALID_DBL),
			mNext20(IValidate::INVALID_DBL),
			mNext40(IValidate::INVALID_DBL),
			mRange(IValidate::INVALID_DBL)
		{} 

		virtual ~ReportItem(){}

		virtual double getMin() = 0;
		virtual void setMin(double val){ mMin = val; }

		virtual double getMax() = 0;
		virtual void setMax(double val){ mMax = val; }

		virtual double getCurrent() = 0;
		virtual void setCurrent(double val){ mCurrent = val; }

		virtual double getPrior20() = 0;
		virtual void setPrior20(double val){ mPrior20 = val; }

		virtual double getPrior40() = 0;
		virtual void setPrior40(double val){ mPrior40 = val; }

		virtual double getNext20() = 0;
		virtual void setNext20(double val){ mNext20 = val; }

		virtual double getNext40() = 0;
		virtual void setNext40(double val){ mNext40 = val; }

		virtual double getRange() = 0;
		virtual void setRange(double val){ mRange = val; }

		virtual ITowerReport::Status getStatus() = 0;
		virtual void setStatus(const ITowerReport::Status& status){ mStatus = status; }

	protected:
		double  mMin;
		double  mMax;
		double  mCurrent;
		double  mPrior20;
		double  mPrior40;
		double  mNext20;
		double  mNext40;
		double  mRange;

		ITowerReport::Status    mStatus;

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			pt.put("ReportItem.min", mMin);
			pt.put("ReportItem.max", mMax);
			pt.put("ReportItem.current", mCurrent);
			pt.put("ReportItem.prior20", mPrior20);
			pt.put("ReportItem.prior40", mPrior40);
			pt.put("ReportItem.next20", mNext20);
			pt.put("ReportItem.next40", mNext40);
			pt.put("ReportItem.range", mRange);

			pt.put("ReportItem.status", (int)mStatus);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			mMin = pt.get<double>("ReportItem.min");
			mMax = pt.get<double>("ReportItem.max");
			mCurrent = pt.get<double>("ReportItem.current");
			mPrior20 = pt.get<double>("ReportItem.prior20");
			mPrior40 = pt.get<double>("ReportItem.prior40");
			mNext20 = pt.get<double>("ReportItem.next20");
			mNext40 = pt.get<double>("ReportItem.next40");
			mRange = pt.get<double>("ReportItem.range");

			mStatus = (ITowerReport::Status)pt.get<int>("ReportItem.status");

		}

	protected: //not serialized

		ReportItem(ITowerConfig* config, ITowerData* data)
			:mConfig(config), mData(data){}

		ITowerConfig* mConfig;
		ITowerData* mData;

		double generateNext(int t){

			double val = 0;

			double c0, c1, cov00, cov01, cov11, chisq;

			if (mPrior20 == IValidate::INVALID_DBL){
				std::cout << "warning: can't do linear regression without at least prior20 data..." << std::endl;
				return IValidate::INVALID_DBL;	//TODO think of better way to return error here
			}

			if (mPrior40 == IValidate::INVALID_DBL){
				double x[2] = { -20, 0 };
				double y[2] = { getPrior20(), getCurrent() };
				double w[2] = { 1, 1 };
				gsl_fit_wlinear(x, 1, w, 1, y, 1, 2,
					&c0, &c1, &cov00, &cov01, &cov11,
					&chisq);
			}
			else{
				double x[3] = { -40, -20, 0 };
				double y[3] = { getPrior40(), getPrior20(), getCurrent() };
				double w[3] = { 1, 1, 1 };
				gsl_fit_wlinear(x, 1, w, 1, y, 1, 3,
					&c0, &c1, &cov00, &cov01, &cov11,
					&chisq);
			}

			val = c1 * t + c0;

			return val;

		}
	};

}

#endif
