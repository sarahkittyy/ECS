#pragma once

#include <memory>

namespace ECS
{

/// Forward declaration of class world.
/// In inheriting classes, include ECS/World.hpp directly.
class World;

namespace System
{

/**
 * @brief A system interface, to be inherited by functional systems.
 * 
 */
class ISystem
{
public:
	/**
	 * @brief Called every world update.
	 * 
	 * @param world The ECS world.
	 * @param msElapsed The ms elapsed since last update.
	 */
	virtual void tick(ECS::World* world, float msElapsed) = 0;
};

/**
 * @brief Generic System object.
 * 
 */
typedef std::shared_ptr<ISystem> System;

}

}