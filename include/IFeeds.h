//
//  IFeeds.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/30/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IFeeds_h
#define Distillation_Advisor_IFeeds_h

#include "dacommon.h"

#include "IFeed.h"

namespace dacore {

	class DACORE_API IFeeds : public ISerialize {

	public:
		virtual ~IFeeds(){}

		virtual FeedId count() = 0;

		virtual IFeed* get(FeedId id) = 0;

		virtual void enumerate(std::vector<FeedId>& feeds) = 0;

		virtual FeedId add(IFeed::Type t = IFeed::Type::DEFAULT) = 0;

		virtual void remove(FeedId id) = 0;
	};

}

#endif
