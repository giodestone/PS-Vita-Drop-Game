#pragma once

#include <audio/audio_manager.h>
#include <primitive_builder.h>
#include <Box2D\Box2D.h>
#include "audio_3d.h"
#include "AssetManager.h"
#include "GameStateManager.h"

//Struct for holding informat ion about the paddle
struct PaddleInfo
{
	float HalfWidth = 10.f;
	float HalfHeight = 0.5f;
	float HalfDepth = 1.f;

	float MaxThrusterForce = 200.f;
};

//Configuration of the difficulty
struct Configuration
{
	float DifficultyMultiplyer = 0.8f; //Percentage of difficulty, 1.f = hard mode.
	float StartDelay = 2.f; //The delay before spawing the first object in ms.
	bool PlayMusic = true, PlayingMusic = false; //For determing if music should play, and if its playing
};

//Score struct, holds score

//Framework forward declerations.
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}

/// <summary>
/// Static class containing global variables which are accessed around the game.
/// 
/// This basically substitiutes creating loads of inits or passing around values, making life easier.
/// </summary>
class Game
{
	static gef::InputManager* inputManager;
	static gef::AudioManager* audioManager;
	static Audio3D* audio3D;
	static gef::Renderer3D* renderer3d;
	static gef::SpriteRenderer* spriteRenderer;
	static PrimitiveBuilder* primitiveBuilder;
	static class GameObjectManager* gameObjectManager;
	static b2World* world;
	static AssetManager* assetManager;
	static GameStateManager* gameStateManager;
	
	static gef::Material defaultMaterial;

	static bool isInitialised;

	static PaddleInfo paddleInfo;

	static Configuration configuration;
	static int score;

	static bool shouldExit;
public:
	/// <summary>
	/// Initialise the global game variables.
	/// </summary>
	/// <param name="in"></param>
	/// <param name="au"></param>
	/// <param name="r3d"></param>
	/// <param name="sr"></param>
	/// <param name="pb"></param>
	static void Init(gef::InputManager* in, gef::AudioManager* au, Audio3D* a3d, gef::Renderer3D* r3d, gef::SpriteRenderer* sr, PrimitiveBuilder* pb, GameObjectManager* gom, b2World* w, AssetManager* am, GameStateManager* gsm);
	
	static gef::InputManager* GetInputManager();
	static gef::AudioManager* GetAudioManager();
	static Audio3D* GetAudio3D();
	static gef::Renderer3D* GetRenderer3D();
	static gef::SpriteRenderer* GetSpriteRenderer();
	static PrimitiveBuilder* GetPrimitiveBuilder();
	static GameObjectManager* GetGameObjectManager();
	static b2World* GetB2World();
	static AssetManager* GetAssetManager();
	static GameStateManager* GetGameStateManager();

	static gef::Material GetDefaultMaterial();

	static PaddleInfo& PaddleInfo();
	static Configuration& Configuration();
	static int GetScore();
	static void SetScore(int newScore);


	/// <summary>
	/// Mark the game to exit.
	/// </summary>
	static void Exit();
	
	/// <summary>
	/// Not value of should the game exit. This is only for use inside of the scene app.
	/// </summary>
	static bool NotExit();
private:
	Game();
	~Game();
};

