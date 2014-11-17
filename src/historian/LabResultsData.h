//
//  LabResultsData.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 8/9/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_LabResultsData_h
#define Distillation_Advisor_LabResultsData_h

#include "stdafx.h"

#include "ILabResultsData.h"

namespace dacore {

	class LabResultsData : public ILabResultsData {

	public:
		virtual ~LabResultsData(){}

		virtual double getHeavyKeyLabResult(){ return mHKResult; }
		virtual void setHeavyKeyLabResult(double val){ mHKResult = val; }

		virtual double getLightKeyLabResult(){ return mLKResult; }
		virtual void setLightKeyLabResult(double val){ mLKResult = val; }

		virtual std::string getTimeStamp(){ return mTimestamp; }

	private:
		double mHKResult;
		double mLKResult;

		std::string mTimestamp; //TODO - fix this

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			pt.put("LabResultsData.hkResult", mHKResult);
			pt.put("LabResultsData.lkResult", mLKResult);
			pt.put("LabResultsData.timestamp", mTimestamp);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			mHKResult = pt.get<double>("LabResultsData.hkResult");
			mLKResult = pt.get<double>("LabResultsData.lkResult");
			mTimestamp = pt.get<std::string>("LabResultsData.timestamp");
		}
	};

}

#endif
