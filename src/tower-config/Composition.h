//
//  Composition.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/10/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Composition_h
#define Distillation_Advisor_Composition_h

#include "stdafx.h"

class IMonitorMethod;
class IReportMethod;

#include "IComposition.h"

namespace dacore {

	class Composition : public IComposition {

	public:
		Composition(const std::string& prefix)
			:mPrefix(prefix), mInstabilityValPercent(Validate::INVALID_DBL){

			Validate::registerNumPattern(mPrefix + IComposition_instabilityValPercent, std::tuple<double, double, double, double>(0, Validate::MAX_DBL, 0, Validate::INVALID_DBL));

			Validate::registerStrPattern(mPrefix + IComposition_heavyKey, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(mPrefix + IComposition_heavyKeyUnit, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(mPrefix + IComposition_lightKey, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(mPrefix + IComposition_lightKeyUnit, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(mPrefix + IComposition_analyzerTag, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(mPrefix + IComposition_labTag, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(mPrefix + IComposition_deltaTempTag, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(mPrefix + IComposition_lowTempTag, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
			Validate::registerStrPattern(mPrefix + IComposition_highTempTag, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));

		}

		virtual ~Composition(){}

		const char* IComposition_monitorMethod = "_Composition.monitorMethod";
		virtual MonitorMethod getMonitorMethod(){ return mMonitorMethod; }
		virtual void setMonitorMethod(const MonitorMethod& method){
			Notify::notify(mPrefix + IComposition_monitorMethod);
			mMonitorMethod = method;
		}

		const char* IComposition_reportMethod = "_Composition.reportMethod";
		virtual ReportMethod getReportMethod(){ return mReportMethod; }
		virtual void setReportMethod(const ReportMethod& method){
			Notify::notify(mPrefix + IComposition_reportMethod);
			mReportMethod = method;
		}

		const char* IComposition_isManipulatedSetPoint = "_Composition.isManipulatedSetPoint";
		virtual bool isManipulatedSetPoint(){ return mIsManipulatedSetPoint; }
		virtual void setIsManipulatedSetPoint(bool val){
			Notify::notify(mPrefix + IComposition_isManipulatedSetPoint);
			mIsManipulatedSetPoint = val;
		}

		const char* IComposition_instabilityValPercent = "_Composition.instabilityValPercent";
		virtual double getInstabilityValPercent(){ return mInstabilityValPercent; }
		virtual bool setInstabilityValPercent(double val){
			try{
				Validate::validate(mPrefix + IComposition_instabilityValPercent, val);
				mInstabilityValPercent = val;
				return true;
			}
			catch (std::exception& e){
				//TODO: logging and mechachanism to pass info across DLL boundary...
				return false;
			}
		}

		const char* IComposition_heavyKey = "_Composition.hk";
		virtual std::string getHeavyKey(){ return mHK; }
		virtual bool setHeavyKey(const std::string& val){
			try{
				Validate::validate(mPrefix + IComposition_heavyKey, val);
				mHK = val;
				return true;
			}
			catch (std::exception& e){
				//TODO: logging and mechachanism to pass info across DLL boundary...
				return false;
			}
		}

		const char* IComposition_heavyKeyUnit = "_Composition.hkUnit";
		virtual std::string getHeavyKeyUnit(){ return mHKU; }
		virtual bool setHeavyKeyUnit(const std::string& val){
			try{
				Validate::validate(mPrefix + IComposition_heavyKeyUnit, val);
				mHKU = val;
				return true;
			}
			catch (std::exception& e){
				//TODO: logging and mechachanism to pass info across DLL boundary...
				return false;
			}
		}

		const char* IComposition_lightKey = "_Composition.lk";
		virtual std::string getLightKey(){ return mLK; }
		virtual bool setLightKey(const std::string& val){
			try{
				Validate::validate(mPrefix + IComposition_lightKey, val);
				mLK = val;
				return true;
			}
			catch (std::exception& e){
				//TODO: logging and mechachanism to pass info across DLL boundary...
				return false;
			}
		}

		const char* IComposition_lightKeyUnit = "_Composition.lkUnit";
		virtual std::string getLightKeyUnit(){ return mLKU; }
		virtual bool setLightKeyUnit(const std::string& val){
			try{
				Validate::validate(mPrefix + IComposition_lightKeyUnit, val);
				mLKU = val;
				return true;
			}
			catch (std::exception& e){
				//TODO: logging and mechachanism to pass info across DLL boundary...
				return false;
			}
		}

		const char* IComposition_analyzerTag = "_Composition.analyzerTag";
		virtual std::string getAnalyzerTag(){ return mAnalyzerTag; }
		virtual bool setAnalyzerTag(const std::string& val){
			try{
				Validate::validate(mPrefix + IComposition_analyzerTag, val);
				mAnalyzerTag = val;
				return true;
			}
			catch (std::exception& e){
				//TODO: logging and mechachanism to pass info across DLL boundary...
				return false;
			}
		}

		const char* IComposition_labTag = "_Composition.labTag";
		virtual std::string getLabTag(){ return mLabTag; }
		virtual bool setLabTag(const std::string& val){
			try{
				Validate::validate(mPrefix + IComposition_labTag, val);
				mLabTag = val;
				return true;
			}
			catch (std::exception& e){
				//TODO: logging and mechachanism to pass info across DLL boundary...
				return false;
			}
		}

		const char* IComposition_deltaTempTag = "_Composition.deltaTempTag";
		virtual std::string getDeltaTempTag(){ return mDeltaTempTag; }
		virtual bool setDeltaTempTag(const std::string& val){
			try{
				Validate::validate(mPrefix + IComposition_deltaTempTag, val);
				mDeltaTempTag = val;
				return true;
			}
			catch (std::exception& e){
				//TODO: logging and mechachanism to pass info across DLL boundary...
				return false;
			}
		}

		const char* IComposition_lowTempTag = "_Composition.lowTempTag";
		virtual std::string getLowTempTag(){ return mLowTempTag; }
		virtual bool setLowTempTag(const std::string& val){
			try{
				Validate::validate(mPrefix + IComposition_lowTempTag, val);
				mLowTempTag = val;
				return true;
			}
			catch (std::exception& e){
				//TODO: logging and mechachanism to pass info across DLL boundary...
				return false;
			}
		}

		const char* IComposition_highTempTag = "_Composition.highTempTag";
		virtual std::string getHighTempTag(){ return mHighTempTag; }
		virtual bool setHighTempTag(const std::string& val){
			try{
				Validate::validate(mPrefix + IComposition_highTempTag, val);
				mHighTempTag = val;
				return true;
			}
			catch (std::exception& e){
				//TODO: logging and mechachanism to pass info across DLL boundary...
				return false;
			}
		}

	protected:
		MonitorMethod   mMonitorMethod;
		ReportMethod    mReportMethod;
		bool            mIsManipulatedSetPoint;

		double          mInstabilityValPercent;
		std::string     mAnalyzerTag;
		std::string     mLabTag;
		std::string     mDeltaTempTag;
		std::string     mLowTempTag;
		std::string     mHighTempTag;

		std::string     mHK;
		std::string     mHKU;
		std::string     mLK;
		std::string     mLKU;

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			pt.put(mPrefix + IComposition_monitorMethod, (int)mMonitorMethod);
			pt.put(mPrefix + IComposition_isManipulatedSetPoint, mIsManipulatedSetPoint);
			pt.put(mPrefix + IComposition_reportMethod, (int)mReportMethod);
			pt.put(mPrefix + IComposition_heavyKey, mHK);
			pt.put(mPrefix + IComposition_heavyKeyUnit, mHKU);
			pt.put(mPrefix + IComposition_lightKey, mLK);
			pt.put(mPrefix + IComposition_lightKeyUnit, mLKU);
			pt.put(mPrefix + IComposition_instabilityValPercent, mInstabilityValPercent);
			pt.put(mPrefix + IComposition_analyzerTag, mAnalyzerTag);
			pt.put(mPrefix + IComposition_labTag, mLabTag);
			pt.put(mPrefix + IComposition_deltaTempTag, mDeltaTempTag);
			pt.put(mPrefix + IComposition_lowTempTag, mLowTempTag);
			pt.put(mPrefix + IComposition_highTempTag, mHighTempTag);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			mMonitorMethod = (MonitorMethod)pt.get<int>(mPrefix + IComposition_monitorMethod);
			mIsManipulatedSetPoint = pt.get<bool>(mPrefix + IComposition_isManipulatedSetPoint);
			mReportMethod = (ReportMethod)pt.get<int>(mPrefix + IComposition_reportMethod);
			mHK = pt.get<std::string>(mPrefix + IComposition_heavyKey);
			mHKU = pt.get<std::string>(mPrefix + IComposition_heavyKeyUnit);
			mLK = pt.get<std::string>(mPrefix + IComposition_lightKey);
			mLKU = pt.get<std::string>(mPrefix + IComposition_lightKeyUnit);
			mInstabilityValPercent = pt.get<double>(mPrefix + IComposition_instabilityValPercent);
			mAnalyzerTag = pt.get<std::string>(mPrefix + IComposition_analyzerTag);
			mLabTag = pt.get<std::string>(mPrefix + IComposition_labTag);
			mDeltaTempTag = pt.get<std::string>(mPrefix + IComposition_deltaTempTag);
			mLowTempTag = pt.get<std::string>(mPrefix + IComposition_lowTempTag);
			mHighTempTag = pt.get<std::string>(mPrefix + IComposition_highTempTag);
		}

		//not serialized
	public:

		virtual bool isManualLab()  {
			return (getMonitorMethod() == MonitorMethod::LAB_RESULT && getLabTag().empty());
		}

	private:
		std::string     mPrefix;
	};

}

#endif
