//
//  Overrides.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/11/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_AdviceOverrideSet_h
#define Distillation_Advisor_AdviceOverrideSet_h

#include "stdafx.h"

#include "IOverrides.h"
#include "IOverride.h"

#include "AdvisorFactory.h"

namespace dacore {

	class Overrides : public IOverrides {
	public:

		virtual ~Overrides(){}//TODO: cleanup 

		//IOverrides:
		virtual OverrideId count(){
			return mOverrides.size();
		}

		virtual IOverride* get(OverrideId id){
			if (mOverrides.find(id) == mOverrides.end())
				return NULL;
			else{
				std::map<OverrideId, IOverride*>::iterator it = mOverrides.find(id);
				return (*it).second;
			}
		}

		virtual void enumerate(std::vector<OverrideId>& overrides){
			overrides.clear();
			for (std::map<OverrideId, IOverride*>::iterator it = mOverrides.begin(); it != mOverrides.end(); ++it)
				overrides.push_back((*it).first);
		}

		virtual OverrideId add(){
			OverrideId maxid = 0;
			for (std::map<OverrideId, IOverride*>::iterator it = mOverrides.begin(); it != mOverrides.end(); ++it)
				maxid = std::max(maxid, (*it).first);
			IOverride* ov = AdvisorFactory::create(maxid + 1);
			mOverrides.insert(std::pair<int, IOverride*>(ov->getId(), ov));
			return ov->getId();
		}

		virtual void remove(OverrideId id){
			mOverrides.erase(id);
		}		
		
	//helpers:
		virtual bool willTripFor(IOverride::PreventTarget target, double value){
			IOverride* override = this->find(target);
			if (override == NULL)
				return false;
			if (!override->isEnabled())
				return false;
			return override->willTripFor(value);
		}

		virtual IOverride* find(IOverride::PreventTarget target){
			for (std::map<OverrideId, IOverride*>::iterator it = mOverrides.begin(); it != mOverrides.end(); ++it){
				if ((*it).second->getPreventTarget() == target)
					return (*it).second;
			}
			return nullptr;
		}



	private:
		std::map<OverrideId, IOverride*>    mOverrides;

		//ISerialize:
	public:
		virtual void serialize(boost::property_tree::ptree& pt){
			for (std::map<OverrideId, IOverride*>::iterator it = mOverrides.begin(); it != mOverrides.end(); ++it){
				std::string tag = "override-" + std::to_string((*it).first);
				IOverride* ov = (*it).second;
				ISerialize::serializeObj(pt, tag, ov);
			}
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			bool done = false;
			int idx = 1;
			do {
				std::string tag = "override-" + std::to_string(idx);

				try{
					IOverride* ovr = nullptr;
					std::map<OverrideId, IOverride*>::iterator it = mOverrides.find((OverrideId)idx);
					if (it != mOverrides.end()){
						ovr = (*it).second;
						ISerialize::deserializeObj(pt, tag, ovr);
					}
					else{
						ovr = AdvisorFactory::create();
						ISerialize::deserializeObj(pt, tag, ovr);
						mOverrides.insert(std::pair<int, IOverride*>(ovr->getId(), ovr));
					}

				}
				catch (...){
					done = true;
				}

				idx++;

			} while (!done);
		}
	};

}

#endif

