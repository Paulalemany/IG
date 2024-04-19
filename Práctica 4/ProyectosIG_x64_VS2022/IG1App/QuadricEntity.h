#pragma once
#include "Entity.h"

class QuadricEntity : public Abs_Entity
{
public:

	QuadricEntity() { q = gluNewQuadric(); }	//Constructora
	~QuadricEntity() { gluDeleteQuadric(q); }	//Destructora

	void QuadricColor(GLdouble r, GLdouble g, GLdouble b) { red = r, green = g, blue = b; }

protected:
	GLUquadricObj* q;	//Declaración de las entidades cuádricas
	GLdouble red = 0, blue = 0, green = 0;
};

class Sphere  : public QuadricEntity
{
public:
	Sphere(GLdouble r);	
	void render(glm::dmat4 const& modelViewMat) const;

protected:
	GLdouble radius;

};

class Cylinder : public QuadricEntity
{
public:
	Cylinder(GLdouble base, GLdouble top);	//Constructora del cilindro

	void render(glm::dmat4 const& modelViewMat) const;

protected:
	GLdouble baseRadius;
	GLdouble topRadius;
};

class Disk : public QuadricEntity
{
public:
	Disk(GLdouble innerRadius, GLdouble outerRadius);	//Constructora del disco
	void render(glm::dmat4 const& modelViewMat) const;

protected:
	GLdouble innerRadius;
	GLdouble outerRadius;
};

class PartialDisk : public QuadricEntity
{
public:
	PartialDisk(GLdouble innerRadius, GLdouble outerRadius, GLdouble startAngle, GLdouble sweepAngle);	//Constructora del disco
	void render(glm::dmat4 const& modelViewMat) const;

protected:
	GLdouble innerRadius;
	GLdouble outerRadius;
	GLdouble startAngle;
	GLdouble sweepAngle;
};

