#include "MockLoyaltyRepository.h"
#include <optional>

void MockLoyaltyRepository::setTestData(const std::vector<LoyaltyModel> &data)
{
	_data = data;
}

void MockLoyaltyRepository::setTestData(const LoyaltyModel &data)
{
	_singleData = data;
}

void MockLoyaltyRepository::setId(uint32_t id)
{
	_id = id;
}

std::vector<LoyaltyModel> MockLoyaltyRepository::getAll() const
{
	return _data;
}	

std::optional<LoyaltyModel> MockLoyaltyRepository::getByUsername(const std::string &name) const
{
	if (name == _singleData.getUsername())
		return std::optional(_singleData);
	return {};
}

const LoyaltyRepository& MockLoyaltyRepository::deleteByUsername([[maybe_unused]] const std::string &name) const
{
	return *this;
}

uint32_t MockLoyaltyRepository::create([[maybe_unused]] const LoyaltyModel &model) const
{
	return _id;
}

const LoyaltyRepository& MockLoyaltyRepository::updateByUsername(const std::string &name, [[maybe_unused]] const LoyaltyModel &model) const
{
	if (name == _singleData.getUsername())
		const_cast<LoyaltyModel &>(_singleData) = model;
	return *this;
}
