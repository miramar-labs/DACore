//
//  IManager.h
//
//  Created by Aaron Cody on 11/26/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//
#ifndef DACORE_IMANAGER_H
#define DACORE_IMANAGER_H

#include "dacommon.h"

#include "ITower.h"
#include "IHistorian.h"
#include "IFeed.h"
#include "IOverride.h"

namespace dacore {

	class IAdvice;
	class IControlLimits;
	class IColumn;
	class IBottoms;
	class IComposition;
	class IReboiler;
	class IOverhead;
	class IExternalReflux;
	class IFeed;

	// collections:
	class ITowers;				// towers associated with a historian
	class IOverrides;			// overrides associated with a tower
	class IFeeds;				// feeds associated with a tower

	class DACORE_API IManager
	{
	public:
		virtual ~IManager(){}

	//Historian:
		/*
			creates a historian
		*/
		virtual HistorianId		createHistorian(IHistorian::Type type = IHistorian::Type::PI) = 0;

		/*
			deletes a historian - will fail if it has any associated towers
		*/
		virtual bool			deleteHistorian(HistorianId id) = 0;

		/*
			gets a historian from the global map - HistorianIds are globally unique
		*/
		virtual IHistorian*		getHistorian(HistorianId id) = 0;

		/*
			enumerates all known historians
		*/
		virtual void			enumerateHistorians(std::vector<HistorianId>& hids) = 0;

		/*
			de-associates a tower from a historian 
		*/
		bool					removeTowerFromHistorian(HistorianId hid, TowerId tid);

	//Tower:
		/*
			creates a tower and associates it with a historian
		*/
		virtual TowerId			createTower(HistorianId hid, ITower::Type type = ITower::Type::DISTILLATION) = 0;

		/*
			deletes a tower from a historian
		*/
		virtual bool			deleteTower(HistorianId hid, TowerId id) = 0;

		/* 
			gets a tower from the global map - TowerIds are globally unique (across historians)
		*/
		virtual ITower*			getTower(TowerId id) = 0;	

		/* 
			enumerates all known towers (across all historians)
		*/
		virtual void			enumerateTowers(std::vector<TowerId>& tids) = 0;	

		/* 
			finds the historian associated with this tower
		*/
		virtual IHistorian*		getHistorianOfTower(TowerId id) = 0;

	//Advisor:
		virtual IAdvice*		getAdvice(TowerId id) = 0;

	//Persistence:
		virtual void			loadTowers() = 0;
		virtual void			saveTowers() = 0;
		virtual bool			saveTower(TowerId id) = 0;

		virtual void			loadHistorians() = 0;
		virtual void			saveHistorians() = 0;
		virtual bool			saveHistorian(HistorianId id) = 0;
	};

}// namespace

extern "C" DACORE_API dacore::IManager* DACORE_APIENTRY getManager();

#endif
