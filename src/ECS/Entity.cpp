#include "ECS/Entity.hpp"

namespace ECS
{

Entity::Entity()
	: mID(-1)
{
}

Entity::Entity(long long ID)
	: mID(ID)
{
}

const long long Entity::getID()
{
	return mID;
}

}