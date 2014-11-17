//
//  OverridesData.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/11/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_OverridesData_h
#define Distillation_Advisor_OverridesData_h

#include "stdafx.h"

#include "IOverridesData.h"

namespace dacore {

	class OverridesData : public IOverridesData {

	public:
		virtual ~OverridesData(){}

		virtual double getPreventsDecreaseInReboil(){ return mPreventsDecInReboil; }
		virtual void setPreventsDecreaseInReboil(double val){ mPreventsDecInReboil = val; }

		virtual double getPreventsIncreaseInReboil(){ return mPreventsIncInReboil; }
		virtual void setPreventsIncreaseInReboil(double val){ mPreventsIncInReboil = val; }

		virtual double getPreventsDecreaseInReflux(){ return mPreventsDecInReflux; }
		virtual void setPreventsDecreaseInReflux(double val){ mPreventsDecInReflux = val; }

		virtual double getPreventsIncreaseInReflux(){ return mPreventsIncInReflux; }
		virtual void setPreventsIncreaseInReflux(double val){ mPreventsIncInReflux = val; }

		virtual double getPreventsPressureDecrease(){ return mPreventsPressureInc; }
		virtual void setPreventsPressureDecrease(double val){ mPreventsPressureInc = val; }

		virtual double getPreventsPressureIncrease(){ return mPreventsPressureDec; }
		virtual void setPreventsPressureIncrease(double val){ mPreventsPressureDec = val; }

	private:
		double  mPreventsDecInReboil;
		double  mPreventsIncInReboil;
		double  mPreventsDecInReflux;
		double  mPreventsIncInReflux;
		double  mPreventsPressureInc;
		double  mPreventsPressureDec;

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			pt.put("OverridesData.preventsDecInReboil", mPreventsDecInReboil);
			pt.put("OverridesData.preventsIncInReboil", mPreventsIncInReboil);
			pt.put("OverridesData.preventsDecInReflux", mPreventsDecInReflux);
			pt.put("OverridesData.preventsIncInReflux", mPreventsIncInReflux);
			pt.put("OverridesData.preventsPressureInc", mPreventsPressureInc);
			pt.put("OverridesData.preventsPressureDec", mPreventsPressureDec);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			mPreventsDecInReboil = pt.get<double>("OverridesData.preventsDecInReboil");
			mPreventsIncInReboil = pt.get<double>("OverridesData.preventsIncInReboil");
			mPreventsDecInReflux = pt.get<double>("OverridesData.preventsDecInReflux");
			mPreventsIncInReflux = pt.get<double>("OverridesData.preventsIncInReflux");
			mPreventsPressureInc = pt.get<double>("OverridesData.preventsPressureInc");
			mPreventsPressureDec = pt.get<double>("OverridesData.preventsPressureDec");

		}
	};

}

#endif
