#include "stdafx.h"

#include "ISerialize.h"

namespace dacore {

	void ISerialize::serializeObj(boost::property_tree::ptree& pt, const std::string& tag, ISerialize* obj){
		boost::property_tree::ptree tmp;
		obj->serialize(tmp);
		pt.put_child(tag, tmp);
	}

	void ISerialize::deserializeObj(boost::property_tree::ptree& pt, const std::string& tag, ISerialize* obj){
		obj->deserialize(pt.get_child(tag));
	}

}//namespace