#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace glm;

void Abs_Entity::setRot(dvec3 nrot, GLdouble nang)
{
	rot = nrot;
	ang = glm::radians(nang);
}

void Abs_Entity::addRot(dvec3 addRot, GLdouble nang)
{
	rot += addRot;
	ang += glm::radians(nang);
}

//Abs_Entity
void
Abs_Entity::upload(dmat4 const& modelViewMat) const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat)); // transfers modelView matrix to the GPU
}


#pragma region EjesRGB
	//EjesRGB
	EjesRGB::EjesRGB(GLdouble l)
		: Abs_Entity()
	{
		mMesh = Mesh::createRGBAxes(l);
	}

	EjesRGB::~EjesRGB()
	{
		delete mMesh;
		mMesh = nullptr;
	};

	void
	EjesRGB::render(dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr) {
			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
			upload(aMat);
			glLineWidth(2);
			mMesh->render();
			glLineWidth(1);
		}
	}

	void EjesRGB::update()
	{	

	}
#pragma endregion

#pragma region RegularPolygon

	//RegularPolygon
	RegularPolygon::RegularPolygon(glm::dvec4 color, GLuint num, GLdouble r)
		: Abs_Entity()
	{
		mMesh = Mesh::generateRegularPolygon(num, r);
		setColor(color);
	}

	RegularPolygon::~RegularPolygon()
	{
		delete mMesh;
		mMesh = nullptr;
	}

	void RegularPolygon::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr) {
			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
			glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);	//Color del objeto
			upload(aMat);
			glLineWidth(2);
			mMesh->render();
			glLineWidth(1);
			glColor4d(0, 0, 0, 1);		//Restablecemos el color Negro?
		}
	}

	void RegularPolygon::update()
	{
		
	}
#pragma endregion

#pragma region RGBTriangle

	//RGBTriangle
	RGBTriangle::RGBTriangle(GLdouble r)
		: Abs_Entity()
	{
		//Creamos un tri�ngulo
		mMesh = Mesh::generateRGBTriangle(r);
		mModelMat = translate(mModelMat, dvec3(200, 0, 0)); // ??? funciona para colocarlo donde la circunferencia
	}

	RGBTriangle::~RGBTriangle()
	{
		delete mMesh;
		mMesh = nullptr;
	}

	void RGBTriangle::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr) {
			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

			upload(aMat);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);					//Primitiva para colorear
			mMesh->render();
			glLineWidth(1);
		}
	}

	void RGBTriangle::update()
	{
		//rotacion en sentido horario del triangulo
		mModelMat = rotate(mModelMat, radians(rotationSp), dvec3(0, 0, 1.0));

		//rotacion en sentido antihorario en la circunferencia aaaa
		mModelMat = translate(mModelMat, dvec3(0, 17.35, 0));
	}
#pragma endregion

#pragma region RegularRectangle

	RegularRectangle::RegularRectangle(GLdouble w, GLdouble h)
		: Abs_Entity()
	{
		//Creamos un rect�ngulo
		mMesh = Mesh::generateRectangle(w, h);
	}

	RegularRectangle::~RegularRectangle()
	{

		delete mMesh;
		mMesh = nullptr;
	}

	void RegularRectangle::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr) {
			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
			upload(aMat);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);					//Primitiva para colorear
			mMesh->render();
		}
	}

	void RegularRectangle::update()
	{

	}
#pragma endregion

#pragma region Ground

	Ground::Ground(GLdouble w, GLdouble h, GLuint rw, GLuint rh, Texture* t)
		: Abs_Entity()
	{
		//Creamos un rect�ngulo
		mMesh = Mesh::generateRectangleTexCor(w, h, rw, rh);
		//Textura del ground
		mTexture = t;
	};

	Ground::~Ground()
	{
		delete mMesh;
		delete mTexture;
		mMesh = nullptr;
		mTexture = nullptr;
	}

	void Ground::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr) {
			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//Primitiva para colorear
			mTexture->bind(GL_MODULATE);
			upload(aMat);
			mMesh->render();
			mTexture->unbind();
		}
	}

	void Ground::update()
	{
	}

