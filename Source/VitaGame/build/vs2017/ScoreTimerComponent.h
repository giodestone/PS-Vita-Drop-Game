#pragma once
#include "Component.h"
#include "Text2DComponent.h"

class ScoreTimerComponent :
	public Component
{
	Text2DComponent* text2DComponent;

	float timeElapsed; //total time elapsed since object got created.
	float nextTimeToAddScore;
public:
	/// <summary>
	/// Component responsible for adding 1 score every second that its active, and updating the text component with the current score.
	/// </summary>
	/// <param name="t2dComp">Text2DComponent that the score will be drawn to with a 'Score: ' precursor.</param>
	ScoreTimerComponent(Text2DComponent* t2dComp);
	~ScoreTimerComponent();

	/// <summary>
	/// Adds a point to the score every second and updates text with the object.
	/// </summary>
	/// <param name="dt">Used for keeping track of time.</param>
	/// <param name="caller">Not used.</param>
	void Update(float dt, class GameObject* caller) override;

private:
	/// <summary>
	/// Updates the text2d component with precursor 'Score: ' text.
	/// </summary>
	void updateText2DComponentTextWithScore();
};

