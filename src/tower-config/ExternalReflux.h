//
//  ExternalReflux.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/9/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_ExternalReflux_h
#define Distillation_Advisor_ExternalReflux_h

#include "stdafx.h"

#include "IExternalReflux.h"

namespace dacore {

	class ExternalReflux : public IExternalReflux {

	public:
		ExternalReflux()
			:mRefluxIncMethod(IncreaseMethod::REFLUX_INC_METHOD_OTHER), mRefluxDecMethod(DecreaseMethod::REFLUX_DEC_METHOD_OTHER){

			mFlowFactor = Validate::INVALID_DBL;

			Validate::registerStrPattern(IExternalReflux_incMethodOther, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(IExternalReflux_decMethodOther, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(IExternalReflux_flowTag, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(IExternalReflux_flowUnit, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerNumPattern(IExternalReflux_flowFactor, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));
		}

		virtual ~ExternalReflux(){}

		const char* IExternalReflux_levelControl = "ExternalReflux.levelControl";
		virtual bool getLevelControl(){ return mLevelControl; }
		virtual void setLevelControl(bool val){
			Notify::notify(IExternalReflux_levelControl);
			mLevelControl = val;
		}

		const char* IExternalReflux_configured = "ExternalReflux.configured";
		virtual bool getConfigured(){ return mConfigured; }
		virtual void setConfigured(bool val){
			Notify::notify(IExternalReflux_configured);
			mConfigured = val;
		}

		const char* IExternalReflux_incMethod = "ExternalReflux.incMethod";
		virtual IncreaseMethod getIncreaseMethod(){ return mRefluxIncMethod; }
		virtual void setIncreaseMethod(const IncreaseMethod& method){
			Notify::notify(IExternalReflux_incMethod);
			mRefluxIncMethod = method;
		}

		const char* IExternalReflux_incMethodOther = "ExternalReflux.incMethodOther";
		virtual std::string getIncreaseMethodOther(){ return mIncMethodOther; }
		virtual void setIncreaseMethodOther(const std::string& val){
			Validate::validate(IExternalReflux_incMethodOther, val);
			mIncMethodOther = val;
		}

		const char* IExternalReflux_decMethod = "ExternalReflux.decMethod";
		virtual DecreaseMethod getDecreaseMethod(){ return mRefluxDecMethod; }
		virtual void setDecreaseMethod(const DecreaseMethod& method){
			Notify::notify(IExternalReflux_decMethod);
			mRefluxDecMethod = method;
		}

		const char* IExternalReflux_decMethodOther = "ExternalReflux.decMethodOther";
		virtual std::string getDecreaseMethodOther(){ return mDecMethodOther; }
		virtual void setDecreaseMethodOther(const std::string& val){
			Validate::validate(IExternalReflux_decMethodOther, val);
			mIncMethodOther = val;
		}

		const char* IExternalReflux_flowTag = "ExternalReflux.flowTag";
		virtual std::string getFlowTag(){ return mFlowTag; }
		virtual void setFlowTag(const std::string& val){
			Validate::validate(IExternalReflux_flowTag, val);
			mFlowTag = val;
		}

		const char* IExternalReflux_flowUnit = "ExternalReflux.flowUnit";
		virtual std::string getFlowUnit(){ return mFlowUnit; }
		virtual void setFlowUnit(const std::string& val){
			Validate::validate(IExternalReflux_flowUnit, val);
			mFlowTag = val;
		}

		const char* IExternalReflux_flowFactor = "ExternalReflux.flowFactor";
		virtual double getFlowFactor(){ return mFlowFactor; }
		virtual void setFlowFactor(double val){
			Validate::validate(IExternalReflux_flowFactor, val);
			mFlowFactor = val;
		}

		static const char* ExternalReflux::incMethodStr(IncreaseMethod m){
			switch (m){
			case DEC_DIST_FLOW:
				return "Decrease Overhead flow";
			case INC_REFLUX_FLOW:
				return "Increase Reflux flow";
			case DEC_OH_TEMP:
				return "Decrease Overhead TIC";
			case DEC_DF_RATIO:
				return "Decrease Distillate/Feed Ratio";
			case DEC_RF_RATIO:
				return "Decrease Reflux/Feed Ratio";
			case REFLUX_INC_METHOD_OTHER:
				return "Other (Specify)";
			default: //REFLUX_INC_METHOD_NOT_SET 
				return "...";
			}
		}

		static const char* ExternalReflux::decMethodStr(DecreaseMethod m){
			switch (m){
			case INC_DIST_FLOW:
				return "Increase Overhead Flow";
			case DEC_REFLUX_FLOW:
				return "Decrease Reflux Flow";
			case INC_OH_TEMP:
				return "Increase Overhead TIC";
			case INC_DF_RATIO:
				return "Increase Distillate/Feed Ratio";
			case INC_RF_RATIO:
				return "Increase Reflux/Feed Ratio";
			case REFLUX_DEC_METHOD_OTHER:
				return "Other (Specify)";
			default: //REFLUX_DEC_METHOD_NOT_SET 
				return "...";
			}
		}

	protected:
		bool                    mLevelControl;
		bool                    mConfigured;
		IncreaseMethod			mRefluxIncMethod;
		std::string             mIncMethodOther;
		DecreaseMethod			mRefluxDecMethod;
		std::string             mDecMethodOther;
		std::string             mFlowTag;
		std::string             mFlowUnit;
		double                  mFlowFactor;

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			pt.put(IExternalReflux_levelControl, mLevelControl);
			pt.put(IExternalReflux_configured, mConfigured);
			pt.put(IExternalReflux_incMethod, mRefluxIncMethod);
			pt.put(IExternalReflux_incMethodOther, mIncMethodOther);
			pt.put(IExternalReflux_decMethod, mRefluxDecMethod);
			pt.put(IExternalReflux_decMethodOther, mDecMethodOther);
			pt.put(IExternalReflux_flowTag, mFlowTag);
			pt.put(IExternalReflux_flowUnit, mFlowUnit);
			pt.put(IExternalReflux_flowFactor, mFlowFactor);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			mLevelControl = pt.get<bool>(IExternalReflux_levelControl);
			mConfigured = pt.get<bool>(IExternalReflux_configured);
			mRefluxIncMethod = (IncreaseMethod)pt.get<int>(IExternalReflux_incMethod);
			mIncMethodOther = pt.get<std::string>(IExternalReflux_incMethodOther);
			mRefluxDecMethod = (DecreaseMethod)pt.get<int>(IExternalReflux_decMethod);
			mDecMethodOther = pt.get<std::string>(IExternalReflux_decMethodOther);
			mFlowTag = pt.get<std::string>(IExternalReflux_flowTag);
			mFlowUnit = pt.get<std::string>(IExternalReflux_flowUnit);
			mFlowFactor = pt.get<double>(IExternalReflux_flowFactor);
		}

	};

}// namespace

extern "C" DACORE_API const char* DACORE_APIENTRY RefluxIncMethodStr(dacore::IExternalReflux::IncreaseMethod m){ return dacore::ExternalReflux::incMethodStr(m); }
extern "C" DACORE_API const char* DACORE_APIENTRY RefluxDecMethodStr(dacore::IExternalReflux::DecreaseMethod m){ return dacore::ExternalReflux::decMethodStr(m); }

#endif
