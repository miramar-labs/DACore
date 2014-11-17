//
//  TowerData.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/11/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_TowerData_h
#define Distillation_Advisor_TowerData_h

#include "stdafx.h"

#include "ITowerData.h"

#include "IOverridesData.h"
#include "IInstrumentsData.h"
#include "IInstrumentsData.h"
#include "ILabResultsData.h"

namespace dacore {

	class TowerData : public ITowerData {

	public:
		virtual ~TowerData(){ delete mOverrides; }  //TODO cleanup 

		virtual IOverridesData* getOverrides(){ return mOverrides; }
		virtual void setOverrides(IOverridesData* data){ mOverrides = data; }

		virtual IInstrumentsData* getPrimaryInstruments(){ return mPrimaryInstruments; }
		virtual void setPrimaryInstruments(IInstrumentsData* data){ mPrimaryInstruments = data; }

		virtual IInstrumentsData* getSecondaryInstruments(){ return mSecondaryInstruments; }
		virtual void setSecondaryInstruments(IInstrumentsData* data){ mSecondaryInstruments = data; }

		virtual ILabResultsData* getLabResults(){ return mLabResults; }
		virtual void setLabResults(ILabResultsData* data){ mLabResults = data; }

		virtual double getReflux(){ return mReflux; }
		virtual void setReflux(double val){ mReflux = val; }

		virtual double getFeedFlow1(){ return mFeedFlow1; }
		virtual void setFeedFlow1(double val){ mFeedFlow1 = val; }

		virtual double getHeatingMediumFlow1(){ return mHeatingMediumFlow1; }
		virtual void setHeatingMediumFlow1(double val){ mHeatingMediumFlow1 = val; }

		virtual double getOperatingPressure(){ return mOpPressure; }
		virtual void setOperatingPressure(double val){ mOpPressure = val; }

		virtual double getOutputOnPIC(){ return mOutputOnPIC; }
		virtual void setOutputOnPIC(double val){ mOutputOnPIC = val; }

	private:
		IOverridesData*		mOverrides;
		IInstrumentsData*	mPrimaryInstruments;
		IInstrumentsData*	mSecondaryInstruments;
		ILabResultsData*	mLabResults;
		double mReflux;
		double mFeedFlow1;
		double mHeatingMediumFlow1;
		double mOpPressure;
		double mOutputOnPIC;

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			ISerialize::serializeObj(pt, "TowerData.overrides", mOverrides);
			ISerialize::serializeObj(pt, "TowerData.primaryInstruments", mPrimaryInstruments);
			ISerialize::serializeObj(pt, "TowerData.secondaryInstruments", mSecondaryInstruments);
			ISerialize::serializeObj(pt, "TowerData.labResults", mLabResults);
			pt.put("TowerData.reflux", mReflux);
			pt.put("TowerData.feedFlow1", mFeedFlow1);
			pt.put("TowerData.heatingMediumFlow1", mHeatingMediumFlow1);
			pt.put("TowerData.opPressure", mOpPressure);
			pt.put("TowerData.outputOnPIC", mOutputOnPIC);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			ISerialize::deserializeObj(pt, "TowerData.overrides", mOverrides);
			ISerialize::deserializeObj(pt, "TowerData.primaryInstruments", mPrimaryInstruments);
			ISerialize::deserializeObj(pt, "TowerData.secondaryInstruments", mSecondaryInstruments);
			ISerialize::deserializeObj(pt, "TowerData.labResults", mLabResults);
			mReflux = pt.get<double>("TowerData.reflux");
			mFeedFlow1 = pt.get<double>("TowerData.feedFlow1");
			mHeatingMediumFlow1 = pt.get<double>("TowerData.heatingMediumFlow1");
			mOpPressure = pt.get<double>("TowerData.opPressure");
			mOutputOnPIC = pt.get<double>("TowerData.outputOnPIC");
		}
	};

}

#endif
