#ifndef DA_VALIDATE_H
#define DA_VALIDATE_H

#include "stdafx.h"
#include "IValidate.h"

namespace dacore {

	class Validate : public IValidate {
	public:

		static void registerStrPattern(const std::string& id, std::tuple<std::string, std::string, std::string> pattern);
		static void registerNumPattern(const std::string& id, std::tuple<double, double, double, double> pattern);

		static void validate(const std::string& pname, const std::string& val);
		static void validate(const std::string& pname, double val);
		static void validate(const std::string& pname, long val);
		static void validate(const std::string& pname, bool val);

	};

}

#endif