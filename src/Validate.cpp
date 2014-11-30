#include "stdafx.h"

#include "Validate.h"
#include "Notify.h"

namespace dacore{
 
const char* Validate::REGEX_ALPHA_NUM = ""; //TODO
const char* Validate::INVALID_STR = "<INVALID>";
const double Validate::INVALID_DBL = std::numeric_limits<double>::max();
const double Validate::MAX_DBL = std::numeric_limits<double>::max()-1;


std::map<std::string, std::tuple<std::string, std::string, std::string> >	mPropStrValidationMap;		// map of property 'name' to {regex, default, invalid}
std::map<std::string, std::tuple<double, double, double, double> >			mPropNumValidationMap;		// map of property 'name' to {min, max, default, invalid}

void Validate::registerStrPattern(const std::string& id, std::tuple<std::string, std::string, std::string> pattern){
	mPropStrValidationMap[id] = pattern;
}

void Validate::registerNumPattern(const std::string& id, std::tuple<double, double, double, double> pattern){
	mPropNumValidationMap[id] = pattern;
}

void Validate::validate(const std::string& pname, const std::string& val){
	std::map<std::string, std::tuple<std::string, std::string, std::string> >::iterator it = mPropStrValidationMap.find(pname);
	if (it == mPropStrValidationMap.end())
		throw new std::exception();//TODO - unknown property
	std::string reg = std::get<0>((*it).second);
	//TODO ...validate val against regex....

	Notify::notify(pname);
}

void Validate::validate(const std::string& pname, double val){
	std::map<std::string, std::tuple<double, double, double, double> >::iterator it = mPropNumValidationMap.find(pname);
	if (it == mPropNumValidationMap.end())
		throw new std::exception();//TODO - unknown property
	if (!((val >= std::get<0>((*it).second)) || (val <= std::get<1>((*it).second))))
		throw new std::exception();//TODO - value outside range
	Notify::notify(pname);
}

void Validate::validate(const std::string& pname, bool val){
	//TODO
	Notify::notify(pname);
}

void Validate::validate(const std::string& pname, long val){
	Validate::validate(pname, (double)val);  //CHECKME - cast
}

}//namespace