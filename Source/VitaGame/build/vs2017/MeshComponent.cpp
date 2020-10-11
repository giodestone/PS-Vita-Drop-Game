#include "MeshComponent.h"

#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <input/sony_controller_input_manager.h>
#include <graphics/mesh.h>
#include <graphics/renderer_3d.h>
#include <system/debug_log.h>
#include <graphics/font.h>

#include "GameObject.h"


MeshComponent::MeshComponent(gef::Mesh* mesh, gef::Material mat)
	: Component(COMPONENT_TAG::MESH),
	mesh(mesh),
	material(mat),
	overrideMaterial(true)
{
	meshInstance.set_mesh(mesh);
}


MeshComponent::MeshComponent(gef::Mesh * meshNoMatOverride)
	: Component(COMPONENT_TAG::MESH),
	mesh(meshNoMatOverride),
	overrideMaterial(false)
{
	meshInstance.set_mesh(meshNoMatOverride);
}

MeshComponent::~MeshComponent()
{}

void MeshComponent::Render(GameObject * caller)
{
	if (overrideMaterial)
	{
		Game::GetRenderer3D()->set_override_material(&material); //change to current material
		Game::GetRenderer3D()->DrawMesh(meshInstance);
		Game::GetRenderer3D()->set_override_material(nullptr);
	}
	else
	{
		Game::GetRenderer3D()->DrawMesh(meshInstance);
	}
}

void MeshComponent::Update(float dt, GameObject * caller)
{
	meshInstance.set_transform(caller->GetTransform().GetMatrix()); //update the mesh transform to be based off of the game object transform.
}
