//
//  Feeds.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/30/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Feeds_h
#define Distillation_Advisor_Feeds_h

#include "stdafx.h"

#include "IFeed.h"
#include "IFeeds.h"

//#include "TowerConfigFactory.h"         FIXME !!!
#include "Feed.h"
#include "HeatingMediumFeed.h"

#pragma message ("FIX this!")

namespace dacore {

	class Feeds : public IFeeds {

	public:
		virtual ~Feeds(){
			//TODO cleanup 
		}

		static IFeed* createFeed2(IFeed::Type type = IFeed::Type::DEFAULT, FeedId id = 0){		//FIXME !!!
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

		virtual FeedId count(){
			return mFeeds.size();
		}

		virtual IFeed* get(FeedId id){
			if (mFeeds.find(id) == mFeeds.end())
				return NULL;
			else{
				std::map<FeedId, IFeed*>::iterator it = mFeeds.find(id);
				return (*it).second;
			}
		}

		virtual void enumerate(std::vector<FeedId>& feeds){
			feeds.clear();
			for (std::map<FeedId, IFeed*>::iterator it = mFeeds.begin(); it != mFeeds.end(); ++it)
				feeds.push_back((*it).first);
		}

		virtual FeedId add(IFeed::Type type){
			IFeed* feed = nullptr;

			FeedId maxid = 0;
			for (std::map<FeedId, IFeed*>::iterator it = mFeeds.begin(); it != mFeeds.end(); ++it)
				maxid = std::max(maxid, (*it).first);

			feed = Feeds::createFeed2(type, maxid + 1);

			mFeeds.insert(std::pair<int, IFeed*>(feed->getId(), feed));
			return feed->getId();
		}

		virtual void remove(FeedId fid){
			mFeeds.erase(fid);
		}

		//ISerialize:
	public:
		virtual void serialize(boost::property_tree::ptree& pt){
			for (std::map<FeedId, IFeed*>::iterator it = mFeeds.begin(); it != mFeeds.end(); ++it){
				std::string tag = "feed-" + std::to_string((*it).first);
				IFeed* feed = (*it).second;
				ISerialize::serializeObj(pt, tag, feed);
			}
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			bool done = false;
			int idx = 1;
			do {
				std::string tag = "feed-" + std::to_string(idx);

				try{
					IFeed* feed = nullptr;
					std::map<FeedId, IFeed*>::iterator it = mFeeds.find((FeedId)idx);
					if (it != mFeeds.end()){
						feed = (*it).second;
						ISerialize::deserializeObj(pt, tag, feed);
					}
					else{
						feed = Feeds::createFeed2();
						ISerialize::deserializeObj(pt, tag, feed);
						mFeeds.insert(std::pair<int, IFeed*>(feed->getId(), feed));
					}

				}
				catch (...){
					done = true;
				}

				idx++;

			} while (!done);
		}

	private:
		std::map<FeedId, IFeed*>    mFeeds;
	};

}

#endif

