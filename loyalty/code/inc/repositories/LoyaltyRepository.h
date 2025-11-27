#ifndef __LOYALTYREPOSITORY_H__
#define __LOYALTYREPOSITORY_H__

#include <Poco/Data/Session.h>
#include <Poco/Tuple.h>
#include <memory>
#include <optional>
#include "../models/LoyaltyModel.h"

class LoyaltyRepository
{
	public:
		using SessionPtr = std::shared_ptr<Poco::Data::Session>;
		using LoyaltyModelTuple = Poco::Tuple<uint32_t, std::string, uint32_t,
		      					std::string, uint32_t>;
		using LoyaltyModelNoIdTuple = Poco::Tuple<std::string, uint32_t,
		      					std::string, uint32_t>;

	protected:
		SessionPtr _session;

	public:
		LoyaltyRepository() = default;
		explicit LoyaltyRepository(const LoyaltyRepository &) = delete;
		LoyaltyRepository(LoyaltyRepository &&) = delete;
		~LoyaltyRepository() = default;
		
		virtual LoyaltyRepository& setSession(const SessionPtr &session);
	
		virtual std::optional<LoyaltyModel> getByUsername(const std::string &username) const;
		virtual std::vector<LoyaltyModel> getAll() const;
		virtual uint32_t create(const LoyaltyModel &model) const;
		virtual const LoyaltyRepository& deleteByUsername(const std::string &username) const;
		virtual const LoyaltyRepository& updateByUsername(const std::string &username, const LoyaltyModel &model) const;
};

#endif
