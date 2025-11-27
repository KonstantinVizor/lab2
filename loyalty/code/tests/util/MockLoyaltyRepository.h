#ifndef __MOCKPERSONREPOSITORY_H__
#define __MOCKPERSONREPOSITORY_H__

#include "../../inc/repositories/LoyaltyRepository.h"

class MockLoyaltyRepository : public LoyaltyRepository
{
	private:
		std::vector<LoyaltyModel> _data;
		LoyaltyModel _singleData;
		uint32_t _id;

	public:
		void setTestData(const std::vector<LoyaltyModel> &data);
		void setTestData(const LoyaltyModel &data);
		void setId(uint32_t id);
		virtual std::vector<LoyaltyModel> getAll() const override;
		virtual std::optional<LoyaltyModel> getByUsername(const std::string &name) const override;
		virtual const LoyaltyRepository& deleteByUsername(const std::string &name) const override;
		virtual uint32_t create(const LoyaltyModel &model) const override;
		virtual const LoyaltyRepository& updateByUsername(const std::string &name, const LoyaltyModel &model) const override;
};

#endif
