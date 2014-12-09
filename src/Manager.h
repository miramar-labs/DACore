//
//  DistillationTower.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 6/30/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef __DA_MANAGER_H__
#define __DA_MANAGER_H__

#include "stdafx.h"

#include "IManager.h"

namespace dacore {

	class Manager : public IManager {

		friend class Towers;

	public:
		virtual ~Manager();

	//Tower:
		virtual TowerId			createTower(HistorianId hid, ITower::Type type = ITower::Type::DISTILLATION);

		virtual bool			deleteTower(HistorianId hid, TowerId id);
		
		virtual ITower*			getTower(TowerId id);

		virtual void			enumerateTowers(std::vector<TowerId>& tids);	

		virtual IHistorian*		getHistorianOfTower(TowerId id);

		virtual bool			removeTowerFromHistorian(HistorianId hid, TowerId tid);

		virtual bool			addTowerToHistorian(HistorianId hid, TowerId tid);

	//Historian:
		virtual HistorianId		createHistorian(IHistorian::Type type = IHistorian::Type::PI);

		virtual bool			deleteHistorian(HistorianId id);

		virtual IHistorian*		getHistorian(HistorianId id);

		virtual void			enumerateHistorians(std::vector<HistorianId>& hids);	

	//Advisor:
		virtual IAdvice*		getAdvice(TowerId id);

	//Persistence:
		virtual void			loadTowers();
		virtual void			saveTowers();
		virtual bool			saveTower(TowerId id);

		virtual void			loadHistorians();
		virtual void			saveHistorians();
		virtual bool			saveHistorian(HistorianId id);

	};

}//namespace

#endif