#ifndef DA_ISERIALIZE_H
#define DA_ISERIALIZE_H

#include "dacommon.h"

namespace dacore {

	class  ISerialize
	{
		friend class Manager;
#ifdef UNIT_TESTING		
		friend class BasicUnitTests;
#endif
	public:
		virtual ~ISerialize(){}

	protected:
		virtual void serialize(boost::property_tree::ptree& pt) = 0;		
		virtual void deserialize(boost::property_tree::ptree& pt) = 0;	

		static void serializeObj(boost::property_tree::ptree& pt, const std::string& tag, ISerialize* obj);
		static void deserializeObj(boost::property_tree::ptree& pt, const std::string& tag, ISerialize* obj);
	};

}

#endif