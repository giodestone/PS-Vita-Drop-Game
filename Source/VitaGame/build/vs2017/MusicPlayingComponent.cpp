#include "MusicPlayingComponent.h"

#include "Game.h"


MusicPlayingComponent::MusicPlayingComponent(bool stopOnDestory)
	: Component(COMPONENT_TAG::MUSIC_PLAYER),
	stopOnDestory(stopOnDestory)
{
	if (Game::Configuration().PlayMusic && (Game::Configuration().PlayingMusic == false) && Game::GetAudioManager() != nullptr) //play music if it should
	{
		Game::Configuration().PlayingMusic = true;
		Game::GetAudioManager()->PlayMusic();
	}
}

MusicPlayingComponent::~MusicPlayingComponent()
{
	if (stopOnDestory && Game::GetAudioManager() != nullptr) //stop playing on destroy
	{
		Game::GetAudioManager()->StopMusic();
		Game::Configuration().PlayingMusic = false;
	}
}

void MusicPlayingComponent::Update(float dt, GameObject * caller)
{
	if (Game::Configuration().PlayMusic == false && Game::Configuration().PlayingMusic && Game::GetAudioManager() != nullptr) //if playing music and need to stop
	{
		Game::GetAudioManager()->StopMusic(); //stop playing
		Game::Configuration().PlayingMusic = false;
	}
	else if (Game::Configuration().PlayMusic && Game::Configuration().PlayingMusic == false && Game::GetAudioManager() != nullptr) //if should pay music and not playing music
	{
		Game::GetAudioManager()->PlayMusic(); //start playing
		Game::Configuration().PlayingMusic = true;
	}
}
