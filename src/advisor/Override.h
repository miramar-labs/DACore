//
//  Override.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/11/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Override_h
#define Distillation_Advisor_Override_h

#include "stdafx.h"

#include "IOverride.h"

namespace dacore {

	class Override : public IOverride {

	public:

		Override(OverrideId id = 0, PreventTarget target = PreventTarget::PRESSURE_DECREASE,
			const TripPointOperator& op = TripPointOperator::GREATER_THAN,
			double val = 0.0,
			const std::string& name = "",
			const std::string& message = "")
			:mID(id), mTarget(target), mOp(op), mTripPoint(val), mName(name), mMsg(message){}

		virtual ~Override(){}

		virtual bool willTripFor(double value){
			//TODO: precision ...
			switch (mOp){
			case TripPointOperator::GREATER_THAN:
				return value > mTripPoint;
			case TripPointOperator::LESS_THAN:
				return value < mTripPoint;
			case TripPointOperator::EQUALS:
				return value == mTripPoint;
			default:
				break;  //TODO - error
			}
			return false;
		}

		virtual std::string getMessage(const std::string& method){
			return "Suggestion \"" + method + "\" disabled by \"" + getName() + "\" override.";
		}
		virtual std::string getName(){ return mName; }

		virtual void setTripPoint(double val){ mTripPoint = val; }
		virtual double getTripPoint(){ return mTripPoint; }

		virtual void setTripPointOp(TripPointOperator op){ mOp = op; }
		virtual TripPointOperator getTripPointOp(){ return mOp; }

		virtual void setPreventTarget(PreventTarget target){ mTarget = target; }

		virtual PreventTarget getPreventTarget(){ return mTarget; }

		static const char* preventTargetStr(PreventTarget m){
			switch (m){
			case PRESSURE_INCREASE:
				return "PRESSURE_INCREASE";
			case PRESSURE_DECREASE:
				return "PRESSURE_DECREASE";
			case REFLUX_INCREASE:
				return "REFLUX_INCREASE";
			case REFLUX_DECREASE:
				return "REFLUX_DECREASE";
			case REBOIL_INCREASE:
				return "REBOIL_INCREASE";
			case REBOIL_DECREASE:
				return "REBOIL_DECREASE";

			default:
				return "...";
			}
		}

		virtual bool isEnabled(){ return mEnabled; }

		virtual void setEnabled(bool bEnabled){ mEnabled = bEnabled; }

		virtual OverrideId   getId(){ return mID; }

	private:
		OverrideId			mID;
		PreventTarget       mTarget;
		TripPointOperator   mOp;
		double              mTripPoint;
		std::string         mName;
		std::string         mMsg;
		bool				mEnabled;

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			pt.put("Override.id", mID);
			pt.put("Override.preventTarget", mTarget);
			pt.put("Override.tripPointOp", (int)mOp);
			pt.put("Override.tripPoint", mTripPoint);
			pt.put("Override.name", mName);
			pt.put("Override.message", mMsg);
			pt.put("Override.enabled", mEnabled);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			mID = pt.get<OverrideId>("Override.id");
			mTarget = (PreventTarget)pt.get<int>("Override.preventTarget");
			mOp = (TripPointOperator)pt.get<int>("Override.tripPointOp");
			mTripPoint = pt.get<double>("Override.tripPoint");
			mName = pt.get<std::string>("Override.name");
			mMsg = pt.get<std::string>("Override.message");
			mEnabled = pt.get<bool>("Override.enabled");
		}

	};

}

#endif
