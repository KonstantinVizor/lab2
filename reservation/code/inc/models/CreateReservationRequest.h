#ifndef __CREATERESERVATIONREQUEST_H__
#define __CREATERESERVATIONREQUEST_H__

#include <string>
#include <ctime>

class CreateReservationRequest
{
	private:
		std::string _hotelUid;
		std::time_t _startDate;
		std::time_t _endDate;
		std::string _paymentUid;

	public:
		CreateReservationRequest() = default;
		~CreateReservationRequest() = default;
		explicit CreateReservationRequest(const CreateReservationRequest &obj);
		CreateReservationRequest(CreateReservationRequest &&obj);

		const std::string& getHotelUid() const;
		const std::time_t& getStartDate() const;
		const std::time_t& getEndDate() const;
		const std::string& getPaymentUid() const;

		CreateReservationRequest& setHoteUid(const std::string &hotelUid);
		CreateReservationRequest& setStartDate(const std::time_t &startDate);
		CreateReservationRequest& setEndDate(const std::time_t &endDate);
		CreateReservationRequest& setPaymentUid(const std::string &paymentUid);

		bool fromJson(const std::string &json, bool all = false);
		std::string toJson() const;

		const CreateReservationRequest& operator =(const CreateReservationRequest &obj);
};

#endif
