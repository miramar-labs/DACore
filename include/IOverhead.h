//
//  IOverhead.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IOverhead_h
#define Distillation_Advisor_IOverhead_h

#include "dacommon.h"
#include "IHasComposition.h"

namespace dacore {

	class IExternalReflux;

	class DACORE_API IOverhead : public IHasComposition {

		friend class TowerConfigFactory;

	public:
		virtual ~IOverhead(){}

		virtual IExternalReflux* getExternalReflux() = 0;

	private:
		virtual void setExternalReflux(IExternalReflux* ext) = 0;

	};

}

#endif
