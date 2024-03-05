#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace glm;

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
			glColor4d(0, 0, 0, 0);		//Restablecemos el color �Negro?
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

	Ground::Ground(GLdouble w, GLdouble h, GLuint rw, GLuint rh, std::string bmp)
		: Abs_Entity()
	{
		//Creamos un rect�ngulo
		mMesh = Mesh::generateRectangleTexCor(w, h, rw, rh);

		//Textura del ground
		mTexture = new Texture();
		setTexture(bmp, mTexture); //creo que aqui va esto porque el setColor tb lo pusimos aqui
	};

	Ground::~Ground()
	{
		delete mMesh;
		delete mTexture;
		mMesh = nullptr;
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

	BoxOutline::BoxOutline(GLdouble l, std::string bmp, std::string bmp2)
		: Abs_Entity()
	{
		mMesh = Mesh::generateBoxOutline(l);
		mTexture = new Texture();
		mTexture2 = new Texture();
		setTexture(bmp, mTexture);
		setTexture(bmp2, mTexture2);
	}

	BoxOutline::~BoxOutline()
	{
		delete mMesh;
		delete mTexture;
		delete mTexture2;
		mMesh = nullptr;
	}

	void BoxOutline::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr) {
			glEnable(GL_CULL_FACE);
			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
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

			upload(aMat);
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
	Star::Star(GLuint num, GLdouble r, GLdouble h)
		:Abs_Entity()
	{
		mMesh = Mesh::generateStar3DTexCor(num, r, h);
		mTexture = new Texture();
		setTexture("../BmpsP1/baldosaP.bmp", mTexture);
	}

	Star::~Star()
	{
		delete mMesh;
		mMesh = nullptr;
	}

	void Star::render(glm::dmat4 const& modelViewMat) const
	{
		if (mMesh != nullptr) {
			dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
			upload(aMat);
			glLineWidth(2);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mTexture->bind(GL_MODULATE);
			mMesh->render();
			glLineWidth(1);

		}
	}

	void Star::update()
	{
		//rotacion de las estrellas
		mModelMat = rotate(mModelMat, radians(rotationSp), dvec3(0, 1.0, 1.0));

		////rotacion sobre el eje y
		//mModelMat = translate(mModelMat, dvec3(0, 17.35, 0));
	}

#pragma endregion
