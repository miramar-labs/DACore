#ifndef DA_IVALIDATE_H
#define DA_IVALIDATE_H

#include "dacommon.h"

namespace dacore {

	class DACORE_API IValidate
	{
	public:
		virtual ~IValidate(){}

		 static const char* REGEX_ALPHA_NUM;
		 static const char* INVALID_STR;
		 static const double INVALID_DBL;
		 static const double MAX_DBL;
	};

}

#endif