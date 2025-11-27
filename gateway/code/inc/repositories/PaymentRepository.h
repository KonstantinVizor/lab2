#ifndef __PAYMENT_REPOSITORY_H__
#define __PAYMENT_REPOSITORY_H__

#include <string>
#include "../models/PaymentInfo.h"
#include "../models/PaymentModel.h"

class PaymentRepository
{
	private:
		std::string _path;
	
	public:
		~PaymentRepository() = default;
		PaymentRepository(const PaymentRepository &) = delete;
		PaymentRepository(PaymentRepository &&) = delete;
		PaymentRepository(const std::string &path);

		PaymentInfo getByUid(const std::string &uid);
		void updateByUid(const std::string &uid, const PaymentModel &model);
		std::string create(const PaymentModel &model);

};

#endif
