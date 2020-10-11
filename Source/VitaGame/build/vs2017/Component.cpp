#include "Component.h"



Component::Component(COMPONENT_TAG componentTag)
	: componentTag(componentTag),
	toBeDeleted(false)
{}


Component::~Component()
{}

void Component::Update(float dt, class GameObject* caller)
{}

void Component::Render(class GameObject* caller)
{}

void Component::Render2D(GameObject * caller)
{}

void Component::CollisionResponse(GameObject* other)
{}

void Component::SetOwner(GameObject * owner) 
{ 
	this->owner = owner; 
}

GameObject * Component::GetOwner()
{
	return owner;
}

COMPONENT_TAG & Component::GetComponentTag() 
{ 
	return componentTag; 
}

/// <summary>
/// Whether the component should be removed at the next update.
/// </summary>
/// <returns>Whether the component should be removed at the next update.</returns>

bool Component::IsToBeDeleted() 
{ 
	return toBeDeleted; 
}

void Component::Delete() 
{ 
	toBeDeleted = true; 
}
