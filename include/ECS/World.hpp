#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "ECS/Components/Components.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Systems/Systems.hpp"

namespace ECS
{

/**
 * @brief The entity component system world.
 * 
 */
class World
{
public:
	/**
	 * @brief Construct the world.
	 * 
	 */
	World();

	/**
	 * @brief Update the world.
	 * 
	 * @param msElapsed The time to simulate between the last update.
	 */
	void update(float msElapsed = 0);

	/**
	 * @brief Create a world entity.
	 * 
	 * @return Entity::Entity* The created entity.
	 */
	Entity* createEntity();

	/**
	 * @brief Configure a system to be used.
	 * 
	 * @tparam Sys The system to use in this world.
	 * @tparam Args Argument types passed to the system constructor.
	 * @param args The args passed to the system constructor.
	 * @return System::System Generic pointer to the system itself.
	 */
	template <typename Sys, typename... Args>
	System::System useSystem(Args&&... args)
	{
		//Get the system type info.
		TypeInfo info = &typeid(Sys);
		// Try to find it.
		auto found = mSystems.find(info);
		if (found == mSystems.end())   //If it wasn't found..
		{
			//Create it.
			mSystems[info] = System::System(new Sys(args...));
		}
		else   //Otherwise, just reset it.
		{
			mSystems[info].reset(new Sys(args...));
		}

		//Return the created system.
		return mSystems[info];
	}

	/**
	 * @brief Run a function over each entity with each given component.
	 * 
	 * @tparam Comps The components required to run the system over the entity..
	 * @param fn The function to run through. 
	 */
	template <typename... Comps>
	void each(std::function<void(Entity& e)> fn)
	{
		//For every entity...
		for (auto& [id, e] : mEntities)
		{
			//If the entity has all Required components...
			if (e.has<Comps...>())
			{
				//Run the function over it.
				fn(e);
			}
		}
	}

	/**
	 * @brief Run a function on all entities.
	 * 
	 * @param fn The function to run.
	 */
	void all(std::function<void(Entity& e)> fn);

private:
	/**
	 * @brief A map of entity IDs to their entities.
	 * 
	 */
	std::unordered_map<long long, Entity> mEntities;
	long long mNextID;   ///< The next entity ID.

	/**
	 * @brief A map of type info to the corresponding world system.
	 * 
	 */
	std::unordered_map<TypeInfo, System::System> mSystems;
};

}