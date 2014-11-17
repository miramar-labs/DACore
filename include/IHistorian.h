//
//  IHistorian.h
//
//  Created by Aaron Cody on 7/26/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor__IHistorian_h
#define Distillation_Advisor__IHistorian_h

#include "dacommon.h"

namespace dacore {
	
//helpers (h=IHistorian*):
#define TOWERS(h) h->getTowers()

	class ITowers;

	typedef unsigned long HistorianId;

	class DACORE_API IHistorian : public ISerialize {

	public:
		virtual ~IHistorian(){}

		enum Type	{ FILE_DEMO, PI, IP21 };

		virtual Type getType() = 0;
		virtual void setType(Type type) = 0;

		virtual std::string getServer() = 0;
		virtual void setServer(const std::string& server) = 0;

		virtual ITowers* getTowers() = 0;
		virtual void setTowers(ITowers* towers) = 0;        //TODO - private

		//TODO virtual std::string getDataSource() = 0;
		//TODO	HistorianQueryResult query(HistorianQuery query) throws HistorianException;

		virtual HistorianId		getId() = 0;
		virtual void            setId(HistorianId id) = 0;	//TODO - remove?

	};

}//namespace

extern "C" DACORE_API const char* DACORE_APIENTRY HistorianTypeStr(dacore::IHistorian::Type t);

#endif
