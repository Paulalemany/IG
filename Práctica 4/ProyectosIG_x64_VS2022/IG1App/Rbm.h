#pragma once
#include "Entity.h"
#include "EntityWithMaterial.h"

class RbmSphere : public EntityWithMaterial {
public:

	RbmSphere(GLdouble r, GLint p, GLint m, int g);
	~RbmSphere() { delete Abs_Entity::mMesh; }
	virtual void render(glm::dmat4 const& modelViewMat) const override;
	virtual void update() override {};

protected:
	glm::dvec3* perfil;

};

class RbmToroid : public Abs_Entity {
public:

	RbmToroid(GLuint r, GLuint R, GLuint m, GLuint p, int g);
	~RbmToroid() { delete mMesh; delete[] perfil; }
	virtual void render(glm::dmat4 const& modelViewMat) const override;
	virtual void update() override {};

protected:
	glm::dvec3* perfil;

};

