#ifndef __MOCKHOTELREPOSITORY_H__
#define __MOCKHOTELREPOSITORY_H__

#include "../../inc/repositories/HotelRepository.h"

class MockHotelRepository : public HotelRepository
{
	private:
		std::vector<HotelResponce> _data;
		HotelResponce _singleData;
		uint32_t _id;
		std::string _uid;

	public:
		void setTestData(const std::vector<HotelResponce> &data);
		void setTestData(const HotelResponce &data);
		void setId(uint32_t id);
		void setUid(const std::string &uid);
		virtual std::vector<HotelResponce> getAll(uint32_t pageNumber, uint32_t pageSize) const override;
		virtual std::optional<HotelResponce> getByUid(const std::string &uid) const override;
		virtual const HotelRepository& deleteByUid(const std::string &uid) const override;
		virtual std::pair<uint32_t, std::string> create(const HotelResponce &model) const override;
		virtual const HotelRepository& updateByUid(const std::string &uid, const HotelResponce &model) const override;
};

#endif
