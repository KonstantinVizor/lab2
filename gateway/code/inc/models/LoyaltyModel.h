#ifndef __LOYALTY_H__
#define __LOYALTY_H__

#include <string>
#include <vector>
#include <cstdint>

class LoyaltyModel
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

		uint32_t _id;
		std::string _username;
		uint32_t _reservationCount;
		std::string _status;
		uint32_t _discont;

	public:
		LoyaltyModel() = default;
		~LoyaltyModel() = default;
		explicit LoyaltyModel(const LoyaltyModel &obj);
		LoyaltyModel(LoyaltyModel &&obj);

		const uint32_t& getId() const;
		const std::string& getUsername() const;
		const uint32_t& getReservationCount() const;
		const std::string& getStatus() const;
		const uint32_t& getDiscont() const;

		LoyaltyModel& setId(uint32_t id);
		LoyaltyModel& setUsername(const std::string &username);
		LoyaltyModel& setReservationCount(uint32_t reservationCount);
		LoyaltyModel& setStatus(const Status &status);
		LoyaltyModel& setStatus(const std::string &status);
		LoyaltyModel& setDiscont(uint32_t discont);

		bool fromJson(const std::string &json, bool all = false);
		std::string toJson() const;

		const LoyaltyModel& operator =(const LoyaltyModel &obj);
		bool operator ==(const LoyaltyModel &model) const;
};

#endif
