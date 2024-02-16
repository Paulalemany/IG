#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
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
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
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

RegularCube::RegularCube(GLdouble lenght)
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
