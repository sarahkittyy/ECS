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

Entity::Entity* World::createEntity()
{
	mEntities[++mNextID] = Entity::Entity();
	return &mEntities[mNextID];
}

}