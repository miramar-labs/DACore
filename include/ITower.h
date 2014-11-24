//
//  ITower.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 6/30/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//
//

#ifndef Distillation_Advisor_ITower_h
#define Distillation_Advisor_ITower_h

#include "dacommon.h"

namespace dacore {

//helpers (t=ITower*):
#define CONFIG(t) t->getConfig()
#define DATA(t) t->getData()
#define DATA_PINST(t) t->getData()->getPrimaryInstruments()
#define OVERHEAD_COMPOSITION(t) t->getConfig()->getOverhead()->getComposition()
#define OVERRIDES(t) t->getConfig()->getOverrides()
#define CONTROL_LIMITS(t) t->getConfig()->getControlLimits()
#define FEEDS(t) t->getConfig()->getFeeds()
#define COLUMN(t) t->getConfig()->getColumn()
#define BOTTOMS(t) t->getConfig()->getBottoms()
#define BOTTOMS_COMPOSITION(t) t->getConfig()->getBottoms()->getComposition()
#define REBOILER(t) t->getConfig()->getBottoms()->getReboiler()
#define OVERHEAD(t) t->getConfig()->getOverhead()
#define OVERHEAD_COMPOSITION(t) t->getConfig()->getOverhead()->getComposition()
#define REFLUX(t) t->getConfig()->getOverhead()->getExternalReflux()

class ITowerData;
class ITowerReport;
class ITowerConfig;
class IComposition;

	typedef unsigned long TowerId;

	class DACORE_API ITower : public ISerialize {

	public:
		virtual ~ITower(){}

		enum Type { DISTILLATION
//					,AMINE_ABSORBER
					,DTPRIME				//TODO: remove this
				  };

		virtual ITower::Type getType() = 0;
		virtual void setType(ITower::Type type) = 0;

		virtual std::string     getName() = 0;
		virtual void            setName(const std::string& name) = 0;

		virtual ITowerData*     getData() = 0;
		virtual void            setData(ITowerData* data) = 0;

		virtual ITowerConfig*   getConfig() = 0;
		virtual void            setConfig(ITowerConfig* config) = 0;

		virtual ITowerReport*   getReport() = 0;
		virtual void            setReport(ITowerReport* report) = 0;

		virtual TowerId			getId() = 0;
		virtual void            setId(TowerId id) = 0;	//TODO: remove?

	};

}//namespace

extern "C" DACORE_API const char* DACORE_APIENTRY TowerTypeStr(dacore::ITower::Type t);

#endif
