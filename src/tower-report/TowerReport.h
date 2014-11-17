//
//  TowerReport.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/11/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_TowerReport_h
#define Distillation_Advisor_TowerReport_h

#include "stdafx.h"

#include "DTHeavyKeyReportItem.h"
#include "DTLightKeyReportItem.h"
#include "DTDeltaReportItem.h"
#include "DTRefluxReportItem.h"
#include "DTFeedReportItem.h"
#include "DTHeatingReportItem.h"
#include "DTOperatingPressureReportItem.h"
#include "DTOutputOnPICReportItem.h"

#include "ITowerReport.h"

namespace dacore {

	class IReportItem;

	class TowerReport : public ITowerReport {

	public:
		TowerReport(ITowerConfig* config, ITowerData* data){
			switch (config->getType()){
			case ITower::Type::DISTILLATION:
				mHK = new DTHeavyKeyReportItem(config, data);
				mLK = new DTLightKeyReportItem(config, data);
				mDelta = new DTDeltaReportItem(config, data);;
				mReflux = new DTRefluxReportItem(config, data);
				mFeed = new DTFeedReportItem(config, data);
				mHeating = new DTHeatingReportItem(config, data);
				mOP = new DTOperatingPressureReportItem(config, data);
				mOPIC = new DTOutputOnPICReportItem(config, data);
				break;
			default:
				assert(false);
			}
		}

		virtual ~TowerReport(){ delete mHK; delete mLK; delete mDelta; delete mReflux; delete mFeed; delete mHeating; }

		virtual IReportItem* getHeavyKey(){ return mHK; }
		virtual void setHeavyKey(IReportItem* item){ mHK = item; }

		virtual IReportItem* getLightKey(){ return mLK; }
		virtual void setLightKey(IReportItem* item){ mLK = item; }

		virtual IReportItem* getDelta(){ return mDelta; }
		virtual void setDelta(IReportItem* item){ mDelta = item; }

		virtual IReportItem* getReflux(){ return mReflux; }
		virtual void setReflux(IReportItem* item){ mReflux = item; }

		virtual IReportItem* getFeed(){ return mFeed; }
		virtual void setFeed(IReportItem* item){ mFeed = item; }

		virtual IReportItem* getHeating(){ return mHeating; }
		virtual void setHeating(IReportItem* item){ mHeating = item; }

		virtual IReportItem* getOperatingPressure(){ return mOP; }
		virtual void setOperatingPressure(IReportItem* item){ mOP = item; }

		virtual IReportItem* getOutputOnPIC(){ return mOPIC; }
		virtual void setOutputOnPIC(IReportItem* item){ mOPIC = item; }

	private:
		IReportItem*    mHK;
		IReportItem*    mLK;
		IReportItem*    mDelta;
		IReportItem*    mReflux;
		IReportItem*    mFeed;
		IReportItem*    mHeating;
		IReportItem*    mOP;
		IReportItem*    mOPIC;

	public://protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			ISerialize::serializeObj(pt, "TowerReport.HK", mHK);
			ISerialize::serializeObj(pt, "TowerReport.LK", mLK);
			ISerialize::serializeObj(pt, "TowerReport.Delta", mDelta);
			ISerialize::serializeObj(pt, "TowerReport.Reflux", mReflux);
			ISerialize::serializeObj(pt, "TowerReport.Feed", mFeed);
			ISerialize::serializeObj(pt, "TowerReport.Heating", mHeating);
			ISerialize::serializeObj(pt, "TowerReport.OperatingPressure", mOP);
			ISerialize::serializeObj(pt, "TowerReport.OutputOnPIC", mOPIC);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			ISerialize::deserializeObj(pt, "TowerReport.HK", mHK);
			ISerialize::deserializeObj(pt, "TowerReport.LK", mLK);
			ISerialize::deserializeObj(pt, "TowerReport.Delta", mDelta);
			ISerialize::deserializeObj(pt, "TowerReport.Reflux", mReflux);
			ISerialize::deserializeObj(pt, "TowerReport.Feed", mFeed);
			ISerialize::deserializeObj(pt, "TowerReport.Heating", mHeating);
			ISerialize::deserializeObj(pt, "TowerReport.OperatingPressure", mOP);
			ISerialize::deserializeObj(pt, "TowerReport.OutputOnPIC", mOPIC);
		}
	};

}

#endif
