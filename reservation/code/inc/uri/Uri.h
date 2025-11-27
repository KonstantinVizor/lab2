#ifndef __URI_H__
#define __URI_H__

#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>

class Uri
{
	private:
		std::vector<std::string> _pathFragments;
		std::unordered_map<std::string, std::string> _attributes;
	
	public:
		Uri() = default;
		~Uri() = default;
		explicit Uri(const std::string &uri);
		explicit Uri(const Uri &obj);
		Uri(Uri &&obj);

		int getPathSize() const;
		const std::string& getPathFragment(uint32_t index) const;
		std::string getValue(const std::string &attibute) const;

		const Uri& operator =(const Uri &obj);
};

#endif
