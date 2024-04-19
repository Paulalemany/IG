#include "QuadricEntity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
//Sphere
Sphere::Sphere(GLdouble r)
	: QuadricEntity()
{
	//Creamos la esfera
	radius = r;
}

void Sphere::render(glm::dmat4 const& modelViewMat) const
{
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	// Aquí se puede fijar el color de la esfera así:
	 glEnable (GL_COLOR_MATERIAL);
	 glColor3f(green, red, blue);
	
	// Aquí se puede fijar el modo de dibujar la esfera :
	gluQuadricDrawStyle (q, GLU_FILL);

	gluSphere(q, radius, 50, 50);

	// Aquí se debe recuperar el color :
	glColor3f (1.0 , 1.0 , 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

//Cylinder
Cylinder::Cylinder(GLdouble base, GLdouble top)
	: QuadricEntity()
{
	//Creamos el cono
	baseRadius = base;
	topRadius = top;
	
}

void Cylinder::render(glm::dmat4 const& modelViewMat) const
{
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	// Aquí se puede fijar el color:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(red, green, blue);

	// Aquí se puede fijar el modo de dibujar:
	gluQuadricDrawStyle(q, GLU_FILL);

	gluCylinder(q, baseRadius, topRadius, 100, 50, 50);

	// Aquí se debe recuperar el color :
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);

}

//Disk
Disk::Disk(GLdouble inner, GLdouble outer)
	: QuadricEntity()
{
	innerRadius = inner;
	outerRadius = outer;

	//Transladamos a su sitio el disco para el apt 58
	
	mModelMat = rotate(dmat4(1), radians(80.0), dvec3(1.0, 0.0, 0.0)) * translate(dmat4(1), dvec3(0.0, 0.0, -80.0));
}

void Disk::render(glm::dmat4 const& modelViewMat) const
{
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	// Aquí se puede fijar el color:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1, 0, 0);

	// Aquí se puede fijar el modo de dibujar:
	gluQuadricDrawStyle(q, GLU_FILL);

	gluDisk(q, innerRadius, outerRadius, 50, 50);

	// Aquí se debe recuperar el color :
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

//PartialDisk
PartialDisk::PartialDisk(GLdouble inner, GLdouble outer, GLdouble start, GLdouble sweep)
	: QuadricEntity()
{
	innerRadius = inner;
	outerRadius = outer;
	startAngle = start;
	sweepAngle = sweep;

	mModelMat = rotate(dmat4(1), radians(-80.0), dvec3(0, 0, 1)) * translate(dmat4(1), dvec3(0, 0, 60));
	
}

void PartialDisk::render(glm::dmat4 const& modelViewMat) const
{
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	// Aquí se puede fijar el color:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0, 1, 0);

	// Aquí se puede fijar el modo de dibujar:
	gluQuadricDrawStyle(q, GLU_FILL);

	gluPartialDisk(q, innerRadius, outerRadius, 50, 50, startAngle, sweepAngle);

	// Aquí se debe recuperar el color :
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}
