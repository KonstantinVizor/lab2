#ifndef __USERINFORESPONSE_H__
#define __USERINFORESPONSE_H__

#include "ReservationResponse.h"
#include "LoyaltyInfo.h"

class UserInfoResponse
{
	private:
		std::vector<ReservationResponse> _reservations;
		LoyaltyInfo _loyalty;

	public:
		UserInfoResponse() = default;
		~UserInfoResponse() = default;
		explicit UserInfoResponse(const UserInfoResponse &obj);
		UserInfoResponse(UserInfoResponse &&obj);

		const std::vector<ReservationResponse>& getReservations() const;
		const LoyaltyInfo& getLoyalty() const;

		UserInfoResponse& setReservations(const std::vector<ReservationResponse> &reservations);
		UserInfoResponse& setLoyalty(const LoyaltyInfo &loyalty);

		bool fromJson(const std::string &json, bool all = false);
		std::string toJson() const;
		
		const UserInfoResponse& operator =(const UserInfoResponse &obj);
};

#endif
