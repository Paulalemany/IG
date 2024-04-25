#include "CompoundEntity.h"
#include <glm/gtc/matrix_transform.hpp>

void CompoundEntity::addEntity(Abs_Entity* ae)
{
	gObjects.push_back(ae);
}

void CompoundEntity::moveModelMat(glm::dmat4 const& aMat)
{
	
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
	//Ponemos la textura a todas las partes
	t = new Texture();
	wings1->setTexture("../BmpsP1/noche.bmp", t, 200);
	wings2->setTexture("../BmpsP1/noche.bmp", t, 200);
	wings3->setTexture("../BmpsP1/noche.bmp", t, 200);

	//Creamos cada parte del ala
	wings1 = new Ground(100.0, 50.0, 1, 1, t );
	wings2 = new Ground(100.0, 50.0, 1, 1, t);
	wings3 = new Ground(100.0, 50.0, 1, 1, t);

	//Colocamos las alas de los extremos para que hagan la forma
	glm::dmat4 trans = translate(glm::dmat4(1), glm::dvec3(0, 17, 42)) * rotate(glm::dmat4(1), glm::radians(45.0), glm::dvec3(-1.0, 0, 0));
	wings2->setModelMat(trans);

	trans = translate(glm::dmat4(1), glm::dvec3(0, 17, -42)) * rotate(glm::dmat4(1), glm::radians(45.0), glm::dvec3(1.0, 0, 0));
	wings3->setModelMat(trans);

	//Añadimos la entidad
	addEntity(wings1);
	addEntity(wings2);
	addEntity(wings3);

	//mMesh = wings1->modelMat() + wings2->modelMat() + wings3->mModelMat();

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
