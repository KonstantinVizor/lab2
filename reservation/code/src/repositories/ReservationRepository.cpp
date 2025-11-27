#include "../../inc/repositories/ReservationRepository.h"
#include <Poco/DateTime.h>
#include <Poco/Data/Statement.h>
#include <Poco/Timespan.h>
#include <Poco/UUID.h>
#include <Poco/Data/Binding.h>
#include <Poco/Data/Extraction.h>
#include <Poco/Data/Position.h>
#include <Poco/UUIDGenerator.h>
#include <vector>

ReservationRepository& ReservationRepository::setSession(const SessionPtr &session)
{
	_session = session;
	return *this;
}

std::optional<ReservationModel> ReservationRepository::getByUid(const std::string &uid) const
{
	std::string muid = uid;
	std::vector<ReservationModelTuple> tuple;
	ReservationModel result;
	std::string request = "SELECT id, reservation_uid, username, \
				payment_uid, hotel_id, status, \
				start_date, end_date \
				FROM reservation WHERE reservation_uid = $1";
	*_session << request, 
			Poco::Data::Keywords::use(muid),
			Poco::Data::Keywords::into(tuple),
			Poco::Data::Keywords::now;
	if (tuple.size() == 0)
		return {};
	result.setId(tuple[0].get<0>())
		.setReservationUid(tuple[0].get<1>())
		.setUsername(tuple[0].get<2>())
		.setPaymentUid(tuple[0].get<3>())
		.setHotelId(tuple[0].get<4>())
		.setStatus(tuple[0].get<5>())
		.setStartDate(tuple[0].get<6>().timestamp().epochTime())
		.setEndDate(tuple[0].get<7>().timestamp().epochTime());
	return result;
}

std::vector<ReservationModel> ReservationRepository::getByUsername(const std::string &username) const
{
	std::string musername = username;
	std::vector<ReservationModelTuple> tuple;
	std::vector<ReservationModel> result;
	std::string request = "SELECT id, reservation_uid, username, \
				payment_uid, hotel_id, status, \
				start_date, end_date \
				FROM reservation WHERE username = $1";
	*_session << request, 
			Poco::Data::Keywords::use(musername),
			Poco::Data::Keywords::into(tuple),
			Poco::Data::Keywords::now;
	for (int i = 0; i < static_cast<int>(tuple.size()); i++)
		result.push_back(ReservationModel().setId(tuple[i].get<0>())
						.setReservationUid(tuple[i].get<1>())
						.setUsername(tuple[i].get<2>())
						.setPaymentUid(tuple[i].get<3>())
						.setHotelId(tuple[i].get<4>())
						.setStatus(tuple[i].get<5>())
						.setStartDate(tuple[i].get<6>().timestamp().epochTime())
						.setEndDate(tuple[i].get<7>().timestamp().epochTime()));
	return result;
}

std::vector<ReservationModel> ReservationRepository::getAll() const
{
	std::vector<ReservationModelTuple> tuple;
	std::vector<ReservationModel> result;
	std::string request = "SELECT id, reservation_uid, username, \
				payment_uid, hotel_id, status, \
				start_date, end_date \
				FROM reservation";
	*_session << request, 
			Poco::Data::Keywords::into(tuple),
			Poco::Data::Keywords::now;
	for (int i = 0; i < static_cast<int>(tuple.size()); i++)
		result.push_back(ReservationModel().setId(tuple[0].get<0>())
						.setReservationUid(tuple[0].get<1>())
						.setUsername(tuple[0].get<2>())
						.setPaymentUid(tuple[0].get<3>())
						.setHotelId(tuple[0].get<4>())
						.setStatus(tuple[0].get<5>())
						.setStartDate(tuple[0].get<6>().timestamp().epochTime())
						.setEndDate(tuple[0].get<7>().timestamp().epochTime()));
	return result;
}

std::pair<uint32_t, std::string> ReservationRepository::create(const ReservationModel &model) const
{
	uint32_t id;
	Poco::UUIDGenerator generator;
	std::string request = "INSERT INTO reservation(reservation_uid, username, payment_uid, \
			       				hotel_id, status, start_date, end_date) \
					VALUES ($1, $2, $3, $4, $5, $6, $7) RETURNING id";
	std::string uid = generator.createV7().toString();
	ReservationModelNoIdTuple tuple;
       	tuple = {
		uid,
		model.getUsername(),
		model.getPaymentUid(),
		model.getHotelId(),
		model.getStatus(),
		Poco::DateTime(Poco::Timestamp::fromEpochTime(model.getStartDate())),
		Poco::DateTime(Poco::Timestamp::fromEpochTime(model.getEndDate()))};
	*_session << request,
			Poco::Data::Keywords::use(tuple),
			Poco::Data::Keywords::into(id),
			Poco::Data::Keywords::now;
	return {id, tuple.get<0>()};
}

const ReservationRepository& ReservationRepository::deleteByUid(const std::string &uid) const
{
	std::string muid = uid;
	std::string request = "DELETE FROM reservation WHERE reservation_uid = $1";
	*_session << request,
			Poco::Data::Keywords::use(muid),
			Poco::Data::Keywords::now;
	return *this;
}

const ReservationRepository& ReservationRepository::updateByUid(const std::string &uid, const ReservationModel &model) const
{
	std::string muid = uid;
	std::string nuid = model.getReservationUid();
	std::string username = model.getUsername();
	std::string paymentUid = model.getPaymentUid();
	uint32_t hotelId = model.getHotelId();
	std::string status = model.getStatus();
	Poco::DateTime startDate = Poco::Timestamp::fromEpochTime(model.getStartDate());
	Poco::DateTime endDate = Poco::Timestamp::fromEpochTime(model.getEndDate());
	std::string request = "UPDATE reservation SET reservation_uid = $1, \
						username = $2, \
						payment_uid = $3, \
						hotel_id = $4, \
						status = $5, \
						start_date = $6, \
						end_date = $7 \
					WHERE reservation_uid = $8";
	*_session << request,
			Poco::Data::Keywords::use(nuid),
			Poco::Data::Keywords::use(username),
			Poco::Data::Keywords::use(paymentUid),
			Poco::Data::Keywords::use(hotelId),
			Poco::Data::Keywords::use(status),
			Poco::Data::Keywords::use(startDate),
			Poco::Data::Keywords::use(endDate),
			Poco::Data::Keywords::use(muid),
			Poco::Data::Keywords::now;
	return *this;	
}
