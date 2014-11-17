//
//  IHasComposition.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/6/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_IHasComposition_h
#define Distillation_Advisor_IHasComposition_h

#include "dacommon.h"

#include "ITowerReport.h"

namespace dacore {

	class IComposition;

	class DACORE_API IHasComposition : public ISerialize {

	public:
		virtual ~IHasComposition(){}

		virtual IComposition* getComposition() = 0;

		virtual void setComposition(IComposition* comp) = 0;//TODO - private

		virtual bool isCompositionLogicReversed() = 0;

		virtual ITowerReport::Status getEffectiveStatus(ITowerReport::Status status) = 0;

	};

}

#endif