#pragma endregion

#pragma region RGBRectangle

	RGBRectangle::RGBRectangle(GLdouble w, GLdouble h)
		: Abs_Entity()
	{
		//Creamos un rect�ngulo
		mMesh = Mesh::generateRGBRectangle(w, h);
	}

	RGBRectangle::~RGBRectangle()
	{
		delete mMesh;
		mMesh = nullptr;
	}

	void RGBRectangle::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr) {
			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
			upload(aMat);
			glLineWidth(2);
			mMesh->render();
			glLineWidth(1);
		}
	}

	void RGBRectangle::update()
	{
	}

#pragma endregion

#pragma region RegularCube

	RegularCube::RegularCube(GLdouble lenght)
		: Abs_Entity()
	{
		//Creamos un cubo
		mMesh = Mesh::generateCube(lenght);
	}

	RegularCube::~RegularCube()
	{
		delete mMesh;
		mMesh = nullptr;
	}

	void RegularCube::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr) {
			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			upload(aMat);
			glLineWidth(2);
			mMesh->render();
			glLineWidth(1);
		}
	}

	void RegularCube::update()
	{
		std::cout << "RegularCube update" << std::endl;
	}
#pragma endregion

#pragma region RGBCube

	RGBCube::RGBCube(GLdouble l)
		: Abs_Entity()
	{
		//Creamos un cubo
		mMesh = Mesh::generateRGBCubeTriangles(l);
	}

	RGBCube::~RGBCube()
	{
		delete mMesh;
		mMesh = nullptr;
	}

	void RGBCube::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr) {
			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
			upload(aMat);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mMesh->render();
		}
	}

	void RGBCube::update()
	{
		std::cout << "RGBCube update" << std::endl;
	}


#pragma endregion

#pragma region BoxOutline

	BoxOutline::BoxOutline(GLdouble l, Texture* t, Texture* t2)
		: Abs_Entity()
	{
		mMesh = Mesh::generateBoxOutline(l);

		//movemos la caja
		mModelMat = translate(dmat4(1), dvec3(0.0, -50, 0.0));

		mTexture = t;
		mTexture2 = t2;
	}

	BoxOutline::~BoxOutline()
	{
		delete mMesh;
		delete mTexture;
		delete mTexture2;
		mMesh = nullptr;
		mTexture = nullptr;
		mTexture2 = nullptr;
	}

	void BoxOutline::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr) {
			
			glEnable(GL_CULL_FACE);
			
			/// [ Culling ]
			// Que es? -> eliminar elementos, sacrificar selectivamente, entresacar o descartar
						// Tipos:
							// · Backface culling : eliminacion de caras traseras
							// · (view) Frustum culling : eliminacion de caras de una malla que estan fuera del frustum
							// · Occlusion culling : eliminacion de objetos que estan ocultos por otros objetos.
			// Como usar -> glEnable(GL_CULL_FACE);
			//				bind
			//				glCullFace(GL_BACK); // face = GL_FRONT, GL_BACK o GL_FRONT_AND_BACK
			//				render
			//				unbind
			//				*Se repite para GL_FRONT*
			//				glDisable(GL_CULL_FACE);

			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
			upload(aMat);

			glPolygonMode(GL_BACK, GL_FILL);	//Primitiva para colorear
			mTexture2->bind(GL_MODULATE);
			glCullFace(GL_BACK);
			mMesh->render();
			mTexture2->unbind();

			glPolygonMode(GL_FRONT, GL_FILL);
			mTexture->bind(GL_MODULATE);
			glCullFace(GL_FRONT);
			mMesh->render();
			mTexture->unbind();

			glDisable(GL_CULL_FACE);
			mMesh->render();
		}
	}

	void BoxOutline::update()
	{

	}

#pragma endregion

