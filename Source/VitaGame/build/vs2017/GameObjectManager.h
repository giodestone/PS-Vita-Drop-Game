#pragma once

#include <vector>
#include <queue>
#include "GameObject.h"

class GameObjectManager
{
	std::vector<GameObject*> gameObjects;

	std::queue<GameObject*> gameObjectsToAdd;

	bool isUpdating; //to stop objects getting added when iterating through.
	bool removeAll; //mark all the things to delete
public:
	/// <summary>
	/// Manages game objects.
	/// </summary>
	GameObjectManager();
	~GameObjectManager();

	/// <summary>
	/// Calls update on all member game objects and handles physics.
	/// </summary>
	/// <param name="dt">Time between update calls.</param>
	void Update(float dt);

	/// <summary>
	/// Calls render on all the member game objects.
	/// </summary>
	void Render();

	/// <summary>
	/// Calls the render 2d method on all member game objects.
	/// </summary>
	void Render2D();

	/// <summary>
	/// Add a game object. Doesn't add to game objects if currently iterating through.
	/// </summary>
	/// <param name="obj">Pointer to the object.</param>
	/// <returns>The object that was added.</returns>
	GameObject* AddObject(GameObject* obj);

	/// <summary>
	/// Mark all game objects for deletion.
	/// </summary>
	/// <remarks>At most one full update cycle will complete before everything is deleted.</remarks>
	void RemoveAll();

private:
	/// <summary>
	/// Go through all collisions and call collision response if possible.
	/// </summary>
	void runThroughCollisions();
};

