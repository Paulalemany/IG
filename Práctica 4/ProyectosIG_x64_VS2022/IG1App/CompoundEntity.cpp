#include "CompoundEntity.h"
#include <glm/gtc/matrix_transform.hpp>


#pragma region CompoundEntity
	void CompoundEntity::addEntity(Abs_Entity* ae)
	{
		gObjects.push_back(ae);
	}
	
	void CompoundEntity::render(const glm::dmat4& modelViewMat) const
	{
		glm::dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);
	
		//Se llama al render de todos los elementos
		for (auto& elems : gObjects)
		{
			elems->render(modelViewMat);
		}
	}

#pragma endregion

#pragma region AdvancedTIE
	AdvancedTIE::AdvancedTIE()
	{
		//Se crean los objetos que lo componen aquí
		//body = new Sphere(50.0);
		//body->QuadricColor(0.1, 0.2, 0.5);
		//addEntity(body);						//Cuerpo del TIE

		wings = new WingAdvancedTIE(100.0, 50.0);


		/*wings->setModelMat(
			translate(glm::dmat4(1.0), glm::dvec3(0, 500, 0))
			* wings->modelMat()
		);*/
		addEntity(wings);						//Alas del TIE
	}

	AdvancedTIE::~AdvancedTIE()
	{
	}

	void AdvancedTIE::render(glm::dmat4 const& modelViewMat) const
	{
		CompoundEntity::render(modelViewMat);
	}

	void AdvancedTIE::update()
	{

	}
#pragma endregion

#pragma region WingAdvancedTIE
	WingAdvancedTIE::WingAdvancedTIE(GLdouble w, GLdouble h)
	{
		//Ponemos la textura a todas las partes
		t = new Texture();
		wings1->setTexture("../BmpsP1/noche.bmp", t, 200);
		wings2->setTexture("../BmpsP1/noche.bmp", t, 200);
		wings3->setTexture("../BmpsP1/noche.bmp", t, 200);

		//Creamos cada parte del ala
		wings1 = new Ground(w, h, 1, 1, t);
		wings2 = new Ground(w, h, 1, 1, t);
		wings3 = new Ground(w, h, 1, 1, t);

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
#pragma endregion

