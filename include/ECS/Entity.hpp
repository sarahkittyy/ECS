#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include <typeinfo>
#include <unordered_map>

#include "ECS/Components/Component.hpp"
#include "ECS/TypeInfo.hpp"

namespace ECS
{

/**
 * @brief An entity object for the ECS.
 * 
 */
class Entity
{
public:
	/**
	 * @brief Default constructor.
	 * 
	 */
	Entity();

	/**
	 * @brief Default entity constructor.
	 * 
	 * @param ID The entity's ID.
	 */
	Entity(long long ID);

	/**
	 * @brief Get the entity's ID.
	 * 
	 * @return const long long The entity's ID.
	 */
	const long long getID();

	/**
	 * @brief Add a component to the 
	 * 
	 * @tparam Comp The type of component to add. 
	 * @tparam Args The parameter pack of args to send to the component constructor.
	 * @param args The arguments to pass to the component constructor.
	 * @return Component::BaseComponent A pointer to that component.
	 */
	template <typename Comp, typename... Args>
	Component::Component add(Args&&... args)
	{
		//Get the component info
		TypeInfo info = &typeid(Comp);
		//Try to find the info in the map.
		auto found = mComponents.find(info);
		if (found == mComponents.end())   //If it's not found..
		{
			//Append it.
			mComponents[info] = Component::Component(new Comp(args...));
		}
		//Otherwise, just reset the found component.
		else
		{
			found->second.reset(new Comp(args...));
		}

		//Return it.
		return mComponents[info];
	}

	/**
	 * @brief Checks if the entity has all given components. 
	 * 
	 * @tparam Comp(s) The components to check for.
	 * @return true If all the components exist
	 * @return false Otherwise.
	 */
	template <typename Comp, typename Comp2, typename... Comps>
	bool has()
	{
		return has<Comp>() && has<Comp2>() && has<Comps...>();
	}

	/**
	 * @brief Checks if the entity has a single component.
	 * 
	 * @tparam Comp The component to check for.
	 * @return true If the entity has that component.
	 * @return false Otherwise.
	 */
	template <typename Comp>
	bool has()
	{
		return mComponents.find(&typeid(Comp)) != mComponents.end();
	}

	/**
	 * @brief Gets the component with the given type T.
	 * 
	 * @tparam T The type of the component.
	 * @return T& A reference to that component.
	 * 
	 * @throws std::out_of_range if the component doesn't exist.
	 */
	template <typename T>
	T& get()
	{
		if (!has<T>())
		{
			throw std::out_of_range("Component on entity not found!");
		}
		else
		{
			//Return it.
			return *reinterpret_cast<T*>(mComponents[&typeid(T)].get());
		}
	}

	/**
	 * @brief Remove the given component from the entity.
	 * 
	 * @tparam Comp The component to remove
	 */
	template <typename Comp>
	void remove()
	{
		//Get the component info
		TypeInfo info = &typeid(Comp);
		//Try to find the info in the map.
		auto found = mComponents.find(info);
		if (found != mComponents.end())   //If it's found..
		{
			//Remove it
			mComponents.erase(found);
		}
	}

private:
	/// All of this entity's components.
	std::unordered_map<TypeInfo, Component::Component> mComponents;
	long long mID;   ///< The entity's ID.
};

}