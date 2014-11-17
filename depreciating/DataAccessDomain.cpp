//
//  DataAccessDomain.cpp
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/12/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#include "DataAccessDomain.h"

const DataAccessDomain& DataAccessDomain::findDADFromKey(const std::string& key){

    if (key == DataAccessDomain::HEAVY_KEY_CURRENT.getKey())
        return DataAccessDomain::HEAVY_KEY_CURRENT;

    if (key == DataAccessDomain::HEAVY_KEY_MINUS_20.getKey())
        return DataAccessDomain::HEAVY_KEY_MINUS_20;
    
    if (key == DataAccessDomain::HEAVY_KEY_MINUS_40.getKey())
        return DataAccessDomain::HEAVY_KEY_MINUS_40;
    
    if (key == DataAccessDomain::LIGHT_KEY_CURRENT.getKey())
        return DataAccessDomain::LIGHT_KEY_CURRENT;
    
    if (key == DataAccessDomain::LIGHT_KEY_MINUS_20.getKey())
        return DataAccessDomain::LIGHT_KEY_MINUS_20;
    
    if (key == DataAccessDomain::LIGHT_KEY_MINUS_40.getKey())
        return DataAccessDomain::LIGHT_KEY_MINUS_40;
    
    if (key == DataAccessDomain::DELTA.getKey())
        return DataAccessDomain::DELTA;
    
    if (key == DataAccessDomain::SECONDARY_HEAVY_KEY_CURRENT.getKey())
        return DataAccessDomain::SECONDARY_HEAVY_KEY_CURRENT;
    
    if (key == DataAccessDomain::SECONDARY_HEAVY_KEY_MINUS_20.getKey())
        return DataAccessDomain::SECONDARY_HEAVY_KEY_MINUS_20;
    
    if (key == DataAccessDomain::SECONDARY_HEAVY_KEY_MINUS_40.getKey())
        return DataAccessDomain::SECONDARY_HEAVY_KEY_MINUS_40;
    
    if (key == DataAccessDomain::SECONDARY_LIGHT_KEY_CURRENT.getKey())
        return DataAccessDomain::SECONDARY_LIGHT_KEY_CURRENT;
    
    if (key == DataAccessDomain::SECONDARY_LIGHT_KEY_MINUS_20.getKey())
        return DataAccessDomain::SECONDARY_LIGHT_KEY_MINUS_20;
    
    if (key == DataAccessDomain::SECONDARY_LIGHT_KEY_MINUS_40.getKey())
        return DataAccessDomain::SECONDARY_LIGHT_KEY_MINUS_40;
    
    if (key == DataAccessDomain::SECONDARY_DELTA.getKey())
        return DataAccessDomain::SECONDARY_DELTA;
    
    if (key == DataAccessDomain::REFLUX.getKey())
        return DataAccessDomain::REFLUX;
    
    if (key == DataAccessDomain::FEED_FLOW_1.getKey())
        return DataAccessDomain::FEED_FLOW_1;
    
    if (key == DataAccessDomain::FEED_FLOW_2.getKey())
        return DataAccessDomain::FEED_FLOW_2;
    
    if (key == DataAccessDomain::FEED_FLOW_3.getKey())
        return DataAccessDomain::FEED_FLOW_3;
    
    if (key == DataAccessDomain::HEATING_MEDIUM_FLOW_1.getKey())
        return DataAccessDomain::HEATING_MEDIUM_FLOW_1;

    if (key == DataAccessDomain::HEATING_MEDIUM_FLOW_2.getKey())
        return DataAccessDomain::HEATING_MEDIUM_FLOW_2;
    
    if (key == DataAccessDomain::HEATING_MEDIUM_FLOW_3.getKey())
        return DataAccessDomain::HEATING_MEDIUM_FLOW_3;
    
    if (key == DataAccessDomain::OPERATING_PRESSURE.getKey())
        return DataAccessDomain::OPERATING_PRESSURE;
    
    if (key == DataAccessDomain::OUTPUT_ON_PIC.getKey())
        return DataAccessDomain::OUTPUT_ON_PIC;
    
    if (key == DataAccessDomain::PREVENTS_PRESSURE_DECREASE.getKey())
        return DataAccessDomain::PREVENTS_PRESSURE_DECREASE;
    
    if (key == DataAccessDomain::PREVENTS_PRESSURE_INCREASE.getKey())
        return DataAccessDomain::PREVENTS_PRESSURE_INCREASE;
    
    if (key == DataAccessDomain::PREVENTS_REBOIL_DECREASE.getKey())
        return DataAccessDomain::PREVENTS_REBOIL_DECREASE;
    
    if (key == DataAccessDomain::PREVENTS_REBOIL_INCREASE.getKey())
        return DataAccessDomain::PREVENTS_REBOIL_INCREASE;
    
    if (key == DataAccessDomain::PREVENTS_REFLUX_DECREASE.getKey())
        return DataAccessDomain::PREVENTS_REFLUX_DECREASE;

    if (key == DataAccessDomain::PREVENTS_REFLUX_INCREASE.getKey())
        return DataAccessDomain::PREVENTS_REFLUX_INCREASE;
    
    return DataAccessDomain::UNKNOWN;
}

