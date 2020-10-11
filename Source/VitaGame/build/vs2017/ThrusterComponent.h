#pragma once
#include "Component.h"
#include "PhysicsComponent.h"
class ThrusterComponent :
	public Component
{
	PhysicsComponent* paddle;

public:
	/// <summary>
	/// This component is for controlling the 'thrusters' on the paddle. It has two thruster.
	/// </summary>
	/// <param name="paddle">Object to apply the force to.</param>
	/// <remarks>The thrusters are really just calls to apply a force to a positon in the world, in relation to the rotation of the object.</remarks>
	ThrusterComponent(PhysicsComponent* paddle);
	~ThrusterComponent();

	/// <summary>
	/// Applies a force depending on the controller analouge sticks to the two thrusters.
	/// </summary>
	/// <param name="dt">Not used.</param>
	/// <param name="caller">Not used.</param>
	void Update(float dt, class GameObject* caller) override;
};

