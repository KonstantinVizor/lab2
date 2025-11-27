#ifndef __PAYMENTINFO_H__
#define __PAYMENTINFO_H__

#include <vector>
#include <string>
#include <cstdint>

class PaymentInfo
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

		std::string _status;
		uint32_t _price;

	public:
		PaymentInfo() = default;
		~PaymentInfo() = default;
		explicit PaymentInfo(const PaymentInfo &obj);
		PaymentInfo(PaymentInfo &&obj);

		const std::string& getStatus() const;
		const uint32_t& getPrice() const;

		PaymentInfo& setStatus(const std::string &status);
		PaymentInfo& setStatus(const Status &status);
		PaymentInfo& setPrice(const uint32_t &price);

		bool fromJson(const std::string &json, bool all = false);
		std::string toJson() const;

		const PaymentInfo& operator =(const PaymentInfo &obj);
};

#endif
