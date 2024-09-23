#include "Model.h"

Model::Model(std::vector<ModelMesh> _meshes)
{
	meshes = _meshes;

	//i could generate mesh data here by loop through all the meshes
	//for(auto& mesh : meshes)
	//	mesh......
}

void Model::Draw()
{
	for (auto& mesh : meshes)
		mesh.Render();
}

void Model::Draw(Shader& shader)
{
	for (auto& mesh : meshes)
		mesh.NewRender(shader);
}

void Model::DebugWireDraw()
{
	for (auto& mesh : meshes)
		mesh.RenderDebugOutLine();
}

void Model::Destroy()
{
	for (auto& m : meshes)
		m.Clear();

	for (auto& t : textures)
		t.UnRegisterUse();
		
}

