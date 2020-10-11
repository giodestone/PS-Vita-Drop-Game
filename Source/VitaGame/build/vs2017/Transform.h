#pragma once

#include <maths/vector4.h>
#include <maths/matrix44.h>
#include <Box2D/Box2D.h>

#include "Component.h"

class Transform : public Component
{
	gef::Vector4 position;
	gef::Vector4 rotation; //Euler angles
	gef::Vector4 scale;

	gef::Matrix44 matrix;

public:
	/// <summary>
	/// Transform for a GameObject.
	/// </summary>
	/// <remarks>I am aware that the gef::Transform class exists but this is tailor made keep rotation as an euler angle.</remarks>
	Transform();
	virtual ~Transform();

	/// <summary>
	/// Get the reference to the position vector.
	/// </summary>
	/// <returns>Reference to position vector.</returns>
	gef::Vector4& Position();

	/// <summary>
	/// Returns a vector 2 with the x and y component.
	/// </summary>
	/// <returns></returns>
	b2Vec2 Get2DPosition() const;

	/// <summary>
	/// Get the reference to the rotation vector, which stores the position via euler angles.
	/// </summary>
	/// <returns>Reference to rotation vector.</returns>
	gef::Vector4& Rotation();

	/// <summary>
	/// Get the reference to the scale vector.
	/// </summary>
	/// <returns>Reference to the scale vector.</returns>
	gef::Vector4& Scale();

	/// <summary>
	/// Set the position vector.
	/// </summary>
	/// <param name="newPosition"></param>
	void SetPositon(gef::Vector4 newPosition);
	
	/// /// <summary>
	/// Set the rotation vector.
	/// </summary>
	/// <param name="newRotation"></param>
	void SetRotation(gef::Vector4 newRotation);

	/// <summary>
	/// Set the scale vector.
	/// </summary>
	/// <param name="newScale"></param>
	void SetScale(gef::Vector4 newScale);

	/// <summary>
	/// Returns the matrix with the transformations.
	/// 
	/// Note that the transform is not updated every time a new value is applied. Only every frame. Call update to fix that.
	/// </summary>
	/// <returns>Matrix with the transformations.</returns>
	gef::Matrix44& GetMatrix() { return matrix; }
	
	/// <summary>
	/// Update the transformation matrix from the position, rotation, and scale values in the class.
	/// </summary>
	/// <param name="dt">Not used.</param>
	/// <param name="caller">Not used.</param>
	/// <remarks>Quite performance intensive. No checks are performed if the underlying values have changed.</remarks>
	void Update(float dt, class GameObject* caller) override;
};

