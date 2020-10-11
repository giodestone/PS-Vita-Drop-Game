#pragma once
#include "Component.h"

#include "StateChangeButton2DComponent.h"
#include "Sprite2DComponent.h"
#include "Text2DComponent.h"

class GamePauserComponent :
	public Component
{
	bool wasPausedDown;

	Text2DComponent* pauseText;

	std::pair<Sprite2DComponent*, StateChangeButton2DComponent*> mainMenu;
	std::pair<Sprite2DComponent*, StateChangeButton2DComponent*> pause;
	std::pair<Sprite2DComponent*, StateChangeButton2DComponent*> unpause;

public:
	/// <summary>
	/// Component reponsible for handing input to pause the game and switching out the UI components depending whether or not the game is paused.
	/// All but text are arguments that are pairs of pointer to Sprite2DComponent, and StateChangeButton2DComponent.
	/// </summary>
	/// <param name="pauseText">Component for text.</param>
	/// <param name="mainMenu">Sprite and button for the main menu. Components should be initially disabled.</param>
	/// <param name="pause">Sprite and button for the pause. Should be left enabled.</param>
	/// <param name="unpause">Sprite and button for the unpause game. Components should be initially disabled.</param>
	/// <remarks>Use std::make_pair to make your life easier. Remember to cast.</remarks>
	GamePauserComponent(Text2DComponent* pauseText, std::pair<Sprite2DComponent*, StateChangeButton2DComponent*> mainMenu, std::pair<Sprite2DComponent*, StateChangeButton2DComponent*> pause, std::pair<Sprite2DComponent*, StateChangeButton2DComponent*> unpause);
	~GamePauserComponent();

	/// <summary>
	/// Check if start was pressed and update the visible components depending on whether the game is paused or not.
	/// </summary>
	/// <param name="dt">Not used.</param>
	/// <param name="caller">Not used.</param>
	void Update(float dt, class GameObject* caller) override;
private:
	/// <summary>
	/// Update what text, buttons/sprites are visible or clikable, depending on whether or not the game is paused.
	/// </summary>
	void updateVisibleAndActive();

	/// <summary>
	/// Check if start was pressed.
	/// </summary>
	void updatePauseStartBtnShortcut();

	/// <summary>
	/// Update whether the game should be paused or not.
	/// </summary>
	void pauseUnpause();
};

