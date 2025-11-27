#ifndef __RESERVATIONWITHHOTEL_H__
#define __RESERVATIONWITHHOTEL_H__

#include "HotelInfo.h"
#include "ReservationModel.h"
#include <ctime>
#include <vector>

class ReservationWithHotel
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
		std::string _paymentUid;

	public:
		ReservationWithHotel() = default;
		~ReservationWithHotel() = default;
		explicit ReservationWithHotel(const ReservationWithHotel &obj);
		ReservationWithHotel(ReservationWithHotel &&obj);
		explicit ReservationWithHotel(const ReservationModel &obj);

		const std::string& getReservationUid() const;
		const HotelInfo& getHotel() const;
		const std::time_t& getStartDate() const;
		const std::time_t& getEndDate() const;
		const std::string& getStatus() const;
		const std::string& getPaymentUid() const;

		ReservationWithHotel& setReservationUid(const std::string &hotelUid);
		ReservationWithHotel& setHotelInfo(const HotelInfo &hotel);
		ReservationWithHotel& setStartDate(const std::time_t &startDate);
		ReservationWithHotel& setEndDate(const std::time_t &endDate);
		ReservationWithHotel& setStatus(const std::string &status);
		ReservationWithHotel& setStatus(const Status &status);
		ReservationWithHotel& setPaymentUid(const std::string &paymentUid);

		bool fromJson(const std::string &json, bool all = false);
		std::string toJson() const;

		const ReservationWithHotel& operator =(const ReservationWithHotel &obj);
};

#endif
