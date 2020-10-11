#pragma once
#include "Component.h"

#include <Box2D/Box2D.h>

class RevoluteJointComponent :
	public Component
{
	b2RevoluteJoint* revoluteJoint;
public:
	/// <summary>
	/// Component for the b2revolutejoint.
	/// </summary>
	/// <param name="revoluteJointDef">Joint def, will override any userdata set.</param>
	RevoluteJointComponent(b2RevoluteJointDef revoluteJointDef);
	~RevoluteJointComponent();

	/// <summary>
	/// Get the pointer to the revolute joint.
	/// </summary>
	/// <returns>Pointer to b2RevoluteJoint.</returns>
	inline b2RevoluteJoint* GetRevoluteJoint() { return revoluteJoint; }

	/// <summary>
	/// Set the pointer to the revolute joint.
	/// </summary>
	/// <param name="revoluteJoint"></param>
	inline void SetRevoluteJoint(b2RevoluteJoint* revoluteJoint) { this->revoluteJoint = revoluteJoint; }
};

