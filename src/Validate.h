#ifndef DA_VALIDATE_H
#define DA_VALIDATE_H

#include "stdafx.h"

namespace dacore {

	class Validate {
	public:

		static const std::string REGEX_ALPHA_NUM;
		static const std::string INVALID_STR;
		static const double INVALID_DBL;

		static void registerStrPattern(const std::string& id, std::tuple<std::string, std::string, std::string> pattern);
		static void registerNumPattern(const std::string& id, std::tuple<double, double, double, double> pattern);

		static void validate(const std::string& pname, const std::string& val);
		static void validate(const std::string& pname, double val);
		static void validate(const std::string& pname, long val);
		static void validate(const std::string& pname, bool val);

	};

}

#endif