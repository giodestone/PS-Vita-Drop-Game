#include "GameObject.h"

#include "Transform.h"


GameObject::GameObject()
	: GameObject(TAG::NONE, new Transform())
{}

GameObject::GameObject(TAG tag, Transform* newTransform) 
	: isToBeDeleted(false),
	tag(tag),
	isUpdating(false)
{
	AddComponent(newTransform);
	transform = newTransform;
	//transform->SetOwner(this);
}

GameObject::~GameObject()
{
	for (auto it = components.begin(); it != components.end();)
	{
		delete *it;
		*it = nullptr;
		it = components.erase(it);
	}
}

std::vector<Component*>& GameObject::GetComponenets() { return components; }

Transform & GameObject::GetTransform() 
{ 
	return *transform; 
}

Transform * GameObject::GetTransformPtr()
{
	return transform;
}

Component* GameObject::AddComponent(Component* component)
{
	component->SetOwner(this);
	if (isUpdating)
	{
		objectsToAdd.push(component);
	}
	else
	{
		components.push_back(component);
	}
	return component;
}

std::vector<Component*> GameObject::GetComponentByTag(COMPONENT_TAG tag)
{
	std::vector<Component*> results;
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->GetComponentTag() == tag)
			results.push_back((*it));
	}
	return results;
}

void GameObject::Update(float dt)
{
	isUpdating = true;
	for (auto it = components.begin(); it != components.end();)
	{
		if ((*it)->IsToBeDeleted())
		{
			delete (*it);
			(*it) = nullptr;
			it = components.erase(it);
		}
		else
		{
			(*it)->Update(dt, this);
			++it;
		}
	}
	isUpdating = false;

	while (!objectsToAdd.empty())
	{
		
		auto objAtFront = objectsToAdd.front();
		objAtFront->SetOwner(this);
		components.push_back(objAtFront);
		objectsToAdd.pop();
	}
}

void GameObject::Render()
{
	for (auto& component : components)
		component->Render(this);
}

void GameObject::Render2D()
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Render2D(this);
	}
}