const DataAccessDomain DataAccessDomain::UNKNOWN = DataAccessDomain("UNKNOWN");

const DataAccessDomain DataAccessDomain::HEAVY_KEY_CURRENT = DataAccessDomain("primaryInstruments.heavyKeyCurrent");

const DataAccessDomain DataAccessDomain::HEAVY_KEY_MINUS_20 = DataAccessDomain("primaryInstruments.heavyKeyMinus20");

const DataAccessDomain DataAccessDomain::HEAVY_KEY_MINUS_40 = DataAccessDomain("primaryInstruments.heavyKeyMinus40");

const DataAccessDomain DataAccessDomain::LIGHT_KEY_CURRENT = DataAccessDomain("primaryInstruments.lightKeyCurrent");

const DataAccessDomain DataAccessDomain::LIGHT_KEY_MINUS_20 = DataAccessDomain("primaryInstruments.lightKeyMinus20");

const DataAccessDomain DataAccessDomain::LIGHT_KEY_MINUS_40 = DataAccessDomain("primaryInstruments.lightKeyMinus40");

const DataAccessDomain DataAccessDomain::DELTA = DataAccessDomain("primaryInstruments.delta");

const DataAccessDomain DataAccessDomain::SECONDARY_HEAVY_KEY_CURRENT = DataAccessDomain("secondaryInstruments.heavyKeyCurrent");

const DataAccessDomain DataAccessDomain::SECONDARY_HEAVY_KEY_MINUS_20 = DataAccessDomain("secondaryInstruments.heavyKeyMinus20");

const DataAccessDomain DataAccessDomain::SECONDARY_HEAVY_KEY_MINUS_40 = DataAccessDomain("secondaryInstruments.heavyKeyMinus40");

const DataAccessDomain DataAccessDomain::SECONDARY_LIGHT_KEY_CURRENT = DataAccessDomain("secondaryInstruments.lightKeyCurrent");

const DataAccessDomain DataAccessDomain::SECONDARY_LIGHT_KEY_MINUS_20 = DataAccessDomain("secondaryInstruments.lightKeyMinus20");

const DataAccessDomain DataAccessDomain::SECONDARY_LIGHT_KEY_MINUS_40 = DataAccessDomain("secondaryInstruments.lightKeyMinus40");

const DataAccessDomain DataAccessDomain::SECONDARY_DELTA = DataAccessDomain("secondaryInstruments.delta");

const DataAccessDomain DataAccessDomain::REFLUX = DataAccessDomain("reflux");

const DataAccessDomain DataAccessDomain::FEED_FLOW_1 = DataAccessDomain("feedFlow1");

const DataAccessDomain DataAccessDomain::FEED_FLOW_2 = DataAccessDomain("feedFlow2");

const DataAccessDomain DataAccessDomain::FEED_FLOW_3 = DataAccessDomain("feedFlow3");

const DataAccessDomain DataAccessDomain::HEATING_MEDIUM_FLOW_1 = DataAccessDomain("heatingMediumFlow1");

const DataAccessDomain DataAccessDomain::HEATING_MEDIUM_FLOW_2 = DataAccessDomain("heatingMediumFlow2");

const DataAccessDomain DataAccessDomain::HEATING_MEDIUM_FLOW_3 = DataAccessDomain("heatingMediumFlow3");

const DataAccessDomain DataAccessDomain::OPERATING_PRESSURE = DataAccessDomain("operatingPressure");

const DataAccessDomain DataAccessDomain::OUTPUT_ON_PIC = DataAccessDomain("outputOnPIC");

// Overrides

const DataAccessDomain DataAccessDomain::PREVENTS_PRESSURE_DECREASE = DataAccessDomain("preventsPressureDecrease");

const DataAccessDomain DataAccessDomain::PREVENTS_PRESSURE_INCREASE = DataAccessDomain("preventsPressureIncrease");

const DataAccessDomain DataAccessDomain::PREVENTS_REBOIL_DECREASE = DataAccessDomain("preventsDecreaseInReboil");

const DataAccessDomain DataAccessDomain::PREVENTS_REBOIL_INCREASE = DataAccessDomain("preventsIncreaseInReboil");

const DataAccessDomain DataAccessDomain::PREVENTS_REFLUX_DECREASE = DataAccessDomain("preventsDecreaseInReflux");

const DataAccessDomain DataAccessDomain::PREVENTS_REFLUX_INCREASE = DataAccessDomain("preventsIncreaseInReflux");
