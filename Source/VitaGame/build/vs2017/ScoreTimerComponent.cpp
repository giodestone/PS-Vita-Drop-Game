#include "ScoreTimerComponent.h"
#include <string>
#include "Game.h"

#include <sstream>

ScoreTimerComponent::ScoreTimerComponent(Text2DComponent* t2dComp)
	: Component(COMPONENT_TAG::SCORE_TIMER),
	text2DComponent(t2dComp),
	timeElapsed(0.f)
{
	nextTimeToAddScore = Game::Configuration().StartDelay;
	updateText2DComponentTextWithScore();
}


ScoreTimerComponent::~ScoreTimerComponent()
{}

void ScoreTimerComponent::Update(float dt, GameObject * caller)
{
	timeElapsed += dt;
	if (timeElapsed >= nextTimeToAddScore) //add score next time its time
	{
		Game::SetScore(Game::GetScore() + 1);
		nextTimeToAddScore = timeElapsed + 1.f;
		updateText2DComponentTextWithScore();
	}

}

void ScoreTimerComponent::updateText2DComponentTextWithScore()
{
	std::stringstream ss;
	ss << "Score: ";
	ss << Game::GetScore();
	text2DComponent->SetText(ss.str());
}
