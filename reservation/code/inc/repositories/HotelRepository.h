#ifndef __HOTELREPOSITORY_H__
#define __HOTELREPOSITORY_H__

#include <Poco/Data/Session.h>
#include <Poco/Tuple.h>
#include <memory>
#include <optional>
#include "../models/HotelResponce.h"

class HotelRepository
{
	public:
		using SessionPtr = std::shared_ptr<Poco::Data::Session>;
		using HotelModelTuple = Poco::Tuple<uint32_t, std::string, std::string, std::string,
		      					std::string, std::string, uint32_t, uint32_t>;
		using HotelModelNoIdTuple = Poco::Tuple<std::string, std::string, std::string,
		      					std::string, std::string, uint32_t, uint32_t>;

	protected:
		SessionPtr _session;

	public:
		HotelRepository() = default;
		explicit HotelRepository(const HotelRepository &) = delete;
		HotelRepository(HotelRepository &&) = delete;
		~HotelRepository() = default;
		
		virtual HotelRepository& setSession(const SessionPtr &session);
	
		virtual std::optional<HotelResponce> getByUid(const std::string &uid) const;
		virtual std::optional<HotelResponce> getById(int32_t id) const;
		virtual std::vector<HotelResponce> getAll(uint32_t pageNumber, uint32_t pageSize) const;
		virtual std::pair<uint32_t, std::string> create(const HotelResponce &model) const;
		virtual const HotelRepository& deleteByUid(const std::string &uid) const;
		virtual const HotelRepository& updateByUid(const std::string &uid, const HotelResponce &model) const;
};

#endif
