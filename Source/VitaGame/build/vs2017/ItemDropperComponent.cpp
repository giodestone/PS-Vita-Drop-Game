#include "ItemDropperComponent.h"

#include "GameObject.h"

#include "MeshComponent.h"
#include "PhysicsComponent.h"

#include "GameObjectManager.h"

#include <Box2D\Collision\Shapes\b2CircleShape.h>

#include "maths/math_utils.h"

#include "GameObject.h"

#include <graphics/colour.h>

#include "AudioEmitterComponent.h"


#include <system/debug_log.h>

ItemDropperComponent::ItemDropperComponent(Transform* ownerTransform, Transform* paddleTransform)
	: Component(COMPONENT_TAG::ITEM_DROPPER),
	paddleTransform(paddleTransform),
	ownerTransform(ownerTransform),

	mt(rd()),
	timeDistribution(0.25f + (0.45f * std::fabsf(Game::Configuration().DifficultyMultiplyer - 1.f)), 1.25f + (1.25f * std::fabsf(Game::Configuration().DifficultyMultiplyer - 1.f))), //min 20ms because thats how long the sound takes to play, add 20% if on medium
	throwingForceDistribution(0.5f, 22.f * Game::Configuration().DifficultyMultiplyer),
	throwingAngularMomentumDistribuiton(-20.f, 20.f), //in radians
	positionOnPaddleDistrbution(-Game::PaddleInfo().HalfWidth, Game::PaddleInfo().HalfWidth), //put into radians
	newXPosDistribution(-10.f, 10.f),
	nextObjectToSpawn(0, 3),

	nextForceDirection(0.f, 0.f),

	//lerpStartPos(ownerTransform->Position()),
	//lerpEndPos(ownerTransform->Position()),
	//lerpStartRot(ownerTransform->Rotation()),
	//lerpEndRot(ownerTransform->Rotation()),

	bowlingBallDistribution(2.f* Game::Configuration().DifficultyMultiplyer, 10.f* Game::Configuration().DifficultyMultiplyer, 0.2f, 1.f, 0.85f, 0.9f, 0.05f, 0.06f),
	plantPotDistribution(0.8f* Game::Configuration().DifficultyMultiplyer, 1.5f* Game::Configuration().DifficultyMultiplyer, 1.f, 1.f, 0.9f, 0.95f),
	bookDistribution(0.5f, 3.f* Game::Configuration().DifficultyMultiplyer, 1.f, 1.f, 0.7f, 0.8f),
	beachBallDistribution(0.2f, 0.6f, 0.8f, 1.8f, 0.7f, 1.f, 0.5f, 0.7f),
	
	timeElapsed(0.f)
{
	initialiseObjects();
	nextTimeToSpawn = Game::Configuration().StartDelay; //this error is a lie.
	nextTimeToSpawnPeriod = Game::Configuration().StartDelay;

	lerpStartPos = ownerTransform->Position();
	lerpEndPos = ownerTransform->Position();
	lerpStartRot = ownerTransform->Rotation();
	lerpEndRot = ownerTransform->Rotation();

}


ItemDropperComponent::~ItemDropperComponent()
{}

void ItemDropperComponent::Update(float dt, GameObject * caller)
{
	timeElapsed += dt;

	if (timeElapsed >= nextTimeToSpawn)
	{
		pickAndSpawnNewObject();

		playSpawnSound();

		//pick a new time to spawn
		nextTimeToSpawnPeriod = timeDistribution(mt);
		nextTimeToSpawn = timeElapsed + nextTimeToSpawnPeriod; //as is this error.
	}
	
	//if position is not where it is curerntly lerp to it

	//convert time elapsed into a percentage.
	float currentPeriod = std::fabsf(timeElapsed - nextTimeToSpawn) / nextTimeToSpawnPeriod;
	
	//Lerp
	auto curx = ownerTransform->Position().x();

	gef::Vector4 currentPos = ownerTransform->Position();
	currentPos.Lerp(lerpEndPos, lerpStartPos, currentPeriod);
	ownerTransform->SetPositon(currentPos);

	gef::Vector4 currentRot = ownerTransform->Position();
	currentRot.Lerp(lerpEndRot, lerpStartRot, currentPeriod);
	ownerTransform->SetRotation(currentRot);

}

void ItemDropperComponent::playSpawnSound()
{
	//play a sound when spawned.
	auto audioEmitter = new AudioEmitter();
	Game::GetAudio3D()->AddEmitter(audioEmitter);
	audioEmitter->Init(Game::GetAssetManager()->GetAudioSample("spawn"), false);
	audioEmitter->set_radius(2.f);
	GetOwner()->AddComponent(new AudioEmitterComponent(audioEmitter));
}

