//
//  Column.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/9/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef Distillation_Advisor_Column_h
#define Distillation_Advisor_Column_h

#include "stdafx.h"

#include "IColumn.h"

namespace dacore {

	class Column : public IColumn {

	public:
		virtual ~Column(){}

		const char* IColumn_isUsingOvhToDetermineLoading = "Column.isUsingOvhToDetermineLoading";
		virtual bool isUsingOverheadKeyToDetermineTowerLoading(){ return mUsingOHK; }
		virtual void setIsUsingOverheadKeyToDetermineTowerLoading(bool isUsing){ mUsingOHK = isUsing; }

		const char* IColumn_usePressureOrTempDelta = "Column.usePressureOrTempDelta";
		virtual DeltaOption getUsePressureOrTemperatureDelta(){ return mDeltaOption; }
		virtual void setUsePressureOrTemperatureDelta(DeltaOption opt){ mDeltaOption = opt; }

		const char* IColumn_forecatsingTimeline = "Column.forecatsingTimeline";
		virtual ForecastingTimeline getForecastingTimeline(){ return mForecastingTimeline; }
		virtual void setForecastingTimeline(ForecastingTimeline tl){ mForecastingTimeline = tl; }

		const char* IColumn_isSuggestChanges = "Column.isSuggestChanges";
		virtual bool isSuggestChanges() { return mSuggestChanges; }
		virtual void setIsSuggestChanges(bool suggest) { mSuggestChanges = suggest; }

		const char* IColumn_isPressureReverseActing = "Column.isPressureReverseActing";
		virtual bool isPressureReverseActing() { return mPressureReverseActing; }
		virtual void setIsPressureReverseActing(bool revActing) {mPressureReverseActing = revActing;}

	protected:
		bool                mUsingOHK;
		DeltaOption         mDeltaOption;
		ForecastingTimeline mForecastingTimeline;
		bool				mSuggestChanges;
		bool				mPressureReverseActing;

	public://TODO: protected:
		//ISerialize:
		virtual void serialize(boost::property_tree::ptree& pt){
			pt.put(IColumn_isUsingOvhToDetermineLoading, mUsingOHK);
			pt.put(IColumn_usePressureOrTempDelta, (int)mDeltaOption); 
			pt.put(IColumn_forecatsingTimeline, (int)mForecastingTimeline); 
			pt.put(IColumn_isSuggestChanges, mSuggestChanges);
			pt.put(IColumn_isPressureReverseActing, mPressureReverseActing);
		}

		virtual void deserialize(boost::property_tree::ptree& pt){
			mUsingOHK = pt.get<bool>(IColumn_isUsingOvhToDetermineLoading);
			mDeltaOption = (DeltaOption)pt.get<int>(IColumn_usePressureOrTempDelta); 
			mForecastingTimeline = (ForecastingTimeline)pt.get<int>(IColumn_forecatsingTimeline); 
			mSuggestChanges = pt.get<bool>(IColumn_isSuggestChanges);
			mPressureReverseActing = pt.get<bool>(IColumn_isPressureReverseActing);
		}
	};

}

#endif
