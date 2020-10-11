#include "scene_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <graphics/mesh.h>
#include <maths/math_utils.h>
#include <input/sony_controller_input_manager.h>
#include <input/input_manager.h>
#include <input/touch_input_manager.h>
#include <string>

SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	renderer_3d_(NULL),
	primitive_builder_(NULL),
	input_manager_(NULL),
	audio_manager_(nullptr),
	audio_3d_(NULL),
	asset_manager_(nullptr),
	game_state_manager_(nullptr),
	game_object_manager_(nullptr),
	world_(nullptr)
{
}

void SceneApp::Init()
{
	// initialise audio manager
	audio_manager_ = gef::AudioManager::Create();

	// initialise input manager
	input_manager_ = gef::InputManager::Create(platform_);

	//enable touchscreen
	if (input_manager_ != nullptr && input_manager_->touch_manager() && (input_manager_->touch_manager()->max_num_panels() > 0))
		input_manager_->touch_manager()->EnablePanel(0);

	//initialise sprite renderer
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	// create the renderer for draw 3D geometry
	renderer_3d_ = gef::Renderer3D::Create(platform_);

	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(platform_);


	//initailise asset manager
	asset_manager_ = new AssetManager(&platform_, audio_manager_);

	//initialise game object manager
	game_object_manager_ = new GameObjectManager();

	//create game state manager
	game_state_manager_ = new GameStateManager(); 


	// create 3d audio system
	audio_3d_ = new Audio3D(audio_manager_);

	//initialise worlds
	world_ = new b2World({ 0.f, -9.8f });

	gef::DebugOut("Size: %i", sizeof(audio_manager_));

	// Initilaise Game Variables
	Game::Init(input_manager_, audio_manager_, audio_3d_, renderer_3d_, sprite_renderer_, primitive_builder_, game_object_manager_, world_, asset_manager_, game_state_manager_);

	game_state_manager_->Init(); //now initialise after game variables have been created.

	SetupLights();
}

void SceneApp::CleanUp()
{
	delete game_object_manager_;
	game_object_manager_ = nullptr;

	delete asset_manager_;
	asset_manager_ = nullptr;

	delete world_;
	world_ = nullptr;

	delete audio_3d_;
	audio_3d_ = NULL;

	delete audio_manager_;
	audio_manager_ = NULL;

	delete input_manager_;
	input_manager_ = NULL;

	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	delete game_state_manager_;
	game_state_manager_ = nullptr;

	/*MAYBE ITS THE SCORE! HAD ISSUES WITH IT BEFORE! CHANGE SCORE COMPONENT! AND STRUCTS URGH! NEXT GET RID OF THAT BOOL IN THE TICK BOX*/

}

bool SceneApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	input_manager_->Update();

	// update 3d audio system
	audio_3d_->Update();

	//update world, only if not paused
	if (!Game::GetGameStateManager()->IsPaused())
		world_->Step(1.f / 60.f, 6, 2); //first is tied to FPS (assumed 60), second is amount of velocity iteraitons and third is position iteraitons

	//update game state manager
	game_state_manager_->Update();

	//update game object
	game_object_manager_->Update(frame_time);

	return Game::NotExit();
}

void SceneApp::Render()
{
	// setup camera

	// projection
	float fov = gef::DegToRad(45.0f);
	float aspect_ratio = (float)platform_.width() / (float)platform_.height();
	gef::Matrix44 projection_matrix;
	projection_matrix = platform_.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);
	renderer_3d_->set_projection_matrix(projection_matrix);

	// view
	gef::Vector4 camera_eye(0.5f, 5.0f, 25.0f);
	gef::Vector4 camera_lookat(0.0f, 4.0f, 0.0f);
	gef::Vector4 camera_up(0.0f, 1.0f, 0.0f);
	gef::Matrix44 view_matrix;
	view_matrix.LookAt(camera_eye, camera_lookat, camera_up);
	renderer_3d_->set_view_matrix(view_matrix);

	// draw 3d geometry
	renderer_3d_->Begin();

	game_object_manager_->Render();

	renderer_3d_->End();

	// start drawing sprites, but don't clear the frame buffer
	sprite_renderer_->Begin(false);
	game_object_manager_->Render2D();

	if (DEBUG)
		Game::GetAssetManager()->GetFont("comic sans")->RenderText(sprite_renderer_, gef::Vector4(650.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);

	sprite_renderer_->End();
}

//void SceneApp::InitFont()
//{
//	font_ = new gef::Font(platform_);
//	font_->Load("comic_sans");
//}
//
//void SceneApp::CleanUpFont()
//{
//	delete font_;
//	font_ = NULL;
//}
//
//void SceneApp::DrawHUD()
//{
//	if(font_)
//	{
//		if (DEBUG)
//		{
//			// display frame rate
//			font_->RenderText(sprite_renderer_, gef::Vector4(650.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f, LY: %.2f, RY: %.2f", fps_, left_y_, right_y_);
//		}
//	}
//}

void SceneApp::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}