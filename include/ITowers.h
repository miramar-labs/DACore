//
//  ITowers.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/31/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_ITowers_h
#define Distillation_Advisor_ITowers_h

#include "dacommon.h"

namespace dacore {

	class DACORE_API ITowers : public ISerialize {

		friend class Manager;

	public:
		virtual ~ITowers(){}

		virtual TowerId count() = 0;

		virtual ITower* get(TowerId id) = 0;		
		
		virtual void enumerate(std::vector<TowerId>& towers) = 0;

	private:	//private to enforce ref-integrity rules up in Manager   
		virtual TowerId add(TowerId tid) = 0;

		virtual void	remove(TowerId id) = 0;
	};

}

#endif
