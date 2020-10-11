#include "ThrusterComponent.h"

#include "GameObject.h"
#include "Game.h"
#include <input/input_manager.h>
#include <input/sony_controller_input_manager.h>
#include <graphics/renderer_3d.h>
#include <graphics/mesh.h>
#include <graphics/mesh_instance.h>
#include <math.h>
#include <maths/math_utils.h>

ThrusterComponent::ThrusterComponent(PhysicsComponent* paddle)
	: Component(COMPONENT_TAG::THRUSTER),
	paddle(paddle)
{}


ThrusterComponent::~ThrusterComponent()
{}

void ThrusterComponent::Update(float dt, GameObject * caller)
{
	const gef::SonyController* controller = Game::GetInputManager()->controller_input()->GetController(0);

	b2Body* paddleBody = paddle->GetBody();

	//calculate a unit vector of the direction of the force at 90 degrees as the thruster should be pointing up and down depeding on the paddle.
	b2Vec2 forceDirection = { std::cosf(paddleBody->GetAngle() - gef::DegToRad(90.f)), std::sinf(paddleBody->GetAngle()  - gef::DegToRad(90.f)) };

	//multiply the force unit vector with the input and max force, yielding unit vector with the percentage of the force in the specific directions.
	b2Vec2 forceWithMaxForceLeft = { 
		(forceDirection.x) * (controller->left_stick_y_axis() * Game::PaddleInfo().MaxThrusterForce), 
		(forceDirection.y) * (controller->left_stick_y_axis() * Game::PaddleInfo().MaxThrusterForce) };
	b2Vec2 forceWithMaxForceRight = { 
		(forceDirection.x) * (controller->right_stick_y_axis() * Game::PaddleInfo().MaxThrusterForce),
		(forceDirection.y) * (controller->right_stick_y_axis() * Game::PaddleInfo().MaxThrusterForce) };

	//now apply the force.
	paddle->GetBody()->ApplyForce(forceWithMaxForceLeft, paddleBody->GetWorldPoint({ -Game::PaddleInfo().HalfWidth + 1.f, 0.f }), true); //left paddle
	paddle->GetBody()->ApplyForce(forceWithMaxForceRight, paddleBody->GetWorldPoint({ Game::PaddleInfo().HalfWidth - 1.f, 0.f }), true); //right paddle
}
