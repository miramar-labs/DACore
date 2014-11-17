//
//  ITowerReport.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 6/30/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_ITowerReport_h
#define Distillation_Advisor_ITowerReport_h

#include "dacommon.h"

namespace dacore {

	class IReportItem;

	class DACORE_API ITowerReport : public ISerialize {

	public:
		virtual ~ITowerReport(){}

		enum Status {
			HIGH, ALMOST_HIGH, OK, ALMOST_LOW, LOW
		};

		enum Trend {
			UP, DOWN, EVEN
		};

		virtual IReportItem* getHeavyKey() = 0;
		virtual void setHeavyKey(IReportItem* item) = 0;

		virtual IReportItem* getLightKey() = 0;
		virtual void setLightKey(IReportItem* item) = 0;

		virtual IReportItem* getDelta() = 0;
		virtual void setDelta(IReportItem* item) = 0;

		virtual IReportItem* getReflux() = 0;
		virtual void setReflux(IReportItem* item) = 0;

		virtual IReportItem* getFeed() = 0;
		virtual void setFeed(IReportItem* item) = 0;

		virtual IReportItem* getHeating() = 0;
		virtual void setHeating(IReportItem* item) = 0;

		virtual IReportItem* getOperatingPressure() = 0;
		virtual void setOperatingPressure(IReportItem* item) = 0;

		virtual IReportItem* getOutputOnPIC() = 0;
		virtual void setOutputOnPIC(IReportItem* item) = 0;

	};

}

#endif
