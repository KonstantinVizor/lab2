#ifndef __CREATOR_HPP__
#define __CREATOR_HPP__

#include "../../inc/creator/Creator.h"

template <typename BaseClass, typename ChildClass>
std::function<BaseClass*()> Creator::getCreateFunction() const
{
	return [](){ return new ChildClass; };
}

template <typename BaseClass, typename ChildClass, typename ...Args>
std::function<BaseClass*()> Creator::getCreateFunction(Args &...args) const
{
	return [&args...](){ return new ChildClass(args...); };
}

#endif
