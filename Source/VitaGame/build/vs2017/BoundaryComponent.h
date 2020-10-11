#pragma once
#include "Component.h"
class BoundaryComponent :
	public Component
{
public:
	/// <summary>
	/// Component for the boundary, i.e. where objects get deleted.
	/// </summary>
	BoundaryComponent();
	~BoundaryComponent();

	/// <summary>
	/// Used to mark objects to be deleted or whether the game should go into GameOver.
	/// </summary>
	/// <param name="other">What is the other game object that has collided with it.</param>
	void CollisionResponse(class GameObject* other) override;
};

