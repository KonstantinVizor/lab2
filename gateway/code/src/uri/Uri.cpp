#include "../../inc/uri/Uri.h"

Uri::Uri(const std::string &uri)
{
	std::string::const_iterator it = uri.begin();
	std::string tmpstring = "";
	std::string attr;
	if (*it == '/')
		it++;
	while (it != uri.end() && *it != '?')
	{
		if (*it == '/')
		{
			_pathFragments.push_back(tmpstring);
			tmpstring = "";
		}
		else
			tmpstring += *it;
		it++;
	}
	if (tmpstring != "" && tmpstring != "/")
		_pathFragments.push_back(tmpstring);
	if (*it == '?')
	{
		it++;
		while (it != uri.end())
		{
			tmpstring = "";
			while (it != uri.end() && *it != '=')
			{
				tmpstring += *it;
				it++;
			}
			it++;
			attr = tmpstring;
			tmpstring = "";
			while (it != uri.end() && *it != '&')
			{
				tmpstring += *it;
				it++;
			}
			_attributes[attr] = tmpstring;
			if (*it == '&')
				it++;
		}
	}
}

Uri::Uri(const Uri &obj) :
		_pathFragments(obj._pathFragments),
		_attributes(obj._attributes)
{}

Uri::Uri(Uri &&obj) :
		_pathFragments(obj._pathFragments),
		_attributes(obj._attributes)
{}

int Uri::getPathSize() const
{
	return _pathFragments.size();
}

const std::string& Uri::getPathFragment(uint32_t index) const
{
	return _pathFragments[index];
}

std::string Uri::getValue(const std::string &attibute) const
{
	try
	{
		const std::string &result = _attributes.at(attibute);
		return result;
	}
	catch (...)
	{}
	return "";
}

const Uri& Uri::operator =(const Uri &obj)
{
	_pathFragments = obj._pathFragments;
	_attributes = obj._attributes;
	return *this;
}
