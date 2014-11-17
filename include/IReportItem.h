//
//  IReportItem.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IReportItem_h
#define Distillation_Advisor_IReportItem_h

#include "dacommon.h"

namespace dacore {

	class DACORE_API IReportItem : public ISerialize {

	public:
		virtual ~IReportItem(){}

		virtual double getMin() = 0;
		virtual void setMin(double val) = 0;

		virtual double getMax() = 0;
		virtual void setMax(double val) = 0;

		virtual double getCurrent() = 0;
		virtual void setCurrent(double val) = 0;

		virtual double getPrior20() = 0;
		virtual void setPrior20(double val) = 0;

		virtual double getPrior40() = 0;
		virtual void setPrior40(double val) = 0;

		virtual double getNext20() = 0;
		virtual void setNext20(double val) = 0;

		virtual double getNext40() = 0;
		virtual void setNext40(double val) = 0;

		virtual double getRange() = 0;
		virtual void setRange(double val) = 0;

		virtual ITowerReport::Status getStatus() = 0;
		virtual void setStatus(const ITowerReport::Status& status) = 0;
	};

}

#endif
