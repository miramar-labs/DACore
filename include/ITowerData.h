//
//  ITowerData.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 6/30/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_ITowerData_h
#define Distillation_Advisor_ITowerData_h

#include "dacommon.h"

namespace dacore {

	class IOverridesData;
	class IInstrumentsData;
	class ILabResultsData;

	class DACORE_API ITowerData : public ISerialize  {	//TODO- CHECKME - do we need to serialize this?????

	public:
		virtual ~ITowerData(){}

		virtual IOverridesData* getOverrides() = 0;
		virtual void setOverrides(IOverridesData* data) = 0;

		virtual IInstrumentsData* getPrimaryInstruments() = 0;
		virtual void setPrimaryInstruments(IInstrumentsData* data) = 0;

		virtual IInstrumentsData* getSecondaryInstruments() = 0;    // can be NULL
		virtual void setSecondaryInstruments(IInstrumentsData* data) = 0;

		virtual ILabResultsData* getLabResults() = 0;
		virtual void setLabResults(ILabResultsData* data) = 0;

		virtual double getReflux() = 0;
		virtual void setReflux(double val) = 0;

		virtual double getFeedFlow1() = 0;
		virtual void setFeedFlow1(double val) = 0;

		virtual double getHeatingMediumFlow1() = 0;
		virtual void setHeatingMediumFlow1(double val) = 0;

		virtual double getOperatingPressure() = 0;
		virtual void setOperatingPressure(double val) = 0;

		virtual double getOutputOnPIC() = 0;
		virtual void setOutputOnPIC(double val) = 0;

	};

}

#endif
