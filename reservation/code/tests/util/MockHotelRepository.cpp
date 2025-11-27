#include "MockHotelRepository.h"
#include <optional>

void MockHotelRepository::setTestData(const std::vector<HotelResponce> &data)
{
	_data = data;
}

void MockHotelRepository::setTestData(const HotelResponce &data)
{
	_singleData = data;
}

void MockHotelRepository::setId(uint32_t id)
{
	_id = id;
}

void MockHotelRepository::setUid(const std::string &uid)
{
	_uid = uid;
}

std::vector<HotelResponce> MockHotelRepository::getAll(uint32_t pageNumber, uint32_t pageSize) const
{
	std::vector<HotelResponce> res;
	for (uint32_t i = (pageNumber - 1) * pageSize; i < _data.size() && i < pageNumber * pageSize; i++)
		res.push_back(_data[i]);
	return _data;
}	

std::optional<HotelResponce> MockHotelRepository::getByUid(const std::string &uid) const
{
	if (uid == _singleData.getHotelUid())
		return std::optional(_singleData);
	return {};
}

const HotelRepository& MockHotelRepository::deleteByUid([[maybe_unused]] const std::string &uid) const
{
	return *this;
}

std::pair<uint32_t, std::string> MockHotelRepository::create([[maybe_unused]] const HotelResponce &model) const
{
	return {_id, _uid};
}

const HotelRepository& MockHotelRepository::updateByUid(const std::string &uid, [[maybe_unused]] const HotelResponce &model) const
{
	if (uid == _singleData.getHotelUid())
		const_cast<HotelResponce &>(_singleData) = model;
	return *this;
}