void ItemDropperComponent::pickAndSpawnNewObject()
{
	//pick a new position of the spawner (and orgin of object)
	float newXPosOfSpawner = positionOnPaddleDistrbution(mt);
	//pick new lookat of the spawner (where it will aim towards)
	float newXLookAtOnPaddle = positionOnPaddleDistrbution(mt);
	while (newXLookAtOnPaddle == newXPosOfSpawner) //as unlikely as this is avoid duplicates
		newXLookAtOnPaddle = positionOnPaddleDistrbution(mt);

	//calculate distance between spawner and paddle y
	float distY = paddleTransform->Position().y() - ownerTransform->Position().y(); //a

																					//calculate distance between lookat x and spawner x
	float distX = newXLookAtOnPaddle - newXPosOfSpawner; //o

														 //now SOH CAH (TOA) it to get the angle it should fire out at
	float newAngle; //o/a
	if (distX >= 0) //if distance is positive then firing to right
		newAngle = std::atanf((std::fabsf(distX) / std::fabsf(distY)));
	else //otherwise firing to right (aka negative angle)
		newAngle = -std::atanf((std::fabsf(distX) / std::fabsf(distY)));

	//Apply it to lerp
	lerpStartRot = lerpEndRot;
	lerpEndRot.set_z(newAngle);

	//Apply the new positon to lerp
	lerpStartPos.set_x(lerpEndPos.x()); //start where we left off
	lerpEndPos.set_x(newXPosOfSpawner);

	//pick a new starting anglular momentum
	float angularMomentumAtSpawn = throwingAngularMomentumDistribuiton(mt);

	//pick a new starting force remember to multiply it by between an angle of 210 to 310
	float totalForce = throwingForceDistribution(mt);
	float currentRotation = lerpStartRot.z();
	b2Vec2 forceDirection = nextForceDirection; //the values calulcated that will be needed for this are always ahead.
	forceDirection.Normalize();
	b2Vec2 forceDirectionAtSpawn = { forceDirection.x * totalForce, forceDirection.y * totalForce };

	nextForceDirection = { distX, distY };

	//spawn the object
	switch (nextObjectToSpawn(mt)) //pick a new thing to spawn.
	{
	case 0:
		Game::GetGameObjectManager()->AddObject(spawnBall(&bowlingBallDistribution, "bowling ball", forceDirectionAtSpawn, angularMomentumAtSpawn));
		break;
	case 1:
		Game::GetGameObjectManager()->AddObject(spawnBall(&beachBallDistribution, "beach ball", forceDirectionAtSpawn, angularMomentumAtSpawn));
		break;
	case 2:
		Game::GetGameObjectManager()->AddObject(spawnShape(&plantPotDistribution, "plant pot", plantPotShape, forceDirectionAtSpawn, angularMomentumAtSpawn));
		break;
	case 3:
		Game::GetGameObjectManager()->AddObject(spawnShape(&bookDistribution, "book", bookShape, forceDirectionAtSpawn, angularMomentumAtSpawn));
		break;

	}
}

void ItemDropperComponent::initialiseObjects()
{
	/*Bowling ball*/
	{
		
	}
	/*Plant pot*/
	{
		b2Vec2 shape[] = { 
		{-0.71f*2.f, 0.575f*2.f },
		{-0.71f*2.f, 0.34f*2.f },
		{-0.5f*2.f, -0.6f*2.f },
		{0.5f*2.f, -0.6f*2.f },
		{0.71f*2.f, 0.34f*2.f },
		{0.71f*2.f, 0.575f*2.f }
		};
		plantPotShape.Set(shape, 6);

	}
	/*Book*/
	{
		bookShape.SetAsBox(1.f, 0.15f);
	}
	/*Beach ball*/
	{
	}
	
}

GameObject* ItemDropperComponent::spawnBall(ObjectDistribution* objectDistrib, std::string meshAlias, b2Vec2 linearVelocity, float angularVelocity)
{
	auto ballObj = new GameObject();
	ballObj->SetTag(TAG::SPAWNED_OBJECT);
	float radius = objectDistrib->SizeDistribution(mt);

	ballObj->GetTransform().SetScale(gef::Vector4( radius, radius, radius )); //set the scale accordingly to the size of the object

	auto mesh = ballObj->AddComponent(new MeshComponent(Game::GetAssetManager()->GetMesh(meshAlias)) );
	
	applySpawnerPositionToObjectAndMesh(ballObj, static_cast<MeshComponent*>(mesh));

	//physics
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = ownerTransform->Get2DPosition();
	bodyDef.angle = ownerTransform->Rotation().z();
	bodyDef.linearVelocity = linearVelocity;
	bodyDef.angularVelocity = angularVelocity;
	bodyDef.userData = mesh; //no collision response.

	b2CircleShape shape;
	shape.m_radius = radius;

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = objectDistrib->WeightDistribution(mt);
	fixture.friction = objectDistrib->FrictionDistribution(mt);
	fixture.restitution = objectDistrib->RestitutionDistribution(mt);

	auto physicsComponent = static_cast<PhysicsComponent*>(ballObj->AddComponent(new PhysicsComponent(bodyDef, fixture)));
	return ballObj;
}

GameObject * ItemDropperComponent::spawnShape(ObjectDistribution * objectDistrib, std::string meshAlias, b2PolygonShape shape, b2Vec2 linearVelocity, float angularVelocity)
{
	auto shapeObj = new GameObject();
	shapeObj->SetTag(TAG::SPAWNED_OBJECT);
	auto mesh = static_cast<MeshComponent*>(shapeObj->AddComponent(new MeshComponent(Game::GetAssetManager()->GetMesh(meshAlias))));

	applySpawnerPositionToObjectAndMesh(shapeObj, mesh);

	//physics
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = ownerTransform->Get2DPosition();
	bodyDef.angle = ownerTransform->Rotation().z();
	bodyDef.linearVelocity = linearVelocity;
	bodyDef.angularVelocity = angularVelocity;
	bodyDef.userData = mesh; //no collision response

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = objectDistrib->WeightDistribution(mt);
	fixture.friction = objectDistrib->FrictionDistribution(mt);
	fixture.restitution = objectDistrib->RestitutionDistribution(mt);

	auto physicsComponent = static_cast<PhysicsComponent*>(shapeObj->AddComponent(new PhysicsComponent(bodyDef, fixture)));
	return shapeObj;
}

void ItemDropperComponent::applySpawnerPositionToObjectAndMesh(GameObject * gameObject, MeshComponent* meshComponent)
{
	gameObject->GetTransformPtr()->SetPositon(ownerTransform->Position()); //set position to the spawner

	gameObject->GetTransformPtr()->Update(0.f, gameObject);

	meshComponent->Update(0.f, meshComponent->GetOwner());
}