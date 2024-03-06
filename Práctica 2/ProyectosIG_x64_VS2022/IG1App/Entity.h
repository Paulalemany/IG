#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Mesh.h"

class Abs_Entity // abstract class
{
public:
	Abs_Entity()
	  : mModelMat(1.0), mColor(1) {}; // 4x4 identity matrix

	virtual ~Abs_Entity() = default;

	Abs_Entity(const Abs_Entity& e) = delete;            // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete; // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0; // abstract method
	virtual void update() {}	//Modifica el mModelMat de las entidades que la cambien

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	//Color
	glm::dvec4 const& color() const { return mColor; };
	void setColor(glm::dvec4 const& aColor) { mColor = aColor; };

	//Texture
	//Le pasamos como par�metro el nombre de la textura
	void setTexture(std::string textura, Texture * t, GLuint a)const { t->load(textura, a); }

protected:
	Mesh* mMesh = nullptr; // the mesh
	Texture* mTexture = nullptr;
	Texture* mTexture2 = nullptr;
	glm::dmat4 mModelMat;  // modeling matrix
	glm::dvec4 mColor;	   // color de la entidad

	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const;
};


class EjesRGB : public Abs_Entity
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class RegularPolygon : public Abs_Entity 
{
public: 
	explicit RegularPolygon(glm::dvec4 mColor, GLuint num, GLdouble r);
	~RegularPolygon();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class RGBTriangle : public Abs_Entity {
public:
	explicit RGBTriangle(GLdouble r);
	~RGBTriangle();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();

private:
	GLdouble rotationSp = 5.0;
};

class RegularRectangle : public Abs_Entity {
public:
	explicit RegularRectangle(GLdouble w, GLdouble h);
	~RegularRectangle();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class Ground : public Abs_Entity {
public:
	//Har� falta un ancho, un largo y el punto de origen??
	explicit Ground(GLdouble w, GLdouble h, GLuint rw, GLuint rh, std::string bmp);
	~Ground();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();

};

class RGBRectangle : public Abs_Entity {
public:
	explicit RGBRectangle(GLdouble w, GLdouble h);
	~RGBRectangle();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class RegularCube : public Abs_Entity {
public:
	explicit RegularCube(GLdouble lenght);
	~RegularCube();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class RGBCube : public Abs_Entity {
public:
	explicit RGBCube(GLdouble l);
	~RGBCube();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class BoxOutline : public Abs_Entity {
public:
	explicit BoxOutline(GLdouble l, std::string bmp, std::string bmp2);
	~BoxOutline();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class Star : public Abs_Entity {

	GLdouble rotationSp = 5.0;

public:
	explicit Star(GLuint num, GLdouble r);
	explicit Star(GLuint num, GLdouble r, GLdouble h);
	~Star();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class GlassParapet : public Abs_Entity{

public:
	explicit GlassParapet(GLdouble w, GLdouble h, std::string bmp);
	~GlassParapet();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

#endif //_H_Entities_H_
