#pragma once
#include <graphics/mesh_instance.h>
#include <audio/audio_manager.h>
#include <map>
#include <graphics/scene.h>
#include <graphics/mesh.h>
#include <graphics/font.h>

#include <assets/png_loader.h>
class AssetManager
{
	std::map<std::string, int> audioSamples;
	
	std::map<std::string, gef::Scene*> scenes;
	std::map<std::string, gef::Mesh*> meshes;
	std::map<std::string, bool> isMeshInScene; //for later deletion of meshes

	std::map<std::string, gef::Font*> fonts;
	
	std::map<std::string, gef::Texture*> textures;

	gef::Platform* platform;
	gef::PNGLoader pngLoader;
	gef::AudioManager* audioManager;

public:
	/// <summary>
	/// For managing meshes and sound assets. Handles loading, deleting and retreiving.
	/// 
	/// This is basically a wrapper around a map for all game assets.
	/// </summary>
	/// <param name="platform"></param>
	AssetManager(gef::Platform* platform, gef::AudioManager* am);
	~AssetManager();

	/// <summary>
	/// Load an audio sample and associate it with an alias.
	/// </summary>
	/// <param name="path">A full path (with file extension) to where the file is located.</param>
	/// <param name="alias">The phase that will be used to retrieve it later.</param>
	/// <returns>The audio id of the sample loaded.</returns>
	int LoadAudioSample(std::string path, std::string alias);

	/// <summary>
	/// Load musi. Only one sample can be loaded.
	/// </summary>
	/// <param name="path">The full path (with file extension to where the file is located).</param>
	/// <remarks>Later, unloading is called by the asset manager, but if you load any files in you need to do the stuff to unload/load.</remarks>
	void LoadMusic(const char* path);

	/// <summary>
	/// Loads a mesh (and relevant scene) into memory, for retrival later.
	/// </summary>
	/// <param name="path">Path of asset.</param>
	/// <param name="alias">The phase that will be used to retrieve it later.</param>
	void LoadMesh(std::string path, std::string alias);

	/// <summary>
	/// Loads a font into memory, for retrival via alias later.
	/// </summary>
	/// <param name="path">Path of font.</param>
	/// <param name="alias">The phase that will be used to retrieve it later.</param>
	void LoadFont(std::string path, std::string alias);

	/// <summary>
	/// Load a texture into memory, for later retirval via alias.
	/// </summary>
	/// <param name="path">Path to file,</param>
	/// <param name="alias">Phase that will be used to retrieve it.</param>
	void LoadTexture(std::string path, std::string alias);

	/// <summary>
	/// Add a mesh which can be later referenced by ans alias.
	/// </summary>
	/// <param name="mesh"></param>
	/// <param name="alias"></param>
	void AddMesh(gef::Mesh* mesh, std::string alias);

	/// <summary>
	/// Get a mesh by alias.
	/// </summary>
	/// <param name="alias"></param>
	/// <returns>The mesh.</returns>
	/// <remarks>Throws exception if fails.</remarks>
	gef::Mesh* GetMesh(std::string alias);

	/// <summary>
	/// Get a font by alias.
	/// </summary>
	/// <param name="alias"></param>
	/// <returns>The font.</returns>
	gef::Font* GetFont(std::string alias);

	/// <summary>
	/// Get a texture by alias.
	/// </summary>
	/// <param name="alias"></param>
	/// <returns>The texture.</returns>
	gef::Texture* GetTexture(std::string alias);

	/// <summary>
	/// Get an audio sample by alias.
	/// </summary>
	/// <param name="alias"></param>
	/// <returns>The ID of the sample.</returns>
	int GetAudioSample(std::string alias);
private:
	gef::Scene* LoadSceneAssets(gef::Platform& platform, const char* filename);
	gef::Mesh* GetMeshFromSceneAssets(gef::Scene* scene);
};

