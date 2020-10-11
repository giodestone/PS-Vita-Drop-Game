#include "Transform.h"

#include <maths/quaternion.h>


Transform::Transform()
	: Component(COMPONENT_TAG::TRANSFORM)
{
	position = { 0.f, 0.f, 0.f, 0.f };
	rotation = { 0.f, 0.f, 0.f, 0.f };
	scale = { 1.f, 1.f, 1.f, 0.f };
}


Transform::~Transform()
{}

gef::Vector4 & Transform::Position() 
{ 
	return position; 
}

b2Vec2 Transform::Get2DPosition() const 
{ 
	return b2Vec2(position.x(), position.y()); 
}

gef::Vector4 & Transform::Rotation() 
{ 
	return rotation; 
}

gef::Vector4 & Transform::Scale() 
{ 
	return scale; 
}

void Transform::SetPositon(gef::Vector4 newPosition) 
{ 
	this->position = newPosition; 
}

void Transform::SetRotation(gef::Vector4 newRotation) 
{ 
	this->rotation = newRotation; 
}

void Transform::SetScale(gef::Vector4 newScale) 
{ 
	this->scale = newScale; 
}

void Transform::Update(float dt, class GameObject* caller)
{
	//SRT
	gef::Matrix44 scaleMatrix;
	scaleMatrix.Scale(scale);

	gef::Matrix44 rotationMatrixX;
	gef::Matrix44 rotationMatrixY;
	gef::Matrix44 rotationMatrixZ;
	rotationMatrixX.RotationX(rotation.x());
	rotationMatrixY.RotationY(rotation.y());
	rotationMatrixZ.RotationZ(rotation.z());

	matrix = scaleMatrix * (rotationMatrixX * rotationMatrixY * rotationMatrixZ);

	matrix.SetTranslation(position);
}
