#ifndef __RESERVATION_H__
#define __RESERVATION_H__

#include <ctime>
#include <string>
#include <vector>
#include <cstdint>

class ReservationModel
{
	public:
		using Status = enum
		{
			PAID = 0,
			CANCELED = 1
		};

	private:
		static inline std::vector<std::string> _statuses =
		{
			"PAID",
			"CANCELED"
		};

		uint32_t _id;
		std::string _reservationUid;
		std::string _username;
		std::string _paymentUid;
		uint32_t _hotelId;
		std::string _status;
		std::time_t _startDate;
		std::time_t _endDate;

	public:
		ReservationModel() = default;
		~ReservationModel() = default;
		explicit ReservationModel(const ReservationModel &obj);
		ReservationModel(ReservationModel &&obj);

		const uint32_t& getId() const;
		const std::string& getReservationUid() const;
		const std::string& getUsername() const;
		const std::string& getPaymentUid() const;
		const uint32_t& getHotelId() const;
		const std::string& getStatus() const;
		const std::time_t& getStartDate() const;
		const std::time_t& getEndDate() const;

		ReservationModel& setId(uint32_t id);
		ReservationModel& setReservationUid(const std::string &uid);
		ReservationModel& setUsername(const std::string &username);
		ReservationModel& setPaymentUid(const std::string &paymentUid);
		ReservationModel& setHotelId(uint32_t hotelId);
		ReservationModel& setStatus(const Status &status);
		ReservationModel& setStatus(const std::string &status);
		ReservationModel& setStartDate(const std::time_t &startDate);
		ReservationModel& setEndDate(const std::time_t &endDate);

		bool fromJson(const std::string &json, bool all = false);
		std::string toJson() const;

		const ReservationModel& operator =(const ReservationModel &obj);
		bool operator ==(const ReservationModel &model) const;
};

#endif
