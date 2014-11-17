//
//  Overhead.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/9/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Overhead_h
#define Distillation_Advisor_Overhead_h

#include "stdafx.h"

#include "ITowerReport.h"
#include "IOverhead.h"

#include "IComposition.h"
#include "IExternalReflux.h"

namespace dacore {

	class Overhead : public IOverhead {

	public:
		virtual ~Overhead(){ delete mExtReflux; delete mComp; }

		//IOverhead:
		const char* IOverhead_externalReflux = "Overhead.ExternalReflux";
		virtual IExternalReflux* getExternalReflux(){ return mExtReflux; }
		virtual void setExternalReflux(IExternalReflux* ext){ mExtReflux = ext; }

		//IHasComposition:
		const char* IOverhead_composition = "Overhead.Composition";
		virtual IComposition* getComposition(){ return mComp; }
		virtual void setComposition(IComposition* comp){ mComp = comp; }

		virtual bool isCompositionLogicReversed(){ return mComp->getReportMethod() == IComposition::ReportMethod::ASSAY; }

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

	protected:
		IExternalReflux*    mExtReflux;
		IComposition*       mComp;

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			ISerialize::serializeObj(pt, IOverhead_externalReflux, mExtReflux);
			ISerialize::serializeObj(pt, IOverhead_composition, mComp);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			ISerialize::deserializeObj(pt, IOverhead_externalReflux, mExtReflux);
			ISerialize::deserializeObj(pt, IOverhead_composition, mComp);
		}
	};

}

#endif
