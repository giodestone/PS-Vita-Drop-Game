#include "GameObjectManager.h"



GameObjectManager::GameObjectManager()
	: isUpdating(false),
	removeAll(false)
{
}


GameObjectManager::~GameObjectManager()
{
	for (auto it = gameObjects.begin(); it != gameObjects.end();)
	{
		delete (*it);
		(*it) = nullptr;
		it = gameObjects.erase(it);
	}
}

void GameObjectManager::Update(float dt)
{
	runThroughCollisions();

	isUpdating = true;
	//Go through game objects and delete any ones that should be and update others.
	for (auto it = gameObjects.begin(); it != gameObjects.end();)
	{
		if ((*it)->IsToBeDeleted())
		{
			delete (*it);
			(*it) = nullptr;
			it = gameObjects.erase(it);
		}
		else
		{
			if (Game::GetGameStateManager()->IsPaused())
			{
				if ((*it)->GetTag() == TAG::UPDATE_WHILE_PAUSED)
					(*it)->Update(dt);
			}
			else
				(*it)->Update(dt);
			++it;
		}
	}

	//for (auto& gameobj : gameObjects)
	//	gameobj->Update(dt);
	isUpdating = false;

	//Add any game objects that may have been added during runtime.
	while (!gameObjectsToAdd.empty())
	{
		gameObjects.push_back(gameObjectsToAdd.front());
		gameObjectsToAdd.pop();
	}
	
	//if remove all flag is set remove all objects.
	if (removeAll)
	{
		for (auto it = gameObjects.begin(); it != gameObjects.end();)
		{
			delete (*it);
			(*it) = nullptr;
			it = gameObjects.erase(it);
		}

		removeAll = false;
	}
}

void GameObjectManager::runThroughCollisions()
{
	//Run through collisions
	//get the head of the contact list
	b2Contact* contact = Game::GetB2World()->GetContactList();
	// get contact count
	int contact_count = Game::GetB2World()->GetContactCount();

	for (int contact_num = 0; contact_num<contact_count; ++contact_num)
	{
		if (contact->IsTouching())
		{
			// get the colliding bodies
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();

			// DO COLLISION RESPONSE HERE
			if (static_cast<Component*>(bodyA->GetUserData()) != nullptr &&
				static_cast<Component*>(bodyB->GetUserData()) != nullptr)
			{
				static_cast<Component*>(bodyA->GetUserData())->CollisionResponse(static_cast<Component*>(bodyB->GetUserData())->GetOwner()); //must be static_cast because dynamic_cast only works with complete class types (i.e. void* isn't a class nor is it complete)
				static_cast<Component*>(bodyB->GetUserData())->CollisionResponse(static_cast<Component*>(bodyA->GetUserData())->GetOwner());
			}
		}

		// Get next contact point
		contact = contact->GetNext();
	}
}

void GameObjectManager::Render()
{
	for (auto gameObject : gameObjects)
		gameObject->Render();
}

void GameObjectManager::Render2D()
{
	for (auto gameObject : gameObjects)
		gameObject->Render2D();
}

GameObject* GameObjectManager::AddObject(GameObject * obj)
{
	if (!isUpdating)
		gameObjects.push_back(obj);
	else
		gameObjectsToAdd.emplace(obj);

	return obj;
}

void GameObjectManager::RemoveAll()
{
	removeAll = true;
}
