#pragma once

#include <vector>
#include <queue>

#include "Game.h"
#include "Transform.h"
#include "TAGS.h"

/// <summary>
/// Stores anything in game. Contains components which is where the behaviour of the class is stored.
/// </summary>
class GameObject
{
	std::vector<Component*> components;
	std::queue<Component*> objectsToAdd;
	Transform* transform; //Root transform of the whole object.

	bool isToBeDeleted;
	bool isUpdating;

	TAG tag;
public:
	/// <summary>
	/// Game Object is the class which should contain components.
	/// </summary>
	GameObject();
	GameObject(TAG tag, Transform* newTransform);
	~GameObject();

	std::vector<Component*>& GetComponenets();
	Transform& GetTransform();
	Transform* GetTransformPtr();
	
	/// <summary>
	/// Add a component.
	/// </summary>
	/// <param name="component">The pointer to the component.</param>
	/// <returns>The component that was added.</returns>
	Component* AddComponent(Component* component);

	/// <summary>
	/// Get all of the components that have the same tag.
	/// </summary>
	/// <param name="tag">Tag to match.</param>
	/// <returns>All components that the game object has that match the tag.</returns>
	std::vector<Component*> GetComponentByTag(COMPONENT_TAG tag);

	/// <summary>
	/// Should the object be deleted next update.
	/// </summary>
	/// <returns>Whether the object should be deleted.</returns>
	bool IsToBeDeleted() { return isToBeDeleted; }

	/// <summary>
	/// Mark the object to be deleted.
	/// </summary>
	void Remove() { isToBeDeleted = true; }

	/// <summary>
	/// Get the tag of the game object.
	/// </summary>
	/// <returns>Tag of the game object.</returns>
	TAG GetTag() const { return tag; }

	/// <summary>
	/// Set the tag of the game object.
	/// </summary>
	/// <param name="tag">What the new tag should be.</param>
	void SetTag(const TAG tag) { this->tag = tag; }

private: //for use witith GameObjectManager
	friend class GameObjectManager; //So the methods are not called by any one else.

	/// <summary>
	/// Main update for all game componenets.
	/// </summary>
	/// <param name="dt">Time between update calls.</param>
	void Update(float dt);

	/// <summary>
	/// Main render for all the game componenets.
	/// </summary>
	void Render();

	/// <summary>
	/// Render 2d for all the game components.
	/// </summary>
	void Render2D();
};

