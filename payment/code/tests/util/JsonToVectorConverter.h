#ifndef __JSONTOVECTORCONVERTER_H__
#define __JSONTOVECTORCONVERTER_H__

#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>

class JsonVectorConverter
{
	public:
		std::vector<std::string> jsonToVector(const std::string &json) const;
};

#endif
