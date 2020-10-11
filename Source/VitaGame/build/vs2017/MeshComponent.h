#pragma once
#include "Component.h"

#include <gef.h>
#include <graphics\mesh_instance.h>
#include <graphics\mesh_instance.h>
#include <graphics\material.h>

#include "Transform.h"

class MeshComponent :
	public Component
{
	gef::MeshInstance meshInstance;
	gef::Mesh* mesh;
	gef::Material material;
	bool overrideMaterial;

public:
	/// <summary>
	/// Component responsible for holding and drawing a mesh.
	/// Constructor for material override.
	/// </summary>
	/// <param name="mesh">Pointer to the mest.</param>
	/// <param name="mat">The material that will override any ones that a mesh will contain.</param>
	MeshComponent(gef::Mesh* mesh, gef::Material mat);

	/// <summary>
	/// Component responsible for holding and drawing a mesh.
	/// </summary>
	/// <param name="meshNoMatOverride">Pointer to mesh which will not be overriden</param>
	MeshComponent(gef::Mesh* meshNoMatOverride);
	~MeshComponent();

	/// <summary>
	/// Renders the mesh.
	/// </summary>
	/// <param name="caller"></param>
	void Render(class GameObject* caller) override;

	/// <summary>
	/// Updates the transform of the mesh intance.
	/// </summary>
	/// <param name="dt"></param>
	/// <param name="caller">From who to update the positon from.</param>
	/// <remarks>Performance intensive.</remarks>
	void Update(float dt, class GameObject* caller) override;

	/// <summary>
	/// Get the mesh instance.
	/// </summary>
	/// <returns>Mesh instance.</returns>
	inline gef::MeshInstance& MeshInstance() { return meshInstance; }
};

