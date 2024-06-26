#include "CompoundEntity.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../IG1App/Light.h"


using namespace glm;
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
			elems->render(aMat);
		}
	}

#pragma endregion

#pragma region AdvancedTIE
	AdvancedTIE::AdvancedTIE()
	{
		//Se crean los objetos que lo componen aqu�

		///Eje del TIE
		eje = new Cylinder(10, 10, 200);
		eje->QuadricColor(0.1, 0.2, 0.5);
		eje->setModelMat(
			translate(dmat4(1), dvec3(100, 100, 0))
		);
		addEntity(eje);

		///Cuerpo del TIE
		body = new Sphere(60.0);
		body->QuadricColor(0.1, 0.2, 0.5);
		body->setModelMat(
			translate(dmat4(1), dvec3(100, 100, 100))
		);
		addEntity(body);

		///Morro
		morro = new Cylinder(15, 15, 25);
		morro->QuadricColor(0.1, 0.2, 0.5);
		morro->setModelMat(
			translate(dmat4(1), dvec3(155, 100, 100))
			* rotate(dmat4(1), radians(90.0), dvec3(0.0, 1.0, 0.0))
		);
		addEntity(morro);

		///Disco del Morro
		tapaMorro = new Disk(5, 15);
		tapaMorro->QuadricColor(0.1, 0.2, 0.5);
		tapaMorro->setModelMat(
			translate(dmat4(1), dvec3(180, 100, 100))
			* rotate(dmat4(1), radians(90.0), dvec3(0.0, 1.0, 0.0))
		);
		addEntity(tapaMorro);

		/// Alas del TIE (al final porque son transparentes)
		wing1 = new WingAdvancedTIE(100.0, 50.0, 0);
		wing1->setModelMat(
			rotate(dmat4(1), glm::radians(-90.0), glm::dvec3(0.0, 0.0, 1.0))
			* translate(mModelMat, dvec3(-100, 100, 200)) 
			* rotate(dmat4(1), radians(180.0), dvec3(1.0, 0.0, 0.0))
		);
		addEntity(wing1);						

		wing2 = new WingAdvancedTIE(100.0, 50.0, 180);
		wing2->setModelMat(
			rotate(dmat4(1), glm::radians(-90.0), glm::dvec3(0.0, 0.0, 1.0))
			* translate(mModelMat, dvec3(-100, 100, 0))
		);
		addEntity(wing2);

		/// Foco
		//La posici�n inicial se fija en la constructora de la entidad que las contiene; generalmente esa
		//posici�n suele ser el punto(0, 0, 0)
		foco = new SpotLight();
		
	}

	AdvancedTIE::~AdvancedTIE()
	{
		delete foco;
		foco = nullptr;
	}

	void AdvancedTIE::render(glm::dmat4 const& modelViewMat) const
	{
		CompoundEntity::render(modelViewMat);
		// Actualizamos posicion del foco
		foco->upload(modelViewMat * mModelMat);
	}

	void AdvancedTIE::update()
	{
	}
	void AdvancedTIE::activaFoco()
	{
		foco->enable();
	}
	void AdvancedTIE::desactivaFoco()
	{
		foco->disable();
	}
#pragma endregion

#pragma region WingAdvancedTIE
	WingAdvancedTIE::WingAdvancedTIE(GLdouble w, GLdouble h, GLdouble rot)
	{
		
		//wings1->setTexture("../BmpsP1/noche.bmp", t, 200);
		//wings2->setTexture("../BmpsP1/noche.bmp", t, 200);
		//wings3->setTexture("../BmpsP1/noche.bmp", t, 200);

		////Creamos cada parte del ala
		//wings1 = new Ground(w, h, 1, 1, t);
		//wings2 = new Ground(w, h, 1, 1, t);
		//wings3 = new Ground(w, h, 1, 1, t);

		////Colocamos las alas de los extremos para que hagan la forma
		//glm::dmat4 trans = translate(glm::dmat4(1), glm::dvec3(0, 17, 42)) * rotate(glm::dmat4(1), glm::radians(45.0), glm::dvec3(-1.0, 0, 0));
		//wings2->setModelMat(trans);

		//trans = translate(glm::dmat4(1), glm::dvec3(0, 17, -42)) * rotate(glm::dmat4(1), glm::radians(45.0), glm::dvec3(1.0, 0, 0));
		//wings3->setModelMat(trans);

		////A�adimos la entidad
		//addEntity(wings1);
		//addEntity(wings2);
		//addEntity(wings3);
		
		//Ponemos la textura
		mTexture = new Texture();
		setTexture("../BmpsP1/noche.bmp", mTexture, 200);

		//Construimos el ala sobre el suelo
		mMesh = Mesh::generateWingAdvancedTIE(w, h);

	}

	void WingAdvancedTIE::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr) {

			glm::dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//Primitiva para colorear
			mTexture->bind(GL_MODULATE);

			upload(aMat);
			mMesh->render();

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mTexture->unbind();
		}
	}
#pragma endregion

