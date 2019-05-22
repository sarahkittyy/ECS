#pragma once

#include <memory>
#include <typeinfo>

#include "ECS/TypeInfo.hpp"

namespace ECS::Component
{

/**
 * @brief The base component interface..
 * 
 */
class IComponent
{
};

/**
 * @brief An actual component.
 * 
 */
typedef std::shared_ptr<IComponent> Component;

}