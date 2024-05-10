#pragma once
#include "Entity.h"
class Toroid :
    public Abs_Entity
{
public:
	Toroid(GLuint r, GLuint R, GLuint m, GLuint p);
	virtual ~Toroid();

	virtual void render(glm::dmat4 const& modelViewMat) const override;
		
};

