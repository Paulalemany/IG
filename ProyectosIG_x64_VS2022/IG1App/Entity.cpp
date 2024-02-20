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
	std::cout << "EjesRGB update" << std::endl;
}

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
		glColor4d(0, 0, 0, 0);		//Restablecemos el color ¿Negro?
	}
}

void RegularPolygon::update()
{
	std::cout << "RegularPolygon update" << std::endl;
}

//RGBTriangle
RGBTriangle::RGBTriangle(GLdouble r)
	: Abs_Entity()
{
	//Creamos un triángulo
	mMesh = Mesh::generateRGBTriangle(r);
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
	std::cout << "RGBTriangle update" << std::endl;
}

RegularRectangle::RegularRectangle(GLdouble w, GLdouble h)
	: Abs_Entity()
{
	//Creamos un rectángulo
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
	std::cout << "RegularRectangle update" << std::endl;
}

RGBRectangle::RGBRectangle(GLdouble w, GLdouble h)
	: Abs_Entity()
{
	//Creamos un rectángulo
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
	std::cout << "RGBRectangle update" << std::endl;
}

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
