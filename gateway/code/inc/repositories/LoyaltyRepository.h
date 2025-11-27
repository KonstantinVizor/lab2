#ifndef __LOYALTY_REPOSITORY_H__
#define __LOYALTY_REPOSITORY_H__

#include <string>
#include "../models/LoyaltyInfo.h"
#include "../models/LoyaltyModel.h"

class LoyaltyRepository
{
	private:
		std::string _path;
	
	public:
		~LoyaltyRepository() = default;
		LoyaltyRepository(const LoyaltyRepository &) = delete;
		LoyaltyRepository(LoyaltyRepository &&) = delete;
		LoyaltyRepository(const std::string &path);

		LoyaltyInfo getByUsername(const std::string &username);
		void updateByUsername(const std::string &username, const LoyaltyModel &model);

};

#endif
