#include "PhysicsComponent.h"

#include "GameObject.h"

#include "RevoluteJointComponent.h"

PhysicsComponent::PhysicsComponent(b2BodyDef bodyDef, b2FixtureDef fixtureDef)
	: Component(COMPONENT_TAG::PHYSICS)
{
	body = Game::GetB2World()->CreateBody(&bodyDef); //create body
	body->CreateFixture(&fixtureDef); //add fixture
}

PhysicsComponent::~PhysicsComponent()
{
	body->SetUserData(nullptr);
	
	disconnectFromAllJoints();

	Game::GetB2World()->DestroyBody(body); //now destroy the body
	body = nullptr;
}

void PhysicsComponent::disconnectFromAllJoints()
{
	std::vector<b2Joint*> jointsToRemove;
	auto jointIter = body->GetJointList();
	while (jointIter != nullptr) //get all joints that the body is connected to for later deletion
	{
		jointsToRemove.push_back(jointIter->joint);
		jointIter = jointIter->next;
	}

	for (auto it = jointsToRemove.begin(); it != jointsToRemove.end();)
	{
		static_cast<RevoluteJointComponent*>((*it)->GetUserData())->SetRevoluteJoint(nullptr); //so it doesn't try to delete a joint at a (in a moment) dangling pointer.
		static_cast<RevoluteJointComponent*>((*it)->GetUserData())->Delete(); //mark game object for deletion
		Game::GetB2World()->DestroyJoint((*it)); //actually destroy the joint
		(*it) = nullptr; //mark it deleted
		it = jointsToRemove.erase(it); //move onto next one.
	}
}

void PhysicsComponent::Update(float dt, GameObject * caller)
{
	updatePositionFromSimulation(caller);
}

void PhysicsComponent::updatePositionFromSimulation(GameObject * object)
{
	auto pos = body->GetPosition();
	object->GetTransform().SetPositon(gef::Vector4(body->GetPosition().x, body->GetPosition().y, object->GetTransform().Position().z()));
	object->GetTransform().SetRotation(gef::Vector4(object->GetTransform().Rotation().x(), object->GetTransform().Rotation().y(), body->GetAngle()));
}
