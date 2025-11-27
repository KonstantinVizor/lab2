#ifndef __CREATOR_H__
#define __CREATOR_H__

#include <functional>
class Creator
{
	public:
		Creator() = default;
		explicit Creator(const Creator &) = delete;
		Creator(Creator &&) = delete;
		~Creator() = default;
	
		template <typename BaseClass, typename ChildClass>
		std::function<BaseClass*()> getCreateFunction() const;

		template <typename BaseClass, typename ChildClass, typename... Args>
		std::function<BaseClass*()> getCreateFunction(Args &...args) const;
};

#endif
