#include "ECS/World.hpp"

namespace ECS
{

World::World()
{
	mNextID = 0;
}

World::~World()
{
}

void World::update(float msElapsed)
{
	//Call onUpdate().
	onUpdate(msElapsed);

	//Update each system.
	for (auto& [info, system] : mSystems)
	{
		system->tick(this, msElapsed);
	}
}

void World::onUpdate(float msElapsed)
{
}

Entity* World::createEntity()
{
	mNextID++;
	mEntities[mNextID] = Entity(mNextID);
	return &mEntities[mNextID];
}

Entity* World::getEntityByID(long long id)
{
	//try to find it...
	auto found = mEntities.find(id);
	if (found == mEntities.end())   //not found..
	{
		//Return nullptr.
		return nullptr;
	}
	//Otherwise, return the found item.
	return &mEntities[id];
}

void World::removeEntity(long long id)
{
	//Erase the element at [id]
	mEntities.erase(id);
}

void World::all(std::function<void(Entity& e)> fn)
{
	for (auto& [id, e] : mEntities)
	{
		fn(e);
	}
}

}