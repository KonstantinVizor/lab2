#ifndef __MOCKRESERVATIONREPOSITORY_H__
#define __MOCKRESERVATIONREPOSITORY_H__

#include "../../inc/repositories/ReservationRepository.h"

class MockReservationRepository : public ReservationRepository
{
	private:
		std::vector<ReservationModel> _data;
		ReservationModel _singleData;
		uint32_t _id;
		std::string _uid;

	public:
		void setTestData(const std::vector<ReservationModel> &data);
		void setTestData(const ReservationModel &data);
		void setId(uint32_t id);
		void setUid(const std::string &uid);
		virtual std::vector<ReservationModel> getAll() const override;
		virtual std::optional<ReservationModel> getByUid(const std::string &uid) const override;
		virtual const ReservationRepository& deleteByUid(const std::string &uid) const override;
		virtual std::pair<uint32_t, std::string> create(const ReservationModel &model) const override;
		virtual const ReservationRepository& updateByUid(const std::string &uid, const ReservationModel &model) const override;
};

#endif
