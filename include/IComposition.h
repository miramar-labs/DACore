//
//  IComposition.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IComposition_h
#define Distillation_Advisor_IComposition_h

#include "dacommon.h"

namespace dacore {

	class IMonitorMethod;
	class IReportMethod;

	class DACORE_API IComposition : public ISerialize {

	public:
		virtual ~IComposition(){}

		enum MonitorMethod { ANALYZER, TEMPERATURE, LAB_RESULT };

		const char* IComposition_name = "Feed.name";
		virtual MonitorMethod getMonitorMethod() = 0;
		virtual void setMonitorMethod(const MonitorMethod& method) = 0;

		enum ReportMethod { HEAVY_KEY_CONTENT, LIGHT_KEY_CONTENT, ASSAY };

		virtual ReportMethod getReportMethod() = 0;
		virtual void setReportMethod(const ReportMethod& method) = 0;

		virtual bool isManipulatedSetPoint() = 0;
		virtual void setIsManipulatedSetPoint(bool v) = 0;

		virtual double getInstabilityValPercent() = 0;
		virtual void setInstabilityValPercent(double v) = 0;

		virtual std::string getHeavyKey() = 0;
		virtual void setHeavyKey(const std::string& v) = 0;

		virtual std::string getHeavyKeyUnit() = 0;
		virtual void setHeavyKeyUnit(const std::string& v) = 0;

		virtual std::string getLightKey() = 0;
		virtual void setLightKey(const std::string& v) = 0;

		virtual std::string getLightKeyUnit() = 0;
		virtual void setLightKeyUnit(const std::string& v) = 0;

		virtual std::string getAnalyzerTag() = 0;
		virtual void setgetAnalyzerTag(const std::string& v) = 0;

		virtual std::string getLabTag() = 0;
		virtual void setLabTag(const std::string& v) = 0;

		virtual std::string getDeltaTempTag() = 0;
		virtual void setDeltaTempTag(const std::string& v) = 0;

		virtual std::string getLowTempTag() = 0;
		virtual void setLowTempTag(const std::string& v) = 0;

		virtual std::string getHighTempTag() = 0;
		virtual void setHighTempTag(const std::string& v) = 0;

		//computed:	
		virtual bool isManualLab() = 0;
	};

}

#endif
