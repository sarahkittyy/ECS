#include "ECS/World.hpp"

namespace ECS
{

World::World()
{
	mNextID = 0;
}

void World::update(float msElapsed)
{
	//Update each system.
	for (auto& [info, system] : mSystems)
	{
		system->tick(this, msElapsed);
	}
}

Entity* World::createEntity()
{
	mEntities[++mNextID] = Entity();
	return &mEntities[mNextID];
}

void World::all(std::function<void(Entity& e)> fn)
{
	for (auto& [id, e] : mEntities)
	{
		fn(e);
	}
}

}