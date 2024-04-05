#include "QuadricEntity.h"

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
	// glEnable ( GL_COLOR_MATERIAL );
	// glColor3f (...);
	
	// Aquí se puede fijar el modo de dibujar la esfera :
	// gluQuadricDrawStyle (q, ...);

	gluSphere(q, radius, 50, 50);

	// Aquí se debe recuperar el color :
	// glColor3f (1.0 , 1.0 , 1.0);

}

//Cylinder
Cylinder::Cylinder(GLdouble base, GLdouble top)
	: QuadricEntity()
{
	//Creamos el cono
	baseRadius = base;
	topRadius = top;
	//gluCylinder(q, baseRadius, topRadius, height, slices, stacks);
	
}

void Cylinder::render(glm::dmat4 const& modelViewMat) const
{
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	gluCylinder(q, baseRadius, topRadius, 100, 50, 50);
}

//Disk
Disk::Disk(GLdouble inner, GLdouble outer)
	: QuadricEntity()
{
	innerRadius = inner;
	outerRadius = outer;
}

void Disk::render(glm::dmat4 const& modelViewMat) const
{
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	gluDisk(q, innerRadius, outerRadius, 50, 50);
}

//PartialDisk
PartialDisk::PartialDisk(GLdouble inner, GLdouble outer)
	: QuadricEntity()
{
	innerRadius = inner;
	outerRadius = outer;
	
}

void PartialDisk::render(glm::dmat4 const& modelViewMat) const
{
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	gluPartialDisk(q, innerRadius, outerRadius, 50, 50, 0, 30);
}
