//
//  ControlLimits.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/20/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_ControlLimits_h
#define Distillation_Advisor_ControlLimits_h

#include "stdafx.h"

#include "IValidate.h"
#include "IControlLimits.h"

namespace dacore {

	class ControlLimits : public IControlLimits {

	public:
		ControlLimits(){
			mHKMin = Validate::INVALID_DBL;
			mLKMin = Validate::INVALID_DBL;
			mDeltaMin = Validate::INVALID_DBL;
			mRefluxMin = Validate::INVALID_DBL;
			mFeedMin = Validate::INVALID_DBL;
			mHeatingMediumFlowMin = Validate::INVALID_DBL;
			mOpPressureMin = Validate::INVALID_DBL;
			mPressureControllerMin = Validate::INVALID_DBL;

			mHKMax = Validate::INVALID_DBL;
			mLKMax = Validate::INVALID_DBL;
			mDeltaMax = Validate::INVALID_DBL;
			mRefluxMax = Validate::INVALID_DBL;
			mFeedMax = Validate::INVALID_DBL;
			mHeatingMediumFlowMax = Validate::INVALID_DBL;
			mOpPressureMax = Validate::INVALID_DBL;
			mPressureControllerMax = Validate::INVALID_DBL;

			Validate::registerNumPattern(IControlLimits_hk_min, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
			Validate::registerNumPattern(IControlLimits_lk_min, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
			Validate::registerNumPattern(IControlLimits_delta_min, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
			Validate::registerNumPattern(IControlLimits_reflux_min, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
			Validate::registerNumPattern(IControlLimits_feed_min, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
			Validate::registerNumPattern(IControlLimits_heatingMediumFlow_min, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
			Validate::registerNumPattern(IControlLimits_operatingPressure_min, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
			Validate::registerNumPattern(IControlLimits_pressureController_min, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));

			Validate::registerNumPattern(IControlLimits_hk_max, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
			Validate::registerNumPattern(IControlLimits_lk_max, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
			Validate::registerNumPattern(IControlLimits_delta_max, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
			Validate::registerNumPattern(IControlLimits_reflux_max, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
			Validate::registerNumPattern(IControlLimits_feed_max, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
			Validate::registerNumPattern(IControlLimits_heatingMediumFlow_max, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
			Validate::registerNumPattern(IControlLimits_operatingPressure_max, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
			Validate::registerNumPattern(IControlLimits_pressureController_max, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));

		}

		virtual ~ControlLimits(){}

		const char* IControlLimits_hk_min = "ControlLimits.hkMin";
		virtual double getHeavyKeyMin(){ return mHKMin; }
		virtual void setHeavyKeyMin(double val){
			Validate::validate(IControlLimits_hk_min, val);
			mHKMin = val;
		}

		const char* IControlLimits_hk_max = "ControlLimits.hkMax";
		virtual double getHeavyKeyMax(){ return mHKMax; }
		virtual void setHeavyKeyMax(double val){
			Validate::validate(IControlLimits_hk_max, val);
			mHKMax = val;
		}

		const char* IControlLimits_lk_min = "ControlLimits.lkMin";
		virtual double getLightKeyMin(){ return mLKMin; }
		virtual void setLightKeyMin(double val){
			Validate::validate(IControlLimits_lk_min, val);
			mLKMin = val;
		}

		const char* IControlLimits_lk_max = "ControlLimits.lkMax";
		virtual double getLightKeyMax(){ return mLKMax; }
		virtual void setLightKeyMax(double val){
			Validate::validate(IControlLimits_lk_max, val);
			mLKMax = val;
		}

		const char* IControlLimits_delta_min = "ControlLimits.deltaMin";
		virtual double getDeltaInstrumentMin(){ return mDeltaMin; }
		virtual void setDeltaInstrumentMin(double val){
			Validate::validate(IControlLimits_delta_min, val);
			mDeltaMin = val;
		}

		const char* IControlLimits_delta_max = "ControlLimits.deltaMax";
		virtual double getDeltaInstrumentMax(){ return mDeltaMax; }
		virtual void setDeltaInstrumentMax(double val){
			Validate::validate(IControlLimits_delta_max, val);
			mDeltaMax = val;
		}

		const char* IControlLimits_reflux_min = "ControlLimits.refluxMin";
		virtual double getRefluxMin(){ return mRefluxMin; }
		virtual void setRefluxMin(double val){
			Validate::validate(IControlLimits_reflux_min, val);
			mRefluxMin = val;
		}

		const char* IControlLimits_reflux_max = "ControlLimits.refluxMax";
		virtual double getRefluxMax(){ return mRefluxMax; }
		virtual void setRefluxMax(double val){
			Validate::validate(IControlLimits_reflux_max, val);
			mRefluxMax = val;
		}

		const char* IControlLimits_feed_min = "ControlLimits.feedMin";
		virtual double getFeedMin(){ return mFeedMin; }
		virtual void setFeedMin(double val){
			Validate::validate(IControlLimits_feed_min, val);
			mFeedMin = val;
		}

		const char* IControlLimits_feed_max = "ControlLimits.feedMax";
		virtual double getFeedMax(){ return mFeedMax; }
		virtual void setFeedMax(double val){
			Validate::validate(IControlLimits_feed_max, val);
			mFeedMax = val;
		}

		const char* IControlLimits_heatingMediumFlow_min = "ControlLimits.heatingMediumFlowMin";
		virtual double getHeatingMediumFlowMin(){ return mHeatingMediumFlowMin; }
		virtual void setHeatingMediumFlowMin(double val){
			Validate::validate(IControlLimits_heatingMediumFlow_min, val);
			mHeatingMediumFlowMin = val;
		}

		const char* IControlLimits_heatingMediumFlow_max = "ControlLimits.heatingMediumFlowMax";
		virtual double getHeatingMediumFlowMax(){ return mHeatingMediumFlowMax; }
		virtual void setHeatingMediumFlowMax(double val){
			Validate::validate(IControlLimits_heatingMediumFlow_max, val);
			mHeatingMediumFlowMax = val;
		}

		const char* IControlLimits_operatingPressure_min = "ControlLimits.operatingPressureMin";
		virtual double getOperatingPressureMin(){ return mOpPressureMin; }
		virtual void setOperatingPressureMin(double val){
			Validate::validate(IControlLimits_operatingPressure_min, val);
			mOpPressureMin = val;
		}

		const char* IControlLimits_operatingPressure_max = "ControlLimits.operatingPressureMax";
		virtual double getOperatingPressureMax(){ return mOpPressureMax; }
		virtual void setOperatingPressureMax(double val){
			Validate::validate(IControlLimits_operatingPressure_max, val);
			mOpPressureMax = val;
		}

		const char* IControlLimits_pressureController_min = "ControlLimits.pressureControllerMin";
		virtual double getPressureControllerMin(){ return mPressureControllerMin; }
		virtual void setPressureControllerMin(double val){
			Validate::validate(IControlLimits_pressureController_min, val);
			mPressureControllerMin = val;
		}

		const char* IControlLimits_pressureController_max = "ControlLimits.pressureControllerMax";
		virtual double getPressureControllerMax(){ return mPressureControllerMax; }
		virtual void setPressureControllerMax(double val){
			Validate::validate(IControlLimits_pressureController_max, val);
			mPressureControllerMax = val;
		}

		virtual const RefluxLimitType& getRefluxLimitType(){ return mRefluxLimitType; }
		virtual void setRefluxLimitType(const RefluxLimitType& type){ mRefluxLimitType = type; }

	protected:
		double  mHKMin;
		double  mLKMin;
		double  mDeltaMin;
		double  mRefluxMin;
		double  mFeedMin;
		double  mHeatingMediumFlowMin;
		double  mOpPressureMin;
		double  mPressureControllerMin;

		double  mHKMax;
		double  mLKMax;
		double  mDeltaMax;
		double  mRefluxMax;
		double  mFeedMax;
		double  mHeatingMediumFlowMax;
		double  mOpPressureMax;
		double  mPressureControllerMax;

		RefluxLimitType mRefluxLimitType;

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){

			pt.put(IControlLimits_hk_min, mHKMin);
			pt.put(IControlLimits_lk_min, mLKMin);
			pt.put(IControlLimits_delta_min, mDeltaMin);
			pt.put(IControlLimits_reflux_min, mRefluxMin);
			pt.put(IControlLimits_feed_min, mFeedMin);
			pt.put(IControlLimits_heatingMediumFlow_min, mHeatingMediumFlowMin);
			pt.put(IControlLimits_operatingPressure_min, mOpPressureMin);
			pt.put(IControlLimits_pressureController_min, mPressureControllerMin);

			pt.put(IControlLimits_hk_max, mHKMax);
			pt.put(IControlLimits_lk_max, mLKMax);
			pt.put(IControlLimits_delta_max, mDeltaMax);
			pt.put(IControlLimits_reflux_max, mRefluxMax);
			pt.put(IControlLimits_feed_max, mFeedMax);
			pt.put(IControlLimits_heatingMediumFlow_max, mHeatingMediumFlowMax);
			pt.put(IControlLimits_operatingPressure_max, mOpPressureMax);
			pt.put(IControlLimits_pressureController_max, mPressureControllerMax);

			pt.put("ControlLimits.refluxLimitType", (int)mRefluxLimitType);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){

			mHKMin = pt.get<double>(IControlLimits_hk_min);
			mLKMin = pt.get<double>(IControlLimits_lk_min);
			mDeltaMin = pt.get<double>(IControlLimits_delta_min);
			mRefluxMin = pt.get<double>(IControlLimits_reflux_min);
			mFeedMin = pt.get<double>(IControlLimits_feed_min);
			mHeatingMediumFlowMin = pt.get<double>(IControlLimits_heatingMediumFlow_min);
			mOpPressureMin = pt.get<double>(IControlLimits_operatingPressure_min);
			mPressureControllerMin = pt.get<double>(IControlLimits_pressureController_min);

			mHKMax = pt.get<double>(IControlLimits_hk_max);
			mLKMax = pt.get<double>(IControlLimits_lk_max);
			mDeltaMax = pt.get<double>(IControlLimits_delta_max);
			mRefluxMax = pt.get<double>(IControlLimits_reflux_max);
			mFeedMax = pt.get<double>(IControlLimits_feed_max);
			mHeatingMediumFlowMax = pt.get<double>(IControlLimits_heatingMediumFlow_max);
			mOpPressureMax = pt.get<double>(IControlLimits_operatingPressure_max);
			mPressureControllerMax = pt.get<double>(IControlLimits_pressureController_max);

			mRefluxLimitType = (RefluxLimitType)pt.get<int>("ControlLimits.refluxLimitType");
		}

	};

}

#endif
