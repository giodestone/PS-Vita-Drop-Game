#pragma once
#include "Component.h"

#include <box2d\Box2D.h>

class PhysicsComponent :
	public Component
{
	b2Body* body;

public:
	///	<summary>
	/// Component for storing a b2Body and updating the game objects transform to that of the bodies.
	/// </summary>
	///	<param name="bodyDef"></param>
	///	<param name="fixtureDef">Fixture def, remembr to set the user data as a pointer to a Component.</param>
	PhysicsComponent(b2BodyDef bodyDef, b2FixtureDef fixtureDef);
	~PhysicsComponent();

	/// <summary>
	/// Get a pointer to the body being held.
	/// </summary>
	/// <returns>Pointer to the b2Body the object is associated with.</returns>
	b2Body* GetBody() { return body; }

	/// <summary>
	/// Update the position and rotation of the game object from the simulation.
	/// </summary>
	/// <param name="dt">Not used.</param>
	/// <param name="caller">Position of which object will be updated.</param>
	void Update(float dt, class GameObject* caller) override;
private:
	/// <summary>
	/// Updates the positon and rotation of the game object from the b2Body.
	/// </summary>
	/// <param name="object">Object to update it from</param>
	void updatePositionFromSimulation(class GameObject* object);

	/// <summary>
	/// Disconnect the body from all joints.
	/// </summary>
	void disconnectFromAllJoints();
};

