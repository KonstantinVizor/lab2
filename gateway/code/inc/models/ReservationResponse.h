#ifndef __RESERVATIONRESPONSE_H__
#define __RESERVATIONRESPONSE_H__

#include "HotelInfo.h"
#include "PaymentInfo.h"
#include <ctime>

class ReservationResponse
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

	private:
		std::string _reservationUid;
		HotelInfo _hotel;
		std::time_t _startDate;
		std::time_t _endDate;
		std::string _status;
		PaymentInfo _payment;

	public:
		ReservationResponse() = default;
		~ReservationResponse() = default;
		explicit ReservationResponse(const ReservationResponse &obj);
		ReservationResponse(ReservationResponse &&obj);

		const std::string& getReservationUid() const;
		const HotelInfo& getHotel() const;
		const std::time_t& getStartDate() const;
		const std::time_t& getEndDate() const;
		const std::string& getStatus() const;
		const PaymentInfo& getPayment() const;

		ReservationResponse& setReservationUid(const std::string &reservationUid);
		ReservationResponse& setHotel(const HotelInfo &hotel);
		ReservationResponse& setStartDate(const std::time_t &startDate);
		ReservationResponse& setEndDate(const std::time_t &endDate);
		ReservationResponse& setStatus(const std::string &status);
		ReservationResponse& setStatus(const Status &status);
		ReservationResponse& setPayment(const PaymentInfo &payment);

		bool fromJson(const std::string &json, bool all = false);
		std::string toJson() const;

		const ReservationResponse& operator =(const ReservationResponse &obj);
};

#endif
