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
	//Le pasamos como parámetro el nombre de la textura
	void setTexture(std::string textura, Texture * t, GLuint a)const { t->load(textura, a); }

	//apt68
	void setRot(glm::dvec3 nrot, GLdouble nang);
	void addRot(glm::dvec3 addRot, GLdouble nang);
	void setPos(glm::dvec3 newpos) { pos = newpos; }
	void setPos(GLdouble x, GLdouble y, GLdouble z) { setPos(glm::dvec3(x, y, z)); }
	glm::dvec3 getPos() { return pos; }

protected:
	Mesh* mMesh = nullptr; // the mesh
	Texture* mTexture = nullptr;
	Texture* mTexture2 = nullptr;
	glm::dmat4 mModelMat;  // modeling matrix
	glm::dvec4 mColor;	   // color de la entidad

	glm::dvec3 pos;
	glm::dvec3 rot;
	GLdouble ang;

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
	//Hará falta un ancho, un largo y el punto de origen??
	explicit Ground(GLdouble w, GLdouble h, GLuint rw, GLuint rh, Texture* t);
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
	explicit BoxOutline(GLdouble l, Texture* t, Texture* t2);
	~BoxOutline();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class Star : public Abs_Entity {

	GLdouble rotationSp = 5.0;

public:
	explicit Star(GLuint num, GLdouble r);
	explicit Star(GLuint num, GLdouble r, GLdouble h, Texture* t);
	~Star();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class GlassParapet : public Abs_Entity{

public:
	explicit GlassParapet(GLdouble w, GLdouble h, Texture* ts);
	~GlassParapet();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class Photo : public Abs_Entity {

public:
	explicit Photo(GLdouble w, GLdouble h, Texture* t);
	~Photo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class EWingAdvancedTIE : public Abs_Entity {
public:
	//Hará falta un ancho, un largo y el punto de origen??
	explicit EWingAdvancedTIE(GLdouble w, GLdouble h, GLuint rw, GLuint rh, Texture* t);
	~EWingAdvancedTIE();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();

};

class IndexedBox : public Abs_Entity {
public:
	explicit IndexedBox(GLdouble l);
	~IndexedBox();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();

	//void buildNormalVectors(); //apt 65
};

class RbmSphere : public Abs_Entity {
public:

	RbmSphere(GLdouble r, GLint p, GLint m);
	~RbmSphere() { delete mMesh; }
	virtual void render(glm::dmat4 const& modelViewMat) const override;
	virtual void update() override {};

protected:
	glm::dvec3* perfil;

};

class RbmToroid : public Abs_Entity {
public:

	RbmToroid(GLuint r, GLuint R, GLuint m, GLuint p);
	~RbmToroid() { delete mMesh; delete[] perfil; }
	virtual void render(glm::dmat4 const& modelViewMat) const override;
	virtual void update() override {};

protected:
	glm::dvec3* perfil;

};

#endif //_H_Entities_H_
