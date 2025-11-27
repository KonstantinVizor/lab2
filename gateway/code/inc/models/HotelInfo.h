#ifndef __HOTELINFO_H__
#define __HOTELINFO_H__

#include "HotelResponce.h"

class HotelInfo
{
	private:
		std::string _hotelUid;
		std::string _name;
		std::string _fullAddress;
		uint32_t _stars;
		
	public:
		HotelInfo() = default;
		~HotelInfo() = default;
		explicit HotelInfo(const HotelInfo &obj);
		HotelInfo(HotelInfo &&obj);
		explicit HotelInfo(const HotelResponce &resp);

		const std::string& getHotelUid() const;
		const std::string& getName() const;
		const std::string& getFullAddress() const;
		const uint32_t& getStars() const;

		HotelInfo& setHotelUid(const std::string &hotelUid);
		HotelInfo& setName(const std::string &name);
		HotelInfo& setFullAddress(const std::string &fullAddress);
		HotelInfo& setStars(const uint32_t &stars);

		bool fromJson(const std::string &json, bool all = false);
		std::string toJson() const;

		const HotelInfo& operator =(const HotelInfo &obj);
};

#endif
