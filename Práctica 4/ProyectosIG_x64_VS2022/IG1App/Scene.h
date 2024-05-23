#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "QuadricEntity.h"
#include "CompoundEntity.h"
#include "Rbm.h"
#include "Light.h"

#include <vector>

class Scene
{
public:
	Scene() = default;
	~Scene()
	{
		free();
		resetGL();
	};

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	void init();

	void render(Camera const& cam) const;

	void update();

	void addObject(Abs_Entity* e);

	void setScene(int i);

	void deleteObjects();

	//apt68
	void orbit(float time);
	void rotate(float time);

	//luces
	void setLights();

	//apt76
	void switchDirLight(bool s) {
		if (s) { dirLight->enable(); }
		else { dirLight->disable(); }
	}

	//apt77
	void switchPosLight(bool s) {
		if (s) { posLight->enable(); }
		else { posLight->disable(); }
	}

protected:
	void free();
	void setGL();
	void resetGL();
	//Apt 56
	void sceneDirLight(Camera const& cam) const;

	int mId;
	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures; // Textures of the scene

	//apt68
	float speed;
	GLdouble rotY = 0;
	GLdouble rotZ = 0;
	glm::dvec3 frontDir = glm::dvec3(1, 0, 0);


	//M�todo del Nodo ficticio
	CompoundEntity* inventedNode;
	CompoundEntity* inventedNodeRotate;
	CompoundEntity* TIE;

	//Luces
	DirLight* dirLight;
	PosLight* posLight;

};

#endif //_H_Scene_H_
