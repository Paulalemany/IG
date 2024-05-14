#pragma once
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Entity.h"

class Material_
{
protected:
	// Coeficientes de reflexión
	glm::fvec4 ambient = { 0.2 , 0.2 , 0.2 , 1.0 };
	glm::fvec4 diffuse = { 0.8 , 0.8 , 0.8 , 1.0 };
	glm::fvec4 specular = { 0.0 , 0.0 , 0.0 , 1.0 };

	GLfloat expF = 0; // Exponente para la reflexión especular
	GLuint face = GL_FRONT_AND_BACK;
	GLuint sh = GL_SMOOTH; // Tipo de matizado

public:
	Material_() {};
	virtual ~Material_() {};
	virtual void upload();
	void setCopper();
};

class EntityWithMaterial : public Abs_Entity {

public:
	EntityWithMaterial() : Abs_Entity() { };
	virtual ~EntityWithMaterial() { };
	void setMaterial(Material_* matl) { material = matl; };

protected:
	Material_* material = nullptr;
};


