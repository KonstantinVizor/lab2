#ifndef __LOYALTYINFO_H__
#define __LOYALTYINFO_H__

#include <vector>
#include <string>
#include <cstdint>
#include "LoyaltyModel.h"

class LoyaltyInfo
{
	public:
		using Status = enum
		{
			BRONZE = 0,
			SILVER = 1,
			GOLD = 2
		};

	private:
		static inline std::vector<std::string> _statuses =
		{
			"BRONZE",
			"SILVER",
			"GOLD"
		};

		uint32_t _reservationCount;
		std::string _status;
		uint32_t _discont;

	public:
		LoyaltyInfo() = default;
		~LoyaltyInfo() = default;
		explicit LoyaltyInfo(const LoyaltyInfo &obj);
		LoyaltyInfo(LoyaltyInfo &&obj);
		explicit LoyaltyInfo(const LoyaltyModel &obj);

		const uint32_t& getReservationCount() const;
		const std::string& getStatus() const;
		const uint32_t& getDiscount() const;

		LoyaltyInfo& setReservationCount(uint32_t reservationCount);
		LoyaltyInfo& setstatus(const std::string &status);
		LoyaltyInfo& setstatus(const Status &status);
		LoyaltyInfo& setDiscount(uint32_t discount);

		bool fromJson(const std::string &json, bool all = false);
		std::string toJson() const;

		const LoyaltyInfo& operator =(const LoyaltyInfo &obj);
};

#endif
