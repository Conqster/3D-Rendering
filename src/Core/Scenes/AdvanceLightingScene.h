#pragma once
#include "Scene.h"

#include "SceneGraph/ModelLoader.h"
#include "SceneGraph/Model.h"

#include "Graphics/Shader.h"
#include "Graphics/ObjectBuffer/UniformBuffer.h"

#include "Graphics/Meshes/SphereMesh.h"
#include "Graphics/Meshes/SquareMesh.h"
#include "Graphics/Meshes/CubeMesh.h"

#include "Graphics/Lights/NewLights.h"
#include "Util/Constants.h"

#include "Graphics/ObjectBuffer/ShadowMap.h"

#include "Geometry/AABB.h"


class AdvanceLightingScene : public Scene
{
public:
	AdvanceLightingScene() = default;

	virtual void SetWindow(Window* window);
	inline Camera* const GetCamera() const { return m_Camera; }

	virtual void OnInit(Window* window) override;
	virtual void OnUpdate(float delta_time) override;
	virtual void OnRender() override;
	virtual void OnRenderUI() override;

	virtual void OnDestroy() override;
private:
	void CreateObjects();
	void DrawObjects(Shader& shader);
	void LightPass(Shader& shader);
	void InstanceObjectPass(Shader* shader = nullptr);
	void ShadowPass();


	////////////////
	// Utilities 
	////////////////
	ModelLoader modelLoader;
	UniformBuffer m_CameraMatUBO;
	bool doGammaCorrection = false;
	float gamma = 2.2f;
	LearnVertex m_Quad;

	/////////////////
	//Debugging datas
	/////////////////
	float normDebugLength = 0.0f; // 0.03f;
	glm::vec3 normDebugColour = glm::vec3(1.0f, 0.0f, 1.0f);
	bool useDebugColour = true;
	bool debugLightPos = true;
	bool debugScene = false;
	//bool debugWcModelSpace = false;
	bool debugVertexPosColour = false;
	bool disableTexture = true;
	bool useBlinnPhong = true;
	enum DebugModelType : int
	{
		MODEL_SPACE,
		NORMAL,
		MODEL_NORMAL,
		MODEL_ABS_NORMAL,
		MODEL_COLOUR,
		DEFAULT_COLOUR
	}debugModelType;

	//////////////
	// Objects
	//////////////
	//sphere
	SphereMesh sphere;
	//glm::vec3 spherePos = glm::vec3(0.0f);
	//float sphereScale = 1.0f;
#define MAX_SPHERE 5
	glm::vec3 spheresPos[MAX_SPHERE];
	float spheresScale[MAX_SPHERE];
	bool debugSphereAABB = false;
#define MAX_SPHERE_INSTANCE 100
	std::vector<glm::vec3> sphereInstancePos = std::vector<glm::vec3>();
#define MAX_CUBE 5 //current max cube = 5
	glm::vec3 cubesPos[MAX_CUBE]; 
	float cubesScale[MAX_CUBE]; 
	bool debugCubeAABB = false;
	//ground
	SquareMesh ground;
	glm::vec3 groundPos = glm::vec3();
	float groundScale = 50.0f;
	//cube 
	CubeMesh cube;
	//model1 (stanford-bunny)
	std::shared_ptr<Model> model_1;
	//glm::vec3 model_1Pos = glm::vec3(0.0f);
	//float model_1Scale = 20.0f;
#define MAX_BUNNY_MODEL 5
	glm::vec3 bunnysPos[MAX_BUNNY_MODEL];
	float bunnysScale[MAX_BUNNY_MODEL];
	bool debugBunnyAABB = false;
	glm::vec3 centerOffset;
	float scaleBunnyBy = 1.0f;
	//model2 (unknown) 
	std::shared_ptr<Model> model_2;
	glm::vec3 model_2Pos = glm::vec3(20.0f, 1.5f, 10.0f);
	float model_2Scale = 1.0f;
	bool debugModel2AABB = false;
	glm::vec3 model2AABBCenterOffset;
	float model2AABBScale = 1.0f;

	///////////////
	// Shaders
	///////////////
	Shader modelShader;
	Shader debugShader;
	Shader instancingShader;
	Shader screenShader;

	//////Textures
	Texture* brickTex;
	Texture* plainTex;
	Texture* manchesterTex;


	///////////////////////
	// Lights
	///////////////////////
	//NewPointLight pointLights[Shader_Constants::MAX_POINT_LIGHTS];
	const static int MAX_LIGHT = 5;
	struct PointLightObject
	{
		glm::vec3 objectPosition;
		float childLightOffset = 0.0f;
		float moveSpeed = 0.0f;
		NewPointLight light;
	}lightObject[MAX_LIGHT];
	//NewPointLight pointLights[MAX_LIGHT];
	//glm::vec3 pointLocalWorldPosition[MAX_LIGHT]; //probably change later to local relative to parent
	int availablePtLightCount = 0;
	int specShinness = 64;

	
	NewDirectionalLight dirlight;
	struct DirShadowMap
	{
		glm::mat4 lightProj;
		glm::mat4 lightView;
		glm::mat4 lightSpaceMatrix;
		ShadowMap map;
		Shader debugShader;
	}dirShadowMap;


	struct ShadowInfo
	{
		float cam_near = 0.1f;
		float cam_far = 20.0f;
		float cam_size = 50.0f;
		float dirLight_offset = 5.0f;
		glm::vec3 sample_center_pos = glm::vec3(0.0f);
	}shadowCameraInfo;

	float fov = 45.0f;

	struct PlayerTest
	{
		AABB aabb = AABB(2.0f);
		float speed = 2.0f;
		float debugThick = 2.0f;
		float shadowOffset = 5.0f;
	}playerTest;

};
