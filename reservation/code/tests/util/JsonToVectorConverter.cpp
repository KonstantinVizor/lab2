#include "JsonToVectorConverter.h"

std::vector<std::string> JsonVectorConverter::jsonToVector(const std::string &json) const
{
	std::vector<std::string> result;
	Poco::Dynamic::Var var;
	Poco::JSON::Parser parser;
	Poco::JSON::Object::Ptr data;
	var = parser.parse(json);
	if (var.isArray())
	{
		Poco::JSON::Array::Ptr arr = var.extract<Poco::JSON::Array::Ptr>();
		for (int i = 0; i < static_cast<int>(arr->size()); i++)
			result.push_back(arr->get(i).toString());
	}
	return result;
}
