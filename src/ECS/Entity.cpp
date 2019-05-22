#include "ECS/Entity.hpp"

namespace ECS
{

Entity::Entity(long long ID)
	: mID(ID)
{
}

const long long Entity::getID()
{
	return mID;
}

}