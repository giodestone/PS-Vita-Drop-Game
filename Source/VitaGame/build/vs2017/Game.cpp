#include "Game.h"

#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <input/sony_controller_input_manager.h>
#include <graphics/mesh.h>
#include <graphics/renderer_3d.h>
#include <system/debug_log.h>
#include <graphics/font.h>
#include "GameObjectManager.h"
#include <Box2D/Box2D.h>
#include "audio_3d.h"


gef::InputManager* Game::inputManager = nullptr;
gef::AudioManager* Game::audioManager = nullptr;
Audio3D* Game::audio3D = nullptr;
gef::Renderer3D* Game::renderer3d = nullptr;
gef::SpriteRenderer* Game::spriteRenderer = nullptr;
PrimitiveBuilder* Game::primitiveBuilder = nullptr;
class GameObjectManager* Game::gameObjectManager = nullptr;
b2World* Game::world = nullptr;
AssetManager* Game::assetManager = nullptr;
GameStateManager* Game::gameStateManager = nullptr;

gef::Material Game::defaultMaterial;

bool Game::isInitialised = false;

PaddleInfo Game::paddleInfo;

Configuration Game::configuration;

int Game::score = 0;

bool Game::shouldExit = false;

void Game::Init(gef::InputManager* in, gef::AudioManager* au, Audio3D* a3d, gef::Renderer3D* r3d, gef::SpriteRenderer* sr, PrimitiveBuilder* pb, GameObjectManager* gom, b2World* w, AssetManager* am, GameStateManager* gsm)
{
	inputManager = in;
	audioManager = au;
	audio3D = a3d;
	renderer3d = r3d;
	spriteRenderer = sr;
	primitiveBuilder = pb;
	gameObjectManager = gom;
	world = w;
	assetManager = am;
	gameStateManager = gsm;

	defaultMaterial = primitiveBuilder->green_material();

	isInitialised = true;
}

gef::InputManager * Game::GetInputManager()
{
	return inputManager;
}

gef::AudioManager * Game::GetAudioManager()
{
	return audioManager;
}

Audio3D * Game::GetAudio3D()
{
	return audio3D;
}

gef::Renderer3D * Game::GetRenderer3D()
{
	return renderer3d;
}

gef::SpriteRenderer * Game::GetSpriteRenderer()
{
	return spriteRenderer;
}

PrimitiveBuilder * Game::GetPrimitiveBuilder()
{
	return primitiveBuilder;
}

GameObjectManager * Game::GetGameObjectManager()
{
	return gameObjectManager;
}

b2World * Game::GetB2World()
{
	return world;
}

AssetManager * Game::GetAssetManager()
{
	return assetManager;
}

GameStateManager * Game::GetGameStateManager()
{
	return gameStateManager;
}

gef::Material Game::GetDefaultMaterial()
{
	return defaultMaterial;
}

PaddleInfo & Game::PaddleInfo()
{
	return paddleInfo;
}

Configuration & Game::Configuration()
{
	return configuration;
}

int Game::GetScore()
{
	return score;
}

void Game::SetScore(int newScore)
{
	score = newScore;
}

void Game::Exit()
{
	shouldExit = true;
}

bool Game::NotExit()
{
	return !shouldExit;
}

Game::Game()
{}


Game::~Game()
{}
