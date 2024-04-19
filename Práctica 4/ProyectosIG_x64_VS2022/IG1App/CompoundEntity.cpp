#include "CompoundEntity.h"

void CompoundEntity::addEntity(Abs_Entity* ae)
{
	gObjects.push_back(ae);
}


AdvancedTIE::AdvancedTIE()
{
	//Se crean los objetos que lo componen aquí
	body = new Sphere(100.0);
	body->QuadricColor(0.1, 0.2, 0.5);
	addEntity(body);						//Cuerpo del TIE
}

void AdvancedTIE::render(glm::dmat4 const& modelViewMat) const
{
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	//Se llama al render de todos los elementos
	for (auto& elems : gObjects)
	{
		elems->render(modelViewMat);
	}
}

WingAdvancedTIE::WingAdvancedTIE()
{

}

void WingAdvancedTIE::render(glm::dmat4 const& modelViewMat) const
{

}
