#ifndef __HOTEL_REPOSITORY_H__
#define __HOTEL_REPOSITORY_H__


#include <string>
#include <cstdint>
#include "../models/PaginationResponce.h"
#include "../models/ReservationWithHotel.h"
#include "../models/CreateReservationRequest.h"
#include "../models/HotelResponce.h"

class HotelRepository
{
	private:
		std::string _path;
	
	public:
		~HotelRepository() = default;
		HotelRepository(const HotelRepository &) = delete;
		HotelRepository(HotelRepository &&) = delete;
		HotelRepository(const std::string &path);

		PaginationResponce getHotelAll(uint32_t page, uint32_t size);
		HotelResponce getHotelByUid(const std::string &uid);
		std::vector<ReservationWithHotel> getReservationsByUsername(const std::string &username);
		ReservationWithHotel createReservation(const std::string &username, const CreateReservationRequest &request);
		void updateReservation(const std::string &uid, const ReservationWithHotel &res);
		void deleteReservation(const std::string &uid);
};

#endif
