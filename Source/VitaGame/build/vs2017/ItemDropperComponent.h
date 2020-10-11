#pragma once
#include "Component.h"

#include <vector>
#include <map>
#include <Box2D\Box2D.h>
#include "MeshComponent.h"
#include "Transform.h"
#include <random>

struct ObjectDistribution
{
	std::uniform_real<float> WeightDistribution;
	std::uniform_real<float> SizeDistribution;
	std::uniform_real<float> FrictionDistribution;
	std::uniform_real<float> RestitutionDistribution;

	/// <summary>
	/// For holding the distributions of spawnable objects.
	/// </summary>
	/// <param name="minWeight"></param>
	/// <param name="maxWeight"></param>
	/// <param name="minSize"></param>
	/// <param name="maxSize"></param>
	ObjectDistribution(float minWeight, float maxWeight, float minSize, float maxSize, float frictionMin, float frictionMax, float restitutionMin=0.f, float restitituionMax=0.001f)
		: WeightDistribution(minWeight, maxWeight),
		SizeDistribution(minSize, maxSize),
		FrictionDistribution(frictionMin, frictionMax),
		RestitutionDistribution(restitutionMin, restitituionMax)
	{}

	~ObjectDistribution() {}
};

class ItemDropperComponent :
	public Component
{
	Transform* paddleTransform;
	Transform* ownerTransform;

	std::random_device rd; //Initial random seed.
	std::mt19937 mt; //Random number generation.
	std::uniform_real<float> timeDistribution;
	std::uniform_real<float> throwingForceDistribution;
	std::uniform_real<float> throwingAngularMomentumDistribuiton;
	std::uniform_real<float> positionOnPaddleDistrbution; //pick a position on the paddle based on the local transform
	std::uniform_real<float> newXPosDistribution;
	std::uniform_int<int> nextObjectToSpawn;

	std::map<std::string, GameObject*> objects;

	float nextTimeToSpawn;
	float nextTimeToSpawnPeriod;
	b2Vec2 nextForceDirection; //for storing the directon of the next throw

	gef::Vector4 lerpStartPos, lerpEndPos;
	gef::Vector4 lerpStartRot, lerpEndRot;

	ObjectDistribution bowlingBallDistribution;
	ObjectDistribution plantPotDistribution;
	b2PolygonShape plantPotShape;
	ObjectDistribution bookDistribution;
	b2PolygonShape bookShape;
	ObjectDistribution beachBallDistribution;

	float timeElapsed; //total time elpased since object created.
public:
	/// <summary>
	/// Component for picking, aiming at the paddle, and then spawning them.
	/// </summary>
	/// <param name="ownerTransform">Tranform of the owner component. This is needed due to the order that things are initialised.</param>
	/// <param name="paddleTransform">Transform of the paddle.</param>
	ItemDropperComponent(Transform* ownerTransform, Transform* paddleTransform);
	~ItemDropperComponent();

	/// <summary>
	/// Spawn an object, and pick a new time to spawn it.
	/// </summary>
	/// <param name="dt">Delta time, used for checking when an object should be spawned next.</param>
	/// <param name="caller">Not used.</param>
	void Update(float dt, class GameObject* caller) override;
private:
	/// <summary>
	/// Initialise the collision boxes for objects.
	/// </summary>
	void initialiseObjects();

	/// <summary>
	/// Spawn a ball.
	/// </summary>
	/// <param name="objectDistrib"></param>
	/// <param name="meshAlias"></param>
	/// <param name="linearVelocity"></param>
	/// <param name="angularVelocity"></param>
	/// <returns>The game object of the ball.</returns>
	GameObject* spawnBall(ObjectDistribution* objectDistrib, std::string meshAlias, b2Vec2 linearVelocity, float angularVelocity);
	
	/// <summary>
	/// Spawn an object which isnt a ball/has a custom collision.
	/// </summary>
	/// <param name="objectDistrib"></param>
	/// <param name="meshAlias"></param>
	/// <param name="shape"></param>
	/// <param name="linearVelocity"></param>
	/// <param name="angularVelocity"></param>
	/// <returns>Game object which has the object.</returns>
	GameObject* spawnShape(ObjectDistribution* objectDistrib, std::string meshAlias, b2PolygonShape shape, b2Vec2 linearVelocity, float angularVelocity);
	
	/// <summary>
	/// Applies the spawners position to the object and its mesh. This is to stop objects from popping.
	/// </summary>
	/// <param name="gameObject"></param>
	/// <param name="meshComponent"></param>
	void applySpawnerPositionToObjectAndMesh(GameObject * gameObject, MeshComponent* meshComponent);

	/// <summary>
	/// Play a spawn sound.
	/// </summary>
	void playSpawnSound();

	/// <summary>
	/// Pick a new object to spawn and spawn it and apply any other parameters.
	/// </summary>
	void pickAndSpawnNewObject();
};

