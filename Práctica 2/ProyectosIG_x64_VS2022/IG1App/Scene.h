#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"

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

	//Le pasamos como parámetro el nombre de la textura
	void setTexture(std::string textura, Texture* t, GLuint a)const { t->load(textura, a); }

protected:
	void free();
	void setGL();
	void resetGL();

	int mId;
	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures; // Textures of the scene

};

#endif //_H_Scene_H_
