#include "Text2DComponent.h"

#include "Game.h"
#include <graphics/sprite_renderer.h>

Text2DComponent::Text2DComponent(gef::Font * font, std::string text, gef::Vector4 pos, float scale, gef::Colour color)
	: Text2DComponent(font, text, pos, scale, color, gef::TJ_LEFT, true)
{
}

Text2DComponent::Text2DComponent(gef::Font* font, std::string text, gef::Vector4 pos, float scale, gef::Colour color, gef::TextJustification justification, bool shouldRender)
	: Component(COMPONENT_TAG::TEXT_2D),
	font(font),
	fontText(text),
	fontPos(pos),
	fontScale(scale),
	fontColor(color.GetABGR()),
	fontJustification(justification),

	shouldRender(shouldRender)
{
}

Text2DComponent::~Text2DComponent()
{
}

void Text2DComponent::Render2D(GameObject * caller)
{
	if (shouldRender)
		font->RenderText(Game::GetSpriteRenderer(), fontPos, fontScale, fontColor, fontJustification, fontText.data());
}
