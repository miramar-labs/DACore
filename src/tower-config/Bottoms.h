//
//  Bottoms.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/15/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Bottoms_h
#define Distillation_Advisor_Bottoms_h

#include "stdafx.h"

#include "IBottoms.h"
#include "ITowerReport.h"
#include "IReboiler.h"
#include "IComposition.h"

namespace dacore {

	class Bottoms : public IBottoms {

	public:
		Bottoms(){
			Validate::registerStrPattern(IBottoms_heatingMediumOtherText, std::tuple<std::string, std::string, std::string>(Validate::REGEX_ALPHA_NUM, "", Validate::INVALID_STR));
		}

		virtual ~Bottoms(){ delete mComposition; delete mReboiler; }

		//IBottoms:
		const char* IBottoms_heatingMedium = "Bottoms.heatingMedium";
		virtual HeatingMedium getHeatingMedium(){ return mHeatingMedium; }
		virtual void setHeatingMedium(const HeatingMedium& medium){ mHeatingMedium = medium; }

		const char* IBottoms_heatingMediumOtherText = "Bottoms.heatingMediumOtherTxt";
		virtual std::string getHeatingMediumOtherText(){ return mHeatingMediumOtherText; }
		virtual bool setHeatingMediumOtherText(const std::string& text){ 
			try{
				Validate::validate(IBottoms_heatingMediumOtherText, text);
				mHeatingMediumOtherText = text;
				return true;
			}
			catch (std::exception& e){
				//TODO: logging and mechachanism to pass info across DLL boundary...
				return false;
			}
		}

		const char* IBottoms_Reboiler = "Bottoms.Reboiler";
		virtual IReboiler* getReboiler(){ return mReboiler; }
		virtual void setReboiler(IReboiler* reboiler){ mReboiler = reboiler; }

		const char* IBottoms_HeatingMediumFeeds = "Bottoms.HeatingMediumFeeds";
		virtual IFeeds* getHeatingMediumFeeds(){ return mFeeds; }

		//IHasComposition:
		const char* IBottoms_Composition = "Bottoms.Composition";
		virtual IComposition* getComposition(){ return mComposition; }

		virtual ITowerReport::Status getEffectiveStatus(ITowerReport::Status status){

			if (!isCompositionLogicReversed())
				return status;

			switch (status){
			case ITowerReport::Status::HIGH:
				return ITowerReport::Status::LOW;
			case ITowerReport::Status::ALMOST_HIGH:
				return ITowerReport::Status::ALMOST_LOW;
			case ITowerReport::Status::ALMOST_LOW:
				return ITowerReport::Status::ALMOST_HIGH;
			case ITowerReport::Status::LOW:
				return ITowerReport::Status::HIGH;
			default:
				return ITowerReport::Status::OK;
			}
		}

		virtual bool isCompositionLogicReversed(){//CHECKME !!!!
			if (isAnalysis()
				&& getComposition()->getReportMethod() == IComposition::ReportMethod::ASSAY)
				return false;
			else
				return true;
		}

	private:
		virtual void setComposition(IComposition* comp){ mComposition = comp; }

		virtual void setHeatingMediumFeeds(IFeeds* feeds){ mFeeds = feeds; }

	private:
		IComposition*   mComposition;
		IReboiler*      mReboiler;
		std::string     mHeatingMediumOtherText;
		HeatingMedium   mHeatingMedium;
		IFeeds*         mFeeds;

	public://TODO: protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			ISerialize::serializeObj(pt, IBottoms_Composition, mComposition);
			ISerialize::serializeObj(pt, IBottoms_Reboiler, mReboiler);
			ISerialize::serializeObj(pt, IBottoms_HeatingMediumFeeds, mFeeds);

			pt.put(IBottoms_heatingMediumOtherText, mHeatingMediumOtherText);
			pt.put(IBottoms_heatingMedium, (int)mHeatingMedium);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			ISerialize::deserializeObj(pt, IBottoms_Composition, mComposition);
			ISerialize::deserializeObj(pt, IBottoms_Reboiler, mReboiler);
			ISerialize::deserializeObj(pt, IBottoms_HeatingMediumFeeds, mFeeds);

			mHeatingMediumOtherText = pt.get<std::string>(IBottoms_heatingMediumOtherText);
			mHeatingMedium = (HeatingMedium)pt.get<int>(IBottoms_heatingMedium);
		}

	private:
		bool isAnalysis(){//CHECKME !!!
			return (getComposition()->getMonitorMethod() == IComposition::MonitorMethod::ANALYZER
				|| getComposition()->getMonitorMethod() == IComposition::MonitorMethod::LAB_RESULT);
		}

	};

}

#endif
