#include "SplashState.h"

#include <thread>

#include "Game.h"
#include "GameObjectManager.h"

#include "MeshComponent.h"
#include "StateChangeButton2DComponent.h"
#include "Sprite2DComponent.h"
#include "SDFOnLoadComponent.h"
#include "Text2DComponent.h"
#include "FloatSprite2DComponent.h"

SplashState::SplashState()
	: GameState(GAME_STATE_ENUM::SPLASH),
	splash(nullptr)
{}


SplashState::~SplashState()
{}

void SplashState::LoadIn()
{
	isLoading.store(true);

	Game::GetAssetManager()->LoadFont("comic_sans", "comic sans"); //need to load font

	//Add loading text
	std::string loadingText = "Loading...";
	float strLength = Game::GetAssetManager()->GetFont("comic sans")->GetStringLength(loadingText.data());

	splash = Game::GetGameObjectManager()->AddObject(new GameObject());
	splash->AddComponent(new Text2DComponent(
		Game::GetAssetManager()->GetFont("comic sans"), 
		loadingText, { (960.f / 2.f) - (strLength / 2.f), 544.f * (5.f / 6.f), 0.f }, //middle of screen 5/6ths down
		1.f, 
		gef::Colour(1.f, 1.f, 1.f)));
	splash->AddComponent(new SDFOnLoadComponent(&isLoading));

	Game::GetAssetManager()->LoadTexture("Logo.png", "logo"); //need to load logo
	
	//Add floating logo
	gef::Sprite* sp = new gef::Sprite();
	sp->set_texture(Game::GetAssetManager()->GetTexture("logo"));
	sp->set_width(512.f);
	sp->set_height(256.f);
	sp->set_position({ (960.f / 2.f), (544.f / 2.f), 0.f }); //put it at centre of the screen.
	auto spriteComp = splash->AddComponent(new Sprite2DComponent(sp));
	splash->AddComponent(new FloatSprite2DComponent(static_cast<Sprite2DComponent*>(spriteComp), 0.5f, 1.f));

	//create thread
	loadingThread = std::thread(SplashState::LoadStuffThreadFunc, &isLoading); //this error is a lie
}

void SplashState::CleanUp()
{
	loadingThread.join();
}

void SplashState::LoadStuffThreadFunc(std::atomic<bool>* isLoading)
{
	//instance meshes
	Game::GetAssetManager()->AddMesh(Game::GetPrimitiveBuilder()->CreateSphereMesh(0.5f, 4, 4), "player");
	Game::GetAssetManager()->AddMesh(Game::GetPrimitiveBuilder()->CreateBoxMesh({ Game::PaddleInfo().HalfWidth, Game::PaddleInfo().HalfHeight, Game::PaddleInfo().HalfDepth }), "paddle");
	Game::GetAssetManager()->AddMesh(Game::GetPrimitiveBuilder()->CreateBoxMesh({ 0.1f, 0.1f, 0.1f }), "paddle base");

	//load textures
	Game::GetAssetManager()->LoadTexture("Play.png", "play button");
	Game::GetAssetManager()->LoadTexture("Instructions.png", "instructions button");
	Game::GetAssetManager()->LoadTexture("HighScore.png", "high score button");
	Game::GetAssetManager()->LoadTexture("Settings.png", "settings button");
	Game::GetAssetManager()->LoadTexture("Exit.png", "exit button");
	Game::GetAssetManager()->LoadTexture("Ticked.png", "ticked");
	Game::GetAssetManager()->LoadTexture("Unticked.png", "unticked");
	Game::GetAssetManager()->LoadTexture("Pause.png", "paused button");
	Game::GetAssetManager()->LoadTexture("Easy.png", "easy button");
	Game::GetAssetManager()->LoadTexture("Medium.png", "medium button");
	Game::GetAssetManager()->LoadTexture("Difficult.png", "hard button");
	Game::GetAssetManager()->LoadTexture("Replay.png", "replay button");
	Game::GetAssetManager()->LoadTexture("Pause.png", "pause button");
	Game::GetAssetManager()->LoadTexture("InstructionsControls.png", "controls");

	//load meshes
	Game::GetAssetManager()->LoadMesh("Box.scn", "spawner");
	Game::GetAssetManager()->LoadMesh("BowlingBall.scn", "bowling ball");
	Game::GetAssetManager()->LoadMesh("PlantPot.scn", "plant pot");
	Game::GetAssetManager()->LoadMesh("Book.scn", "book");
	Game::GetAssetManager()->LoadMesh("BeachBall.scn", "beach ball");

	//load audio
	Game::GetAssetManager()->LoadAudioSample("Spawn.wav", "spawn");
	Game::GetAssetManager()->LoadMusic("GameplayMus.wav");

	//say that we're done loading
	isLoading->store(false);
}
