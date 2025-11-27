#ifndef __CREATERESERVATIONRESPONSE_H__
#define __CREATERESERVATIONRESPONSE_H__

#include <vector>
#include <string>
#include <ctime>
#include <cstdint>
#include "PaymentInfo.h"
#include "ReservationModel.h"

class CreateReservationResponse
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

		std::string _reservationUid;
		std::string _hotelUid;
		std::time_t _startDate;
		std::time_t _endDate;
		uint32_t _discount;
		std::string _status;
		PaymentInfo _payment;

	public:
		CreateReservationResponse() = default;
		~CreateReservationResponse() = default;
		explicit CreateReservationResponse(const CreateReservationResponse &obj);
		CreateReservationResponse(CreateReservationResponse &&obj);
		explicit CreateReservationResponse(ReservationModel &obj);

		const std::string& getReservationUid() const;
		const std::string& getHotelUid() const;
		const std::time_t& getStartDate() const;
		const std::time_t& getEndDate() const;
		const uint32_t& getDiscount() const;
		const std::string& getStatus() const;
		const PaymentInfo& getPayment() const;

		CreateReservationResponse& setReservationUid(const std::string &reservationUid);
		CreateReservationResponse& setHotelUid(const std::string &hotelUid);
		CreateReservationResponse& setStartDate(const std::time_t &startDate);
		CreateReservationResponse& setEndDate(const std::time_t &endDate);
		CreateReservationResponse& setDiscount(const uint32_t &discount);
		CreateReservationResponse& setStatus(const std::string &status);
		CreateReservationResponse& setStatus(const Status &status);
		CreateReservationResponse& setPayment(const PaymentInfo &payment);

		bool fromJson(const std::string &json, bool all = false);
		std::string toJson() const;

		const CreateReservationResponse& operator =(const CreateReservationResponse &obj);
};

#endif
