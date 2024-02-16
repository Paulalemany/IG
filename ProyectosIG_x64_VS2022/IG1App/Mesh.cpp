#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

void
Mesh::draw() const
{
	glDrawArrays(
	  mPrimitive,
	  0,
	  size()); // primitive graphic, first index and number of elements to be rendered
}

void
Mesh::render() const
{
	if (vVertices.size() > 0) { // transfer data
		// transfer the coordinates of the vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(
		  3, GL_DOUBLE, 0, vVertices.data()); // number of coordinates per vertex, type of
		                                      // each coordinate, stride, pointer
		if (vColors.size() > 0) {             // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(
			  4, GL_DOUBLE, 0, vColors.data()); // components number (rgba=4), type of
			                                    // each component, stride, pointer
		}

		draw();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

Mesh* Mesh::generateRegularPolygon(GLuint num, GLdouble r)
{	
	Mesh* mesh = new Mesh();					//Creamos una nueva malla
	mesh->mPrimitive = GL_LINE_LOOP;			//Hacemos que las lineas empiencen y terminen en el mismo punto??
	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);				//Reserva espacio para el número de vértices


	for (int i = 0; i < num; i++) {
		mesh->vVertices.emplace_back(r * cos(radians((360.0/num) * i + 90.0)) , r * sin(radians((360.0 / num) * i + 90)), 0.0); //Se supone que pone el resto de vértices
	}

	return mesh;
}

Mesh* Mesh::generateRGBTriangle(GLdouble r)
{
	Mesh* mesh = new Mesh();							//Creamos una nueva malla
	glPolygonMode(GL_FRONT, GL_FILL);					//Primitiva para colorear
	//glPolygonMode(GL_BACK, GL_LINE);					//Dibuja las lineas detras
	glPolygonMode(GL_BACK, GL_POINT);					//Dibuja los puntos detras
	mesh->mNumVertices = 3.0;
	mesh->vVertices.reserve(mesh->mNumVertices);		//Reserva espacio para el número de vértices
	mesh->vColors.reserve(mesh->mNumVertices);

	for (int i = 0; i < mesh->mNumVertices; i++) {
		mesh->vVertices.emplace_back(r * cos(radians((360.0 / mesh->mNumVertices) * i + 90.0)), r * sin(radians((360.0 / mesh->mNumVertices) * i + 90.0)), 0.0); //Se supone que pone el resto de vértices
	}

	//Cambiar color de los vértices
	
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);	
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh* Mesh::generateRectangle(GLdouble w, GLdouble h)
{
	Mesh* mesh = new Mesh();							//Creamos una nueva malla
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);					//Primitiva para colorear
	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	

	mesh->mNumVertices = 4.0;							// v0, v1, v2, v3
	mesh->vVertices.reserve(mesh->mNumVertices);		//Reserva espacio para el número de vértices

	mesh->vVertices.emplace_back(-w/2,h/2,0);
	mesh->vVertices.emplace_back(w/2, h / 2,0);
	mesh->vVertices.emplace_back(-w/2, -h / 2,0);
	mesh->vVertices.emplace_back(w/2, - h / 2, 0);

	return mesh;
}

Mesh* Mesh::generateRGBRectangle(GLdouble w, GLdouble h)
{
	Mesh* mesh = new Mesh();					//Creamos una nueva malla
	glPolygonMode(GL_BACK, GL_LINE);			//Primitiva para colorear
	glPolygonMode(GL_FRONT, GL_FILL);

	mesh->mPrimitive = GL_TRIANGLE_STRIP;


	mesh->mNumVertices = 4.0;							// v0, v1, v2, v3
	mesh->vVertices.reserve(mesh->mNumVertices);		//Reserva espacio para el número de vértices
	mesh->vColors.reserve(mesh->mNumVertices);			//reserva para el color

	//posición
	mesh->vVertices.emplace_back(-w / 2, h / 2, 0);
	mesh->vVertices.emplace_back(w / 2, h / 2, 0);
	mesh->vVertices.emplace_back(-w / 2, -h / 2, 0);
	mesh->vVertices.emplace_back(w / 2, -h / 2, 0);

	//Color
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh* Mesh::generateCube(GLdouble length)
{
	Mesh* mesh = new Mesh();					//Creamos una nueva malla
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 8.0;							
	mesh->vVertices.reserve(mesh->mNumVertices);		//Reserva espacio para el número de vértices

	//posición primer triangulo
	mesh->vVertices.emplace_back(-length / 2, -length / 2, length / 2);
	mesh->vVertices.emplace_back(-length/2, length/2, length/2);
	mesh->vVertices.emplace_back(length/2, -length/2, length/2);
	mesh->vVertices.emplace_back(length/2, length/2, length/2);

	mesh->vVertices.emplace_back(-length / 2, -length / 2, -length / 2);
	mesh->vVertices.emplace_back(-length/2, length/2, -length/2);
	mesh->vVertices.emplace_back(length/2, -length/2, -length/2);
	mesh->vVertices.emplace_back(length/2, length/2, -length/2);
	//mesh->vVertices.emplace_back(-length/2, length/2, length/2);
	//mesh->vVertices.emplace_back(-length/2, length/2, length/2);
	//mesh->vVertices.emplace_back(-length/2, length/2, length/2);
	//mesh->vVertices.emplace_back(-length/2, length/2, length/2);
	

	return mesh;
}

Mesh*
Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}
