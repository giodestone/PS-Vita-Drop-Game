#include "RevoluteJointComponent.h"

#include "Game.h"

RevoluteJointComponent::RevoluteJointComponent(b2RevoluteJointDef revoluteJointDef)
	: Component(COMPONENT_TAG::REVOLUTE)
{
	revoluteJoint = static_cast<b2RevoluteJoint*>(Game::GetB2World()->CreateJoint(&revoluteJointDef));
	revoluteJoint->SetUserData(this);
}

RevoluteJointComponent::~RevoluteJointComponent()
{
	if (revoluteJoint != nullptr) //TODO: If this component would ever get destroyed first it could cause problems.
	{
		Game::GetB2World()->DestroyJoint(revoluteJoint);
		revoluteJoint = nullptr;
	}
}
