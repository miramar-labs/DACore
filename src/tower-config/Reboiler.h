//
//  Reboiler.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/9/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Reboiler_h
#define Distillation_Advisor_Reboiler_h

#include "stdafx.h"

#include "IReboiler.h"

namespace dacore {

	class Reboiler : public IReboiler {

	public:
		Reboiler() :mReboilIncMethod(IncreaseMethod::REBOIL_INC_METHOD_OTHER),
			mReboilDecMethod(DecreaseMethod::REBOIL_DEC_METHOD_OTHER){

			Validate::registerStrPattern(IReboiler_incMethodOther, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(IReboiler_decMethodOther, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));

		}

		virtual ~Reboiler(){}

		const char* IReboiler_levelControl = "Reboiler.levelControl";
		virtual bool getLevelControl(){ return mLevelControl; }
		virtual void setLevelConrol(bool val){
			Notify::notify(IReboiler_levelControl);
			mLevelControl = val;
		}

		const char* IReboiler_incMethod = "Reboiler.incMethod";
		virtual IncreaseMethod getIncreaseMethod(){ return mReboilIncMethod; }
		virtual void setIncreaseMethod(const IncreaseMethod& method){
			Notify::notify(IReboiler_incMethod);
			mReboilIncMethod = method;
		}

		const char* IReboiler_incMethodOther = "Reboiler.incMethodOther";
		virtual std::string getIncreaseMethodOther(){ return mReboilIncMethodOther; }
		virtual void setIncreaseMethodOther(const std::string& other){
			Validate::validate(IReboiler_incMethodOther, other);
			mReboilIncMethodOther = other;
		}

		const char* IReboiler_decMethod = "Reboiler.decMethod";
		virtual DecreaseMethod getDecreaseMethod(){ return mReboilDecMethod; }
		virtual void setDecreaseMethod(const DecreaseMethod& method){
			Notify::notify(IReboiler_decMethod);
			mReboilDecMethod = method;
		}

		const char* IReboiler_decMethodOther = "Reboiler.decMethodOther";
		virtual std::string getDecreaseMethodOther(){ return mReboilDecMethodOther; }
		virtual void setDecreaseMethodOther(const std::string& other){
			Validate::validate(IReboiler_decMethodOther, other);
			mReboilDecMethodOther = other;
		}

		static const char* incMethodStr(IncreaseMethod m){
			switch (m){
				case INC_BASE_TEMP:
					return "Increase Base TIC";
				case DEC_BASE_FLOW:
					return "Decrease Base FIC";			
				case INC_HM_FEED_RATIO:
					return "Increase the heating medium/Feed Ratio";			
				case INC_HM_FLOW:
					return "Increase heating medium FIC";			
				case DEC_BOTTOMS_FEED_RATIO:
					return "Decrease Bottoms/Feed Ratio";			
				case REBOIL_INC_METHOD_OTHER:
					return "Other (Specify)";
				default:// REBOIL_INC_METHOD_NOT_SET 
					return "...";
			}
		}

		static const char* decMethodStr(DecreaseMethod m){
			switch (m){
			case DEC_BASE_TEMP:
				return "Decrease Base TIC";
			case INC_BASE_FLOW:
				return "Increase Base FIC";
			case DEC_HM_FEED_RATIO:
				return "Decrease the heating medium/Feed Ratio";
			case DEC_HM_FLOW:
				return "Decrease heating medium FIC";
			case INC_BOTTOMS_FEED_RATIO:
				return "Increase Bottoms/Feed Ratio";
			case REBOIL_DEC_METHOD_OTHER:
				return "Other (Specify)";
			default:// REBOIL_DEC_METHOD_NOT_SET 
				return "...";
			}
		}

	protected:
		bool                    mLevelControl;
		IncreaseMethod			mReboilIncMethod;
		std::string             mReboilIncMethodOther;
		DecreaseMethod			mReboilDecMethod;
		std::string             mReboilDecMethodOther;

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			pt.put(IReboiler_levelControl, mLevelControl);
			pt.put(IReboiler_incMethod, mReboilIncMethod);
			pt.put(IReboiler_incMethodOther, mReboilIncMethodOther);
			pt.put(IReboiler_decMethod, mReboilDecMethod);
			pt.put(IReboiler_decMethodOther, mReboilDecMethodOther);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			mLevelControl = pt.get<bool>(IReboiler_levelControl);
			mReboilIncMethod = (IncreaseMethod)pt.get<int>(IReboiler_incMethod);
			mReboilIncMethodOther = pt.get<std::string>(IReboiler_incMethodOther);
			mReboilDecMethod = (DecreaseMethod)pt.get<int>(IReboiler_decMethod);
			mReboilDecMethodOther = pt.get<std::string>(IReboiler_decMethodOther);
		}

	};

}//namespace

extern "C" DACORE_API const char* DACORE_APIENTRY ReboilerIncMethodStr(dacore::IReboiler::IncreaseMethod m){ return dacore::Reboiler::incMethodStr(m); }
extern "C" DACORE_API const char* DACORE_APIENTRY ReboilerDecMethodStr(dacore::IReboiler::DecreaseMethod m){ return dacore::Reboiler::decMethodStr(m); }


#endif
