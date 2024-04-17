#include "CompoundEntity.h"

void CompoundEntity::addEntity(Abs_Entity* ae)
{
}

void CompoundEntity::render(glm::dmat4 const& modelViewMat) const
{
	for (auto& elems : gObjects) 
	{
		elems->render(modelViewMat);
	}
}
