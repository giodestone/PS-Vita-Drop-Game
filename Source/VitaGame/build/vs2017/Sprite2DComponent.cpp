#include "Sprite2DComponent.h"

#include "Game.h"
#include "GameObject.h"

#include <graphics/sprite_renderer.h>
#include <assets/png_loader.h>

Sprite2DComponent::Sprite2DComponent(gef::Sprite * sprite, bool shouldRender)
	: Component(COMPONENT_TAG::SPRITE_2D),
	sprite(sprite),
	shouldRender(shouldRender)
{
}

Sprite2DComponent::~Sprite2DComponent()
{
	delete sprite;
	sprite = nullptr;
}

void Sprite2DComponent::Render2D(GameObject * caller)
{
	if (shouldRender)
		Game::GetSpriteRenderer()->DrawSprite(*sprite);
}
