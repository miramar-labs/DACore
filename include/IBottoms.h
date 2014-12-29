//
//  IBottoms.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/15/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IBottoms_h
#define Distillation_Advisor_IBottoms_h

#include "dacommon.h"
#include "IHasComposition.h"

namespace dacore {

	class IComposition;
	class IReboiler;
	class IFeeds;

	class DACORE_API IBottoms : public IHasComposition {

		friend class TowerConfigFactory;
		friend class TowerConfig;

	public:
		virtual ~IBottoms(){}

		enum HeatingMedium { STEAM, HOT_OIL, OTHER };

		virtual HeatingMedium getHeatingMedium() = 0;
		virtual void setHeatingMedium(const HeatingMedium& medium) = 0;

		virtual std::string getHeatingMediumOtherText() = 0;
		virtual bool setHeatingMediumOtherText(const std::string& text) = 0;

		virtual IReboiler* getReboiler() = 0;

		virtual IFeeds* getHeatingMediumFeeds() = 0;

	private:
		virtual void setReboiler(IReboiler* reboiler) = 0;
		virtual void setHeatingMediumFeeds(IFeeds* feeds) = 0;

	};

}

#endif
