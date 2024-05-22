#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Cara.h"
#include "../texturas/Texture.h"

#include <vector>

class Mesh
{
public:
	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh

	Mesh() = default;
	virtual ~Mesh() = default;

	Mesh(const Mesh& m) = delete;            // no copy constructor
	Mesh& operator=(const Mesh& m) = delete; // no copy assignment

	virtual void render() const;

	GLuint size() const { return mNumVertices; }; // number of elements
	std::vector<glm::dvec3> const& vertices() const { return vVertices; };
	std::vector<glm::dvec4> const& colors() const { return vColors; };

	static Mesh* generateRegularPolygon(GLuint num, GLdouble r);
	static Mesh* generateRGBTriangle(GLdouble r);
	static Mesh* generateRectangle(GLdouble w, GLdouble h);
	static Mesh* generateRGBRectangle(GLdouble w, GLdouble h);
	static Mesh* generateCube(GLdouble length);
	static Mesh* generateRGBCubeTriangles(GLdouble length);
	static Mesh* generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	static Mesh* generateBoxOutline(GLdouble length);
	static Mesh* generateParpet(GLdouble w, GLdouble h);
	static Mesh* generateStar3D(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generateWingAdvancedTIE(GLdouble w, GLdouble h);

protected:
	GLuint mPrimitive = GL_TRIANGLES;          // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0; // number of elements ( = vVertices.size())
	std::vector<glm::dvec3> vVertices; // vertex array
	std::vector<glm::dvec2> vTexCoords; //Texture Array
	std::vector<glm::dvec4> vColors;   // color array
	std::vector<glm::dvec3> vNormals; //apt61
	virtual void draw() const;
};


//APT62 -> copia pega de la diapo36
class IndexMesh : public Mesh 
{
protected:
	GLuint* nIndexes = nullptr; // tabla de índices
	GLuint nNumIndices = 0;
	std::vector<Cara> vCaras;
	
public:
	IndexMesh() { mPrimitive = GL_TRIANGLES; }
	~IndexMesh() { delete[] nIndexes; }
	virtual void render() const;
	virtual void draw() const;

	//apt63
	static IndexMesh* generateIndexedBox(GLdouble l);

	//metodo de newell (diap 38) - he creado la clase Cara
	void buildNormalVectors();
};

//Apt 69
class MbR : public IndexMesh
{
protected:

	GLint m;				//Número de puntos del perfil
	GLint n;				//Número de muestras al girar al rededor del eje
	//(Damos por hecho que van de abajo a arriba)
	glm::dvec3* perfil;	//Array de vértices que define el perfil que va a hacerse girar 

public:

	MbR(GLint mm, GLint nn, glm::dvec3* p) { m = mm, n = nn, perfil = p; }
	~MbR() override = default;
	static MbR* generateIndexMbR(int mm, int nn, glm::dvec3* perfil);
};

#endif //_H_Scene_H_
