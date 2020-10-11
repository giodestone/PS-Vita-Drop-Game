#pragma once
#include "Component.h"

#include <graphics/font.h>
#include <graphics/colour.h>
#include <maths/vector4.h>
#include <string>
class Text2DComponent :
	public Component
{
	gef::Font* font; //Do not dispose as Asset manager takes care of it.
	std::string fontText;
	gef::Vector4 fontPos;
	UInt32 fontColor; //In ABGR.
	float fontScale;
	gef::TextJustification fontJustification;

	bool shouldRender;
public:
	/// <summary>
	/// Component for drawing text.
	/// Note like the Sprite2DComponent it doesn't use the owning GameObject's position.
	/// </summary>
	/// <param name="font">Font to use.</param>
	/// <param name="text">Text to display.</param>
	/// <param name="pos">Where on the screen it should be.</param>
	/// <param name="scale">How big the text should be.</param>
	/// <param name="color">What colour the text should be.</param>
	Text2DComponent(gef::Font* font, std::string text, gef::Vector4 pos, float scale, gef::Colour color);
	Text2DComponent(gef::Font* font, std::string text, gef::Vector4 pos, float scale, gef::Colour color, gef::TextJustification justification, bool shouldRender = true);
	~Text2DComponent();

	/// <summary>
	/// Set the text being rendered.
	/// </summary>
	/// <param name="text">What the text should say.</param>
	inline void SetText(std::string text) { fontText = text; }

	/// <summary>
	/// Renders the font to the screen, if shouldRender is true.
	/// </summary>
	/// <param name="caller">Not used.</param>
	void Render2D(class GameObject* caller) override;

	/// <summary>
	/// Should the text be rendered.
	/// </summary>
	/// <returns>Whether or not the text should be rendered.</returns>
	inline bool ShouldRender() const { return shouldRender; }

	/// <summary>
	/// Set whether the text should be rendered.
	/// </summary>
	/// <param name="shouldRender">Whether the text should be rendered.</param>
	inline void SetShouldRender(bool shouldRender) { this->shouldRender = shouldRender; }
};