#pragma region Star
	Star::Star(GLuint num, GLdouble r)
		:Abs_Entity()
	{
		mMesh = Mesh::generateStar3D(num, r, 100.0);
	}
	Star::Star(GLuint num, GLdouble r, GLdouble h, Texture* t)
		:Abs_Entity()
	{
		mMesh = Mesh::generateStar3DTexCor(num, r, h);
		mModelMat = translate(dmat4(1), dvec3(0.0, 200.0, 0.0)); //apt 38
		mTexture = t;
	}

	Star::~Star()
	{
		delete mMesh;
		delete mTexture;
		mMesh = nullptr;
		mTexture = nullptr;
	}

	void Star::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr)
		{
			//La estrella la renderizamos dos veces (1 mesh, 2 renders)
			mTexture->bind(GL_REPLACE);
			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
			upload(aMat);
			glLineWidth(2);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mMesh->render();


			dmat4 rMat = mModelMat;
			rMat *= rotate(dmat4(1), radians(180.0), dvec3(0.0, 1.0, 0.0));
			aMat = modelViewMat * rMat; // glm matrix multiplication
			upload(aMat);
			mMesh->render();

			mTexture->unbind();
			glLineWidth(1);
		}
	}

	void Star::update()
	{
		//rotacion de la estrella
		mModelMat = translate(dmat4(1), dvec3(0.0, 200.0, 0.0)) *
			rotate(dmat4(1), radians(rotationSp), dvec3(0.0, 1.0, 0.0)) *
			rotate(dmat4(1), radians(-rotationSp), dvec3(0.0, 0.0, 1.0));

		rotationSp += 1;
	}

#pragma endregion

#pragma region GlassParapet
	GlassParapet::GlassParapet(GLdouble w, GLdouble h, Texture* t)
		:Abs_Entity()
	{
		mMesh = Mesh::generateParpet(w, h);
		mTexture = t;
	}

	GlassParapet::~GlassParapet()
	{
		delete mMesh;
		delete mTexture;
		mMesh = nullptr;
		mTexture = nullptr;
	}

	void GlassParapet::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr){
			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mTexture->bind(GL_MODULATE);

			upload(aMat);
			mMesh->render();
			mTexture->unbind();
		}
	}

	void GlassParapet::update()
	{
	}

#pragma endregion

#pragma region Photo

	Photo::Photo(GLdouble w, GLdouble h, Texture* t)
	{
		//Hacemos un rect�ngulo que se coloque en el suelo que tiene una textura
		//Creamos un rect�ngulo
		mMesh = Mesh::generateRectangleTexCor(w, h, 1, 1);
		mModelMat = translate(mModelMat, dvec3(0.0, 0.1, 0.0));	//Para ponerlo un poco m�s arriba
		mTexture = t;
	}

	Photo::~Photo()
	{
		delete mTexture;
		delete mMesh;
		mMesh = nullptr;
		mTexture = nullptr;
	}

	void Photo::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glLineWidth(2);
			mTexture->bind(GL_REPLACE);

			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
			upload(aMat);
			mMesh->render();

			mTexture->unbind();
			glLineWidth(1);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	void Photo::update()
	{
		mTexture->loadColorBuffer(800.0, 600.0);
	}

#pragma endregion

#pragma region IndexedBox

	IndexedBox::IndexedBox(GLdouble l)
	{
		mMesh = IndexMesh::generateIndexedBox(l);
	}

	IndexedBox::~IndexedBox()
	{
		delete mMesh;
		mMesh = nullptr;
	}

	void IndexedBox::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
			upload(aMat);

			mMesh->render();
		}
	}

	void IndexedBox::update()
	{
		Abs_Entity::update();
	}


	IndexedPyramid::IndexedPyramid(GLdouble l)
	{
		mMesh = IndexMesh::generateIndexPyramid(l);
	}

	IndexedPyramid::~IndexedPyramid()
	{
		delete mMesh;
		mMesh = nullptr;
	}

	void IndexedPyramid::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr)
		{ 
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
			upload(aMat);
			mMesh->render();

			//Renderizamos la parte de abajo del rombo
			dmat4 rMat = mModelMat;
			rMat *= rotate(dmat4(1), radians(180.0), dvec3(1.0, 0.0, 0.0));
			aMat = modelViewMat * rMat; // glm matrix multiplication
			upload(aMat);
			mMesh->render();

		}
	}

	void IndexedPyramid::update()
	{
	}

#pragma endregion

	
