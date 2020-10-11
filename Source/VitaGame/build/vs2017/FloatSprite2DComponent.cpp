#include "FloatSprite2DComponent.h"

#include <math.h>
#include <maths/math_utils.h>

FloatSprite2DComponent::FloatSprite2DComponent(Sprite2DComponent * spriteToFloat, float amplitude, float frequency)
	: Component(COMPONENT_TAG::SPRITE_FLOATER),
	spriteToFloat(spriteToFloat),
	amplidtude(amplitude),
	frequency(frequency),
	timeElapsed(0.f)
{
}

FloatSprite2DComponent::~FloatSprite2DComponent()
{
}

void FloatSprite2DComponent::Update(float dt, GameObject * caller)
{
	timeElapsed += dt;
	float yPos = spriteToFloat->GetSprite()->position().y() + sinf(timeElapsed * 3.14159f * frequency) * amplidtude; //move the y axis along the sine

	spriteToFloat->GetSprite()->set_position(gef::Vector4(spriteToFloat->GetSprite()->position().x(),
		yPos,
		spriteToFloat->GetSprite()->position().z()));
}
