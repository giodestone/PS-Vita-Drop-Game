#pragma once

#include "ComponentTag.h"
/// <summary>
/// Base component class. Place any behaviour you want to add to the GameObject class to a class derived from this one.
/// </summary>
class Component
{
	class GameObject* owner; //Which GameObject 'owns' the component

	COMPONENT_TAG componentTag;

	bool toBeDeleted;
public:
	/// <summary>
	/// The base component for all components.
	/// </summary>
	/// <param name="componentTag"></param>
	Component(COMPONENT_TAG componentTag);
	virtual ~Component();

	/// <summary>
	/// Update method for the component.
	/// </summary>
	/// <param name="dt">Time between updates.</param>
	/// <param name="caller">What game object called the method.</param>
	virtual void Update(float dt, class GameObject* caller);

	/// <summary>
	/// Render method for the componenet.
	/// </summary>
	/// <param name="caller">What game object called the method.</param>
	virtual void Render(class GameObject* caller);

	/// <summary>
	/// Render 2D/spritebatch method for the component.
	/// </summary>
	/// <param name="caller">Which game object called the menthod.</param>
	virtual void Render2D(class GameObject* caller);

	/// <summary>
	/// Collision response method, should be called if the game object has a physics component.
	/// </summary>
	/// <param name="other">The object that the collision happened with.</param>
	virtual void CollisionResponse(class GameObject* other);

	/// <summary>
	/// Set the owner of the component.
	/// </summary>
	/// <param name="owner">Owning GameObject.</param>
	void SetOwner(class GameObject* owner);

	/// <summary>
	/// Get the owner of the component.
	/// </summary>
	/// <returns>Owner of the component.</returns>
	GameObject* GetOwner();

	/// <summary>
	/// Get the components' tag.
	/// </summary>
	/// <returns>Component tag.</returns>
	COMPONENT_TAG& GetComponentTag();

	/// <summary>
	/// Whether the component should be removed at the next update.
	/// </summary>
	/// <returns>Whether the component should be removed at the next update.</returns>
	bool IsToBeDeleted();
	
	/// <summary>
	/// Mark the component to be deleted at the next update.
	/// </summary>
	void Delete();
};

