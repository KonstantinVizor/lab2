#ifndef __RESERVATIONREPOSITORY_H__
#define __RESERVATIONREPOSITORY_H__

#include <Poco/Data/Session.h>
#include <Poco/Tuple.h>
#include <Poco/DateTime.h>
#include <memory>
#include <optional>
#include "../models/ReservationModel.h"

class ReservationRepository
{
	public:
		using SessionPtr = std::shared_ptr<Poco::Data::Session>;
		using ReservationModelTuple = Poco::Tuple<uint32_t, std::string, std::string, std::string,
		      						uint32_t, std::string, Poco::DateTime,
								Poco::DateTime>;
		using ReservationModelNoIdTuple = Poco::Tuple<std::string, std::string, std::string,
		      						uint32_t, std::string, Poco::DateTime,
								Poco::DateTime>;

	protected:
		SessionPtr _session;

	public:
		ReservationRepository() = default;
		explicit ReservationRepository(const ReservationRepository &) = delete;
		ReservationRepository(ReservationRepository &&) = delete;
		~ReservationRepository() = default;
		
		virtual ReservationRepository& setSession(const SessionPtr &session);
	
		virtual std::optional<ReservationModel> getByUid(const std::string &uid) const;
		virtual std::vector<ReservationModel> getByUsername(const std::string &username) const;
		virtual std::vector<ReservationModel> getAll() const;
		virtual std::pair<uint32_t, std::string> create(const ReservationModel &model) const;
		virtual const ReservationRepository& deleteByUid(const std::string &uid) const;
		virtual const ReservationRepository& updateByUid(const std::string &uid, const ReservationModel &model) const;
};

#endif
