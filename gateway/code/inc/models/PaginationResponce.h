#ifndef __PAGINATIONRESPONCE_H__
#define __PAGINATIONRESPONCE_H__

#include <vector>
#include "HotelResponce.h"

class PaginationResponce
{
	private:
		uint32_t _pageNumber;
		uint32_t _pageSize;
		std::vector<HotelResponce> _hotels;

	public:
		PaginationResponce() = default;
		~PaginationResponce() = default;
		explicit PaginationResponce(const PaginationResponce &obj);
		PaginationResponce(PaginationResponce &&obj);

		uint32_t getPageNumber() const;
		uint32_t getPageSize() const;
		const std::vector<HotelResponce>& getHotels() const;

		PaginationResponce& setPageNumber(uint32_t pageNumber);
		PaginationResponce& setPageSize(uint32_t pageSize);
		PaginationResponce& setHotels(const std::vector<HotelResponce> &hotels);

		bool fromJson(const std::string &json, bool all = false);
		std::string toJson() const;

		const PaginationResponce& operator =(const PaginationResponce &obj);
};

#endif
