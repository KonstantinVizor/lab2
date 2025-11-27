#ifndef __PAYMENT_H__
#define __PAYMENT_H__

#include <string>
#include <vector>
#include <cstdint>

class PaymentModel
{
	public:
		using Status = enum
		{
			PAID = 0,
			CANCELED = 1
		};

	private:
		static inline std::vector<std::string> _statuses =
		{
			"PAID",
			"CANCELED"
		};

		uint32_t _id;
		std::string _paymentUid;
		std::string _status;
		uint32_t _price;

	public:
		PaymentModel() = default;
		~PaymentModel() = default;
		explicit PaymentModel(const PaymentModel &obj);
		PaymentModel(PaymentModel &&obj);

		const uint32_t& getId() const;
		const std::string& getPaymentUid() const;
		const std::string& getStatus() const;
		const uint32_t& getPrice() const;

		PaymentModel& setId(uint32_t id);
		PaymentModel& setPaymentUid(const std::string &uid);
		PaymentModel& setStatus(const Status &status);
		PaymentModel& setStatus(const std::string &status);
		PaymentModel& setPrice(uint32_t price);

		bool fromJson(const std::string &json, bool all = false);
		std::string toJson() const;

		const PaymentModel& operator =(const PaymentModel &obj);
		bool operator ==(const PaymentModel &model) const;
};

#endif
