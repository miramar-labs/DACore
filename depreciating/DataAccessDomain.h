//
//  DataAccessDomain.h
//  Distillation Advisor
//
//  Created by Aaron Cody on 7/12/14.
//  Copyright (c) 2014 JSA Labs. All rights reserved.
//

#ifndef __Distillation_Advisor__DataAccessDomain__
#define __Distillation_Advisor__DataAccessDomain__

#include <string>

class DataAccessDomain {
public:

    static const DataAccessDomain UNKNOWN;
    
    static const DataAccessDomain HEAVY_KEY_CURRENT;
    
    static const DataAccessDomain HEAVY_KEY_MINUS_20;
    
    static const DataAccessDomain HEAVY_KEY_MINUS_40;
    
    static const DataAccessDomain LIGHT_KEY_CURRENT;
    
    static const DataAccessDomain LIGHT_KEY_MINUS_20;
    
    static const DataAccessDomain LIGHT_KEY_MINUS_40;
    
    static const DataAccessDomain DELTA;
    
    static const DataAccessDomain SECONDARY_HEAVY_KEY_CURRENT;
    
    static const DataAccessDomain SECONDARY_HEAVY_KEY_MINUS_20;
    
    static const DataAccessDomain SECONDARY_HEAVY_KEY_MINUS_40;
    
    static const DataAccessDomain SECONDARY_LIGHT_KEY_CURRENT;
    
    static const DataAccessDomain SECONDARY_LIGHT_KEY_MINUS_20;
    
    static const DataAccessDomain SECONDARY_LIGHT_KEY_MINUS_40;
    
    static const DataAccessDomain SECONDARY_DELTA;
    
    static const DataAccessDomain REFLUX;
    
    static const DataAccessDomain FEED_FLOW_1;
    
    static const DataAccessDomain FEED_FLOW_2;
    
    static const DataAccessDomain FEED_FLOW_3 ;
    
    static const DataAccessDomain HEATING_MEDIUM_FLOW_1;
    
    static const DataAccessDomain HEATING_MEDIUM_FLOW_2;
    
    static const DataAccessDomain HEATING_MEDIUM_FLOW_3;
    
    static const DataAccessDomain OPERATING_PRESSURE;
    
    static const DataAccessDomain OUTPUT_ON_PIC;
    
    // Overrides
    
    static const DataAccessDomain PREVENTS_PRESSURE_DECREASE;
    
    static const DataAccessDomain PREVENTS_PRESSURE_INCREASE;
    
    static const DataAccessDomain PREVENTS_REBOIL_DECREASE;
    
    static const DataAccessDomain PREVENTS_REBOIL_INCREASE;
    
    static const DataAccessDomain PREVENTS_REFLUX_DECREASE;
    
    static const DataAccessDomain PREVENTS_REFLUX_INCREASE;

    
private:
    std::string mKey;
    
private:
    DataAccessDomain(const std::string& key) {
        this->mKey = key;
    }
    
public:
    bool operator==(const DataAccessDomain &other) const {
        return (mKey == other.mKey);
    }
    
public:
    const std::string& getKey() const {return mKey;}
    
    static const DataAccessDomain& findDADFromKey(const std::string& key);
    
};
#endif /* defined(__Distillation_Advisor__DataAccessDomain__) */
