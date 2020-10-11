#include "InGameState.h"

#include <Box2D/Box2D.h>

#include <graphics/colour.h>

#include "Game.h"
#include "GameObject.h"
#include "GameObjectManager.h"

#include "MeshComponent.h"
#include "PhysicsComponent.h"
#include "AudioEmitterComponent.h"
#include "AudioListenerComponent.h"
#include "ThrusterComponent.h"
#include "RevoluteJointComponent.h"
#include "ItemDropperComponent.h"
#include "BoundaryComponent.h"
#include "ScoreTimerComponent.h"
#include "MusicPlayingComponent.h"
#include "GamePauserComponent.h"

#include "Sprite2DComponent.h"
#include "StateChangeButton2DComponent.h"

InGameState::InGameState()
	: GameState(GAME_STATE_ENUM::IN_GAME)
{}


InGameState::~InGameState()
{}

void InGameState::LoadIn()
{
	/*Add player*/
	{
		GameObject* playerObj = Game::GetGameObjectManager()->AddObject(new GameObject());
		playerObj->SetTag(TAG::PLAYER_BALL);
		playerObj->GetTransform().SetPositon({ 0.f, 1.f, 0.f });
		auto tempUserData = playerObj->AddComponent(new MeshComponent(Game::GetAssetManager()->GetMesh("player"), Game::GetDefaultMaterial()));

		//add physics component
		b2BodyDef def;
		def.type = b2_dynamicBody;
		def.position = playerObj->GetTransform().Get2DPosition();
		def.userData = tempUserData;
		b2CircleShape shape;
		shape.m_radius = 0.5f;

		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 2.f;
		fixture.friction = 0.95f;
		fixture.restitution = 0.f;
		playerObj->AddComponent(new PhysicsComponent(def, fixture));
	}

	Transform* paddleTransform;
	//add platform, anchor and motor joint
	{
		//init platform
		auto platformobj = Game::GetGameObjectManager()->AddObject(new GameObject());
		paddleTransform = platformobj->GetTransformPtr();
		gef::Material platformMat;
		platformMat.set_colour(gef::Colour(255, 82, 64).GetABGR());

		platformobj->AddComponent(new MeshComponent(Game::GetAssetManager()->GetMesh("paddle"), platformMat));

		b2BodyDef platPhysDef;
		platPhysDef.type = b2_dynamicBody;
		platPhysDef.position = platformobj->GetTransform().Get2DPosition();

		b2PolygonShape platPhysShape;
		platPhysShape.SetAsBox(Game::PaddleInfo().HalfWidth, Game::PaddleInfo().HalfHeight);

		b2FixtureDef platFixture;
		platFixture.density = 1.f;
		platFixture.shape = &platPhysShape;
		auto platformPhysComp = platformobj->AddComponent(new PhysicsComponent(platPhysDef, platFixture));

		platformobj->AddComponent(new ThrusterComponent(static_cast<PhysicsComponent*>(platformPhysComp)));

		//Init the object it will be adheared to.
		auto baseForPlatObj = Game::GetGameObjectManager()->AddObject(new GameObject());
		baseForPlatObj->GetTransform().Position().set_z(-0.2f);

		baseForPlatObj->AddComponent(new MeshComponent(Game::GetAssetManager()->GetMesh("paddle base"), Game::GetDefaultMaterial()));

		//physics
		b2BodyDef basePlatPhysDef;
		basePlatPhysDef.type = b2_staticBody;
		basePlatPhysDef.position = baseForPlatObj->GetTransform().Get2DPosition();

		b2PolygonShape basePlatPhysShape;
		basePlatPhysShape.SetAsBox(0.1f, 0.1f);

		b2FixtureDef basePlatFixture;
		basePlatFixture.density = 1.5f;
		basePlatFixture.shape = &basePlatPhysShape;
		basePlatFixture.filter.categoryBits = 0b0010; //dont collide with anything

		auto basePlatForPlatPhysComp = baseForPlatObj->AddComponent(new PhysicsComponent(basePlatPhysDef, basePlatFixture));

		//ADD JOINT BETWEEN BASE AND PLATFORM.
		b2RevoluteJointDef revJointDef;
		revJointDef.bodyA = static_cast<PhysicsComponent*>(platformPhysComp)->GetBody();
		revJointDef.bodyB = static_cast<PhysicsComponent*>(basePlatForPlatPhysComp)->GetBody();
		revJointDef.enableMotor = false;
		revJointDef.collideConnected = false;

		platformobj->AddComponent(new RevoluteJointComponent(revJointDef));
	}

	//Add the spawner
	auto spawnerObj = Game::GetGameObjectManager()->AddObject(new GameObject());
	{
		//assetManager->AddMesh(primitive_builder_->CreateBoxMesh({ 0.5f, 0.5f, 0.5f }), "spawner");
		spawnerObj->AddComponent(new MeshComponent(Game::GetAssetManager()->GetMesh("spawner")));
		spawnerObj->GetTransform().SetPositon(gef::Vector4(0.f, 12.5f, 0.f)); //THIS NEEDS TO BE IN THIS ORDER SO THE SPAWNS INITILAISE CORRETLY
		spawnerObj->GetTransform().SetScale(gef::Vector4( 2.f, 2.f, 2.f )); //2ND ITEM
		auto itemDropperComp = spawnerObj->AddComponent(new ItemDropperComponent(spawnerObj->GetTransformPtr(), paddleTransform)); //SEE ABOVE
	}

	//audio listener
	auto listenerObj = Game::GetGameObjectManager()->AddObject(new GameObject());
	listenerObj->GetTransform().SetScale({ 14.f, 14.f, 14.f });
	listenerObj->AddComponent(new AudioListenerComponent()); //convenient place to store the audio listener.)

	{
		//add a score timer
		auto managerObj = Game::GetGameObjectManager()->AddObject(new GameObject());
		auto textComp = managerObj->AddComponent(new Text2DComponent(Game::GetAssetManager()->GetFont("comic sans"), "",
			{ 50.f, 10.f, 0.f }, 1.f, gef::Colour(1.f, 1.f, 1.f)));

		managerObj->AddComponent(new ScoreTimerComponent(static_cast<Text2DComponent*>(textComp)));

		//add a music player
		managerObj->AddComponent(new MusicPlayingComponent(true));
	}


	//boundary object
	{
		auto boundaryObj = Game::GetGameObjectManager()->AddObject(new GameObject());
		boundaryObj->GetTransform().Position().set_y(-10.f);

		auto boundaryComp = boundaryObj->AddComponent(new BoundaryComponent());

		b2BodyDef boundaryBodyDef;
		boundaryBodyDef.type = b2_staticBody;
		boundaryBodyDef.position = boundaryObj->GetTransform().Get2DPosition();
		boundaryBodyDef.angle = boundaryObj->GetTransform().Rotation().z();
		boundaryBodyDef.userData = boundaryComp;

		b2PolygonShape boundaryShapeDef;
		boundaryShapeDef.SetAsBox(200.f, 2.f);

		b2FixtureDef boundaryFixtureDef;
		boundaryFixtureDef.shape = &boundaryShapeDef;
		boundaryFixtureDef.isSensor = true;

		boundaryObj->AddComponent(new PhysicsComponent(boundaryBodyDef, boundaryFixtureDef));
	}

	//pauser component
	{
		auto pauserObj = Game::GetGameObjectManager()->AddObject(new GameObject());
		pauserObj->SetTag(TAG::UPDATE_WHILE_PAUSED);

		/*Pasue Text*/
		std::string pauseText = "Paused...";
		float pauseTextLen = Game::GetAssetManager()->GetFont("comic sans")->GetStringLength(pauseText.data());
		auto pauseTextComp = pauserObj->AddComponent(new Text2DComponent(
			Game::GetAssetManager()->GetFont("comic sans"),
			pauseText,
			gef::Vector4(960.f / 2.f - (pauseTextLen / 2.f), 544.f * (1.f / 10.f), 0.f),
			1.f,
			gef::Colour(1.f, 1.f, 1.f), 
			gef::TextJustification::TJ_LEFT,
			false));

		/*Exit button*/
		auto exitButtonSprite = new gef::Sprite();
		exitButtonSprite->set_texture(Game::GetAssetManager()->GetTexture("exit button"));
		exitButtonSprite->set_width(64.f);
		exitButtonSprite->set_height(64.f);
		exitButtonSprite->set_position(gef::Vector4(10.f + (exitButtonSprite->width()), 544.f - 10.f - exitButtonSprite->height(), 0.f));
		auto exitButtonSpriteComp = pauserObj->AddComponent(new Sprite2DComponent(exitButtonSprite, false));

		auto exitButtonComp = pauserObj->AddComponent(new StateChangeButton2DComponent(
			{ { exitButtonSprite->position().x() - (exitButtonSprite->width() / 2.f), exitButtonSprite->position().y() - (exitButtonSprite->height() / 2.f) },
			{ exitButtonSprite->width(), exitButtonSprite->height() } },
			GAME_STATE_ENUM::MAIN_MENU,
			false));

		/*Unpause Button*/
		auto unpauseButtonSprite = new gef::Sprite();
		unpauseButtonSprite->set_texture(Game::GetAssetManager()->GetTexture("play button"));
		unpauseButtonSprite->set_width(64.f);
		unpauseButtonSprite->set_height(64.f);
		unpauseButtonSprite->set_position(960.f / 2.f, 544.f - 10.f - unpauseButtonSprite->height(), 0.f);

		auto unpauseButtonSpriteComp = pauserObj->AddComponent(new Sprite2DComponent(unpauseButtonSprite, false));

		auto unpauseButtonComp = pauserObj->AddComponent(new StateChangeButton2DComponent({
			{unpauseButtonSprite->position().x() - (unpauseButtonSprite->width() / 2.f), unpauseButtonSprite->position().y() - (unpauseButtonSprite->height() / 2.f)},
			{unpauseButtonSprite->width(), unpauseButtonSprite->height()} },
			GAME_STATE_ENUM::IN_GAME,
			false));

		/*In game pause button*/
		auto inGamePauseSprite = new gef::Sprite();
		inGamePauseSprite->set_texture(Game::GetAssetManager()->GetTexture("pause button"));
		inGamePauseSprite->set_width(64.f);
		inGamePauseSprite->set_height(64.f);
		inGamePauseSprite->set_position(940.f - 10.f - (inGamePauseSprite->width() / 2.f), 10.f + (inGamePauseSprite->height() / 2.f), 0.f);

		auto inGamePauseSpriteComp = pauserObj->AddComponent(new Sprite2DComponent(inGamePauseSprite));

		auto inGamePauseButtonComp = pauserObj->AddComponent(new StateChangeButton2DComponent(
			{ { inGamePauseSprite->position().x() - (inGamePauseSprite->width() / 2.f), inGamePauseSprite->position().y() - (inGamePauseSprite->height() / 2.f)},
			{ inGamePauseSprite->width(), inGamePauseSprite->height() } },
			GAME_STATE_ENUM::PAUSE,
			true));

		pauserObj->AddComponent(
			new GamePauserComponent(static_cast<Text2DComponent*>(pauseTextComp), 
			std::make_pair(static_cast<Sprite2DComponent*>(exitButtonSpriteComp), static_cast<StateChangeButton2DComponent*>(exitButtonComp)),
			std::make_pair(static_cast<Sprite2DComponent*>(inGamePauseSpriteComp), static_cast<StateChangeButton2DComponent*>(inGamePauseButtonComp)),
			std::make_pair(static_cast<Sprite2DComponent*>(unpauseButtonSpriteComp), static_cast<StateChangeButton2DComponent*>(unpauseButtonComp)) ));
	}
}