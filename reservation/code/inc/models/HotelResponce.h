#ifndef __HOTELRESPONCE_H__
#define __HOTELRESPONCE_H__

#include <string>
#include <cstdint>

class HotelResponce
{
	private:
		uint32_t _id;
		std::string _hotelUid;
		std::string _name;
		std::string _country;
		std::string _city;
		std::string _address;
		uint32_t _stars;
		uint32_t _price;

	public:
		HotelResponce() = default;
		~HotelResponce() = default;
		explicit HotelResponce(const HotelResponce &obj);
		HotelResponce(HotelResponce &&obj);

		const uint32_t& getId() const;
		const std::string& getHotelUid() const;
		const std::string& getName() const;
		const std::string& getCountry() const;
		const std::string& getCity() const;
		const std::string& getAddress() const;
		const uint32_t& getStars() const;
		const uint32_t& getPrice() const;

		HotelResponce& setId(uint32_t id);
		HotelResponce& setHotelUid(const std::string &uid);
		HotelResponce& setName(const std::string &name);
		HotelResponce& setCountry(const std::string &country);
		HotelResponce& setCity(const std::string &city);
		HotelResponce& setAddress(const std::string &address);
		HotelResponce& setStars(uint32_t stars);
		HotelResponce& setPrice(uint32_t price);

		bool fromJson(const std::string &json, bool all = false);
		std::string toJson() const;

		const HotelResponce& operator =(const HotelResponce &obj);
		bool operator ==(const HotelResponce &obj) const;
};

#endif
