//
//  TowerConfigFactory.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/9/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_TowerConfigFactory_h
#define Distillation_Advisor_TowerConfigFactory_h

#include "stdafx.h"

#include "TowerConfig.h"

#include "Bottoms.h"
#include "Overhead.h"
#include "Feeds.h"
#include "Feed.h"
#include "Column.h"
#include "Overrides.h"
#include "Composition.h"
#include "Reboiler.h"
#include "ExternalReflux.h"
#include "Override.h"
#include "ControlLimits.h"
#include "HeatingMediumFeed.h"

#pragma message( "TODO: fix TowerConfigFactory impl")

namespace dacore {

	class TowerConfigFactory {

	public:
		static IFeed* createFeed(IFeed::Type type=IFeed::Type::DEFAULT, FeedId id=0){   //FIXME !!!
			IFeed* feed;
			switch (type){
			case IFeed::Type::HEATINGMEDIUM:
				feed = new HeatingMediumFeed(id);
				break;
			default:
				feed = new Feed(id);
				break;
			}
			return feed;
		}

		static ITowerConfig* create(){

			ITowerConfig* config = new TowerConfig();

			config->setType(ITower::Type::DISTILLATION);

			IBottoms* bottoms = new Bottoms();
			config->setBottoms(bottoms);
			IComposition*  comp = new Composition("Bottoms");
			bottoms->setComposition(comp);
			IReboiler*     reboiler = new Reboiler();
			bottoms->setReboiler(reboiler);

			IOverhead* overhead = new Overhead();
			config->setOverhead(overhead);
			IComposition*  comp2 = new Composition("Overhead");
			overhead->setComposition(comp2);
			IExternalReflux*  ext = new ExternalReflux();
			overhead->setExternalReflux(ext);

			// set feeds on tower
			IFeeds* feeds = new Feeds();
			feeds->add();   // add 3 feeds by default....
			feeds->add();
			feeds->add();
			config->setFeeds(feeds);

			// set heating medium feeds on bottoms:
			IFeeds* hmfeeds = new Feeds();
			hmfeeds->add(IFeed::Type::HEATINGMEDIUM);   // add 3 heating medium feeds by default....
			hmfeeds->add(IFeed::Type::HEATINGMEDIUM);
			hmfeeds->add(IFeed::Type::HEATINGMEDIUM);
			bottoms->setHeatingMediumFeeds(hmfeeds);

			IColumn* column = new Column();
			config->setColumn(column);

			IOverrides* overrides = new Overrides();
			config->setOverrides(overrides);

			IControlLimits* limits = new ControlLimits();
			limits->setRefluxLimitType(IControlLimits::RefluxLimitType::REFLUX_FEED);
			config->setControlLimits(limits);

			return config;
		}

		static ITowerConfig* createDTPrime(){

			ITowerConfig* config = TowerConfigFactory::create();

			config->setType(ITower::Type::DISTILLATION);

			config->setName("12D1");
			config->setIsInactive(false);
			config->setIsIncomplete(false);

			IFeeds* feeds = config->getFeeds();
			std::vector<FeedId> fids;
			feeds->enumerate(fids);
			for (std::vector<FeedId>::iterator it = fids.begin(); it != fids.end(); it++){
				IFeed* f = feeds->get(*it);
				std::string tag = "feed-" + std::to_string(*it);
				f->setName(tag);
				f->setInstrumentTag("12VP.IP");
				f->setEngUnit("PPH");
				f->setFactor(1.0);
			}

			//overhead:
			IExternalReflux*  ovhReflux = config->getOverhead()->getExternalReflux();
			ovhReflux->setConfigured(true);
			ovhReflux->setLevelControl(false);
			ovhReflux->setFlowFactor(1.0);
			ovhReflux->setIncreaseMethod(IExternalReflux::IncreaseMethod::INC_REFLUX_FLOW);
			ovhReflux->setDecreaseMethod(IExternalReflux::DecreaseMethod::DEC_REFLUX_FLOW);

			IComposition*     ovhComp = config->getOverhead()->getComposition();
			ovhComp->setMonitorMethod(IComposition::MonitorMethod::TEMPERATURE);
			ovhComp->setInstabilityValPercent(0.2);
			ovhComp->setIsManipulatedSetPoint(false);

			IColumn* column = config->getColumn();
			column->setForecastingTimeline(IColumn::ForecastingTimeline::FORTY_MINUTE);
			column->setUsePressureOrTemperatureDelta(IColumn::DeltaOption::PRESSURE);

			IControlLimits* limits = config->getControlLimits();

			limits->setDeltaInstrumentMin(1.5);
			limits->setFeedMin(200000.0);
			limits->setHeatingMediumFlowMin(20000.0);
			limits->setHeavyKeyMin(90.0);
			limits->setLightKeyMin(2.0);
			limits->setRefluxMin(0.4);
			limits->setOperatingPressureMin(3.0);
			limits->setPressureControllerMin(0.0);

			limits->setDeltaInstrumentMax(3.5);
			limits->setFeedMax(450000.0);
			limits->setHeatingMediumFlowMax(50000.0);
			limits->setHeavyKeyMax(100.0);
			limits->setLightKeyMax(3.0);
			limits->setRefluxMax(0.55);
			limits->setOperatingPressureMax(7.0);
			limits->setPressureControllerMax(100.0);

			limits->setRefluxLimitType(IControlLimits::RefluxLimitType::REFLUX_FEED);

			IBottoms* bottoms = config->getBottoms();
			IFeeds* hmfeeds = bottoms->getHeatingMediumFeeds();
			std::vector<FeedId> hmfids;
			hmfeeds->enumerate(hmfids);
			for (std::vector<FeedId>::iterator it = hmfids.begin(); it != hmfids.end(); it++){
				IHeatingMediumFeed* f = (IHeatingMediumFeed*)(hmfeeds->get(*it));
				std::string tag = "hmfeed-" + std::to_string(*it);
				f->setName(tag);
				f->setInstrumentTag("12VP.IP");
				f->setEngUnit("PPH");
				f->setFactor(1.0);
				f->setBtuPerUnit(0);
			}

			IComposition*   btmComp = config->getBottoms()->getComposition();
			btmComp->setMonitorMethod(IComposition::MonitorMethod::ANALYZER);
			btmComp->setReportMethod(IComposition::ReportMethod::LIGHT_KEY_CONTENT);
			btmComp->setInstabilityValPercent(0.2);
			btmComp->setIsManipulatedSetPoint(false);

			IReboiler*      btmReboiler = config->getBottoms()->getReboiler();
			btmReboiler->setDecreaseMethod(IReboiler::DecreaseMethod::DEC_HM_FEED_RATIO);
			btmReboiler->setIncreaseMethod(IReboiler::IncreaseMethod::INC_HM_FLOW);

			// advice overrides:
			IOverrides* overrides = config->getOverrides();

			OverrideId id = overrides->add();
			
			overrides->get(id)->setPreventTarget(IOverride::PreventTarget::PRESSURE_DECREASE);
			overrides->get(id)->setTripPointOp(IOverride::TripPointOperator::GREATER_THAN);
			overrides->get(id)->setTripPoint(15.0);

			return config;
		}

	};

}

#endif


