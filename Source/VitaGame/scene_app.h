#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <audio/audio_manager.h>
#include <input/input_manager.h>
#include <box2d/Box2D.h>
#include "audio_3d.h"

#include "Game.h"
#include "GameObject.h"

#include "GameObjectManager.h"

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}

class SceneApp : public gef::Application
{
	static constexpr bool DEBUG = false;
public:
	SceneApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:
	void SetupLights();

	//Game Varialbles
	gef::SpriteRenderer* sprite_renderer_;
	gef::Renderer3D* renderer_3d_;

	PrimitiveBuilder* primitive_builder_;
	gef::InputManager* input_manager_;
	gef::AudioManager* audio_manager_;

	GameObjectManager* game_object_manager_;
	AssetManager* asset_manager_;
	GameStateManager* game_state_manager_;

	b2World* world_;

	Audio3D* audio_3d_;

	float fps_;
};

#endif // _SCENE_APP_H
