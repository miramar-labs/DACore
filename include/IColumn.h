//
//  IColumn.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IColumn_h
#define Distillation_Advisor_IColumn_h

#include "dacommon.h"

namespace dacore {

	class DACORE_API IColumn : public ISerialize {

	public:
		virtual ~IColumn(){}

		virtual bool isUsingOverheadKeyToDetermineTowerLoading() = 0;

		virtual void setIsUsingOverheadKeyToDetermineTowerLoading(bool isUsing) = 0;

		enum DeltaOption { PRESSURE, TEMPERATURE };

		virtual DeltaOption getUsePressureOrTemperatureDelta() = 0;
		virtual void setUsePressureOrTemperatureDelta(DeltaOption opt) = 0;

		enum ForecastingTimeline { NONE, TWENTY_MINUTE, FORTY_MINUTE };

		virtual ForecastingTimeline getForecastingTimeline() = 0;
		virtual void setForecastingTimeline(ForecastingTimeline tl) = 0;
	};

}

#endif
