#include "MockReservationRepository.h"
#include <optional>

void MockReservationRepository::setTestData(const std::vector<ReservationModel> &data)
{
	_data = data;
}

void MockReservationRepository::setTestData(const ReservationModel &data)
{
	_singleData = data;
}

void MockReservationRepository::setId(uint32_t id)
{
	_id = id;
}

void MockReservationRepository::setUid(const std::string &uid)
{
	_uid = uid;
}

std::vector<ReservationModel> MockReservationRepository::getAll() const
{
	return _data;
}	

std::optional<ReservationModel> MockReservationRepository::getByUid(const std::string &uid) const
{
	if (uid == _singleData.getReservationUid())
		return std::optional(_singleData);
	return {};
}

const ReservationRepository& MockReservationRepository::deleteByUid([[maybe_unused]] const std::string &uid) const
{
	return *this;
}

std::pair<uint32_t, std::string> MockReservationRepository::create([[maybe_unused]] const ReservationModel &model) const
{
	return {_id, _uid};
}

const ReservationRepository& MockReservationRepository::updateByUid(const std::string &uid, [[maybe_unused]] const ReservationModel &model) const
{
	if (uid == _singleData.getReservationUid())
		const_cast<ReservationModel &>(_singleData) = model;
	return *this;
}
