#pragma once
#include "Entity.h"
class Toroid :
    public Abs_Entity
{
public:
	Toroid(GLuint r, GLuint R, GLuint p, GLuint m);
	virtual ~Toroid();

	virtual void render(glm::dmat4 const& modelViewMat) const override;
		
};

