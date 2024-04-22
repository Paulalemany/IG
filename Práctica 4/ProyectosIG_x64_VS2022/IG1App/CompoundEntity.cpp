#include "CompoundEntity.h"
#include <glm/gtc/matrix_transform.hpp>

void CompoundEntity::addEntity(Abs_Entity* ae)
{
	gObjects.push_back(ae);
}


AdvancedTIE::AdvancedTIE()
{
	//Se crean los objetos que lo componen aquí
	//body = new Sphere(100.0);
	//body->QuadricColor(0.1, 0.2, 0.5);
	//addEntity(body);						//Cuerpo del TIE

	wings = new WingAdvancedTIE();
	addEntity(wings);						//Alas del TIE
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
	t = new Texture();
	wings1->setTexture("../BmpsP1/noche.bmp", t, 200);
	wings2->setTexture("../BmpsP1/noche.bmp", t, 200);
	wings3->setTexture("../BmpsP1/noche.bmp", t, 200);
	wings3 = wings2 = wings1 = new Ground(100.0, 50.0,1, 1, t );

	
	glm::dmat4 trans = translate(glm::dmat4(1), glm::dvec3(50, 50, 50));
	wings2->setModelMat(trans);
	addEntity(wings1);
	addEntity(wings2);

}

void WingAdvancedTIE::render(glm::dmat4 const& modelViewMat) const
{
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	//Se llama al render de todos los elementos
	for (auto& elems : gObjects)
	{
		elems->render(modelViewMat);
	}
}
