#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;


#pragma region Void

void Mesh::draw() const
{
	glDrawArrays(
		mPrimitive,
		0,
		size()); // primitive graphic, first index and number of elements to be rendered
}

void Mesh::render() const
{
	if (vVertices.size() > 0) 
	{ // transfer data
		// transfer the coordinates of the vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(
			3, GL_DOUBLE, 0, vVertices.data()); // number of coordinates per vertex, type of
		// each coordinate, stride, pointer
		if (vColors.size() > 0) 
		{             // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(
				4, GL_DOUBLE, 0, vColors.data()); // components number (rgba=4), type of
			// each component, stride, pointer
		}
		if (vTexCoords.size() > 0) // El metodo Mesh::render activa y desactiva el array de coordenadas de textura.
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(
				2, GL_DOUBLE, 0, vTexCoords.data());
		}
		//Apt61
		if (vNormals.size() > 0) 
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}

		draw();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}
#pragma endregion

#pragma region Mesh

Mesh* Mesh::generateRegularPolygon(GLuint num, GLdouble r)
{
	Mesh* mesh = new Mesh();					//Creamos una nueva malla
	mesh->mPrimitive = GL_LINE_LOOP;			//Hacemos que las lineas empiencen y terminen en el mismo punto??
	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);				//Reserva espacio para el n�mero de v�rtices

	for (int i = 0; i < num; i++) {
		mesh->vVertices.emplace_back(r * cos(radians((360.0 / num) * i + 90.0)), r * sin(radians((360.0 / num) * i + 90)), 0.0); //Se supone que pone el resto de v�rtices
	}

	return mesh;
}

Mesh* Mesh::generateRGBTriangle(GLdouble r)
{
	Mesh* mesh = new Mesh();							//Creamos una nueva malla
	glPolygonMode(GL_FRONT, GL_FILL);					//Primitiva para colorear
	//glPolygonMode(GL_BACK, GL_LINE);					//Dibuja las lineas detras
	//glPolygonMode(GL_BACK, GL_POINT);					//Dibuja los puntos detras
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);					//Dibuja los puntos detras

	mesh->mNumVertices = 3.0;
	mesh->vVertices.reserve(mesh->mNumVertices);		//Reserva espacio para el n�mero de v�rtices
	mesh->vColors.reserve(mesh->mNumVertices);

	for (int i = 0; i < mesh->mNumVertices; i++) {
		mesh->vVertices.emplace_back(r * cos(radians((360.0 / mesh->mNumVertices) * i + 90.0)), r * sin(radians((360.0 / mesh->mNumVertices) * i + 90.0)), 0.0); //Se supone que pone el resto de v�rtices
	}

	//Cambiar color de los v�rtices

	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh* Mesh::generateRectangle(GLdouble w, GLdouble h)
{
	Mesh* mesh = new Mesh();							//Creamos una nueva malla
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);					//Primitiva para colorear
	mesh->mPrimitive = GL_TRIANGLE_STRIP; // Dibuja los triangulos en sentido antihorario, tomando el triangulo anterior.
														// -> Ej. Si tenemos 6 vertices: v0, v1, v2...
														//        Se colocaran 0,1,2 / luego 2,1,3 / 2,3,4 / 4,3,5 / 4,5,6


	mesh->mNumVertices = 4.0;							// v0, v1, v2, v3
	mesh->vVertices.reserve(mesh->mNumVertices);		//Reserva espacio para el n�mero de v�rtices
	mesh->vColors.reserve(mesh->mNumVertices);			//reserva para el color

	GLdouble altura = -75; //apt 38
	GLdouble offset = 0; // 150; //199; //apt 38

	mesh->vVertices.emplace_back(-w / 2, 0, -h / 2);
	mesh->vVertices.emplace_back(w / 2, 0, -h / 2);
	mesh->vVertices.emplace_back(-w / 2, 0, h / 2);
	mesh->vVertices.emplace_back(w / 2, 0, h / 2);

	//Color
	mesh->vColors.emplace_back(1.0, 1.0, 1.0, 1.0);
	mesh->vColors.emplace_back(1.0, 1.0, 1.0, 1.0);
	mesh->vColors.emplace_back(1.0, 1.0, 1.0, 1.0);
	mesh->vColors.emplace_back(1.0, 1.0, 1.0, 1.0);

	return mesh;
}

Mesh* Mesh::generateRGBRectangle(GLdouble w, GLdouble h)
{
	Mesh* mesh = new Mesh();					//Creamos una nueva malla
	glPolygonMode(GL_BACK, GL_LINE);			//Primitiva para colorear
	glPolygonMode(GL_FRONT, GL_FILL);

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 4.0;							// v0, v1, v2, v3
	mesh->vVertices.reserve(mesh->mNumVertices);		//Reserva espacio para el n�mero de v�rtices
	mesh->vColors.reserve(mesh->mNumVertices);			//reserva para el color

	//posici�n
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

Mesh* Mesh::generateCube(GLdouble l)
{
	Mesh* mesh = new Mesh();					//Creamos una nueva malla
	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 14;
	mesh->vVertices.reserve(mesh->mNumVertices);		//Reserva espacio para el n�mero de v�rtices

	//lo que hace el triangle strip -> coge dos vertices anteriores para hacer el triangulo

	GLdouble a = l / 2;

	mesh->vVertices.emplace_back(-a, -a, -a); //v0
	mesh->vVertices.emplace_back(a, -a, -a); //v1
	mesh->vVertices.emplace_back(-a, -a, a); //v2
	mesh->vVertices.emplace_back(a, -a, a); //v3
	mesh->vVertices.emplace_back(a, a, a); //v4
	mesh->vVertices.push_back(mesh->vVertices[1]); //v5 = v1
	mesh->vVertices.emplace_back(a, a, -a); //v6
	mesh->vVertices.push_back(mesh->vVertices[0]); //v7 = v0
	mesh->vVertices.emplace_back(-a, a, -a); //v8
	mesh->vVertices.push_back(mesh->vVertices[2]); //v9 = v2
	mesh->vVertices.emplace_back(-a, a, a); //v10
	mesh->vVertices.push_back(mesh->vVertices[4]); //v11 = v4
	mesh->vVertices.push_back(mesh->vVertices[8]); //v12 = v8
	mesh->vVertices.push_back(mesh->vVertices[6]); //v13 = v6

	return mesh;
}

Mesh* Mesh::generateRGBCubeTriangles(GLdouble l)
{
	Mesh* mesh = new Mesh();					//Creamos una nueva malla
	mesh->mPrimitive = GL_TRIANGLES;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	mesh->mNumVertices = 36;
	mesh->vVertices.reserve(mesh->mNumVertices);		//Reserva espacio para el n�mero de v�rtices
	mesh->vColors.reserve(mesh->mNumVertices);			//Reerva espacio para los colores

	GLdouble m = l / 2;

	// triangulo 1 cara 1
	mesh->vVertices.emplace_back(-m, -m, -m); // v0
	mesh->vVertices.emplace_back(m, -m, -m); // v1
	mesh->vVertices.emplace_back(-m, -m, m); // v2
	// triangulo 2 cara 1
	mesh->vVertices.emplace_back(m, -m, m); // v3
	mesh->vVertices.push_back(mesh->vVertices[1]); // v4 = v1
	mesh->vVertices.push_back(mesh->vVertices[2]); // v5 = v2

	// triangulo 1 cara 2
	mesh->vVertices.push_back(mesh->vVertices[3]); // v6 = v3
	mesh->vVertices.emplace_back(m, m, m); // v7
	mesh->vVertices.push_back(mesh->vVertices[1]); // v8 = v5 = v2
	// triangulo 2 cara 2
	mesh->vVertices.emplace_back(m, m, -m); // v9
	mesh->vVertices.push_back(mesh->vVertices[7]); // v10 = v7
	mesh->vVertices.push_back(mesh->vVertices[1]); // v11 = v1

	// triangulo 1 cara 3
	mesh->vVertices.push_back(mesh->vVertices[9]); // v12 = v9
	mesh->vVertices.push_back(mesh->vVertices[0]); // v13 = v0
	mesh->vVertices.emplace_back(-m, m, -m); // v14
	// triangulo 2 cara 3
	mesh->vVertices.push_back(mesh->vVertices[9]); // v12 = v9
	mesh->vVertices.push_back(mesh->vVertices[0]); // v13 = v0
	mesh->vVertices.push_back(mesh->vVertices[1]); // v14 = v1

	// triangulo 1 cara 4
	mesh->vVertices.emplace_back(-m, m, -m); // v15 = -v0
	mesh->vVertices.emplace_back(m, m, -m); // v16 = -v1
	mesh->vVertices.emplace_back(-m, m, m); // v17 = -v2
	// triangulo 2 cara 4
	mesh->vVertices.emplace_back(m, m, m); // v18 = -v3
	mesh->vVertices.emplace_back(m, m, -m); // v19 = v16 = -v4 = -v1
	mesh->vVertices.emplace_back(-m, m, m); // v20 = v17 = -v5 = -v2
	// ^^^^ - en y


	// triangulo 1 cara 5
	mesh->vVertices.emplace_back(-m, -m, m); // v21 = -v6 = -v3
	mesh->vVertices.emplace_back(-m, m, m); // v22 = -v7
	mesh->vVertices.emplace_back(-m, -m, -m); // v23 = 
	// triangulo 2 cara 5
	mesh->vVertices.emplace_back(-m, m, -m); // v24 = -v9
	mesh->vVertices.emplace_back(-m, m, m); // v25 = -v10 = -v7
	mesh->vVertices.emplace_back(-m, -m, -m); // v26 = -v11 = -v1
	// ^^^^ - en x

	// triangulo 1 cara 6
	mesh->vVertices.emplace_back(m, m, m); // v27 = -v9
	mesh->vVertices.emplace_back(-m, -m, m); // v28 = -v0
	mesh->vVertices.emplace_back(-m, m, m); // v29
	// triangulo 2 cara 6
	mesh->vVertices.emplace_back(m, m, m); // v30 = v27
	mesh->vVertices.emplace_back(-m, -m, m); // v31 = v28
	mesh->vVertices.emplace_back(m, -m, m); // v32 = v3
	// ^^^^ - en z

	// cara 1
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// cara 2
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// cara 3
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	// cara 4
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// cara 5
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// cara 6
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh* Mesh::generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* mesh = generateRectangle(w, h);
	mesh->vTexCoords.reserve(mesh->mNumVertices);
	mesh->vTexCoords.emplace_back(0, rh);
	mesh->vTexCoords.emplace_back(rw, rh);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(rw, 0);

	return mesh;
}

Mesh* Mesh::generateBoxOutline(GLdouble length)
{
	Mesh* mesh = new Mesh();					//Creamos una nueva malla
	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 10;
	mesh->vVertices.reserve(mesh->mNumVertices);		//Reserva espacio para el n�mero de v�rtices

	//lo que hace el triangle strip -> coge dos vertices anteriores para hacer el triangulo

	GLdouble a = length / 2;

	//Cubo sin tapas
	mesh->vVertices.emplace_back(a, -a, a); //v0
	mesh->vVertices.emplace_back(a, a, a); //v1
	mesh->vVertices.emplace_back(a, -a, -a); //v2

	mesh->vVertices.emplace_back(a, a, -a); //v3
	mesh->vVertices.emplace_back(-a, -a, -a); //v4
	mesh->vVertices.emplace_back(-a, a, -a); //v5

	mesh->vVertices.emplace_back(-a, -a, a); //v6
	mesh->vVertices.emplace_back(-a, a, a); //v7

	mesh->vVertices.push_back(mesh->vVertices[0]); //v8
	mesh->vVertices.push_back(mesh->vVertices[1]); //v9

	//TexCoords
	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(1, 1);
	mesh->vTexCoords.emplace_back(1, 0);

	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(1, 1);
	mesh->vTexCoords.emplace_back(1, 0);

	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);

	return mesh;
}

Mesh* Mesh::generateParpet(GLdouble w, GLdouble h)
{
	Mesh* mesh = new Mesh();					//Creamos una nueva malla
	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 10;
	mesh->vVertices.reserve(mesh->mNumVertices);		//Reserva espacio para el n�mero de v�rtices

	//lo que hace el triangle strip -> coge dos vertices anteriores para hacer el triangulo

	GLdouble a = w / 2;
	GLdouble b = h / 2;

	GLdouble altura = 0; // 150; //apt 38
	GLdouble offset = 0; // 150; //apt 38

	mesh->vVertices.emplace_back(a + offset, -b + altura, a + offset); //v0
	mesh->vVertices.emplace_back(a + offset, b + altura, a + offset); //v1
	mesh->vVertices.emplace_back(a + offset, -b + altura, -a + offset); //v2

	mesh->vVertices.emplace_back(a + offset, b + altura, -a + offset); //v3
	mesh->vVertices.emplace_back(-a + offset, -b + altura, -a + offset); //v4
	mesh->vVertices.emplace_back(-a + offset, b + altura, -a + offset); //v5

	mesh->vVertices.emplace_back(-a + offset, -b + altura, a + offset); //v6
	mesh->vVertices.emplace_back(-a + offset, b + altura, a + offset); //v7

	mesh->vVertices.push_back(mesh->vVertices[0]); //v8
	mesh->vVertices.push_back(mesh->vVertices[1]); //v9

	//TexCoords
	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(1, 1);
	mesh->vTexCoords.emplace_back(1, 0);

	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(1, 1);
	mesh->vTexCoords.emplace_back(1, 0);

	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);

	return mesh;
}

Mesh* Mesh::generateStar3D(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_FAN;			// Todos los triangulos comparten un vertice comun.
	mesh->mNumVertices = 2 * (np + 1);
	mesh->vVertices.reserve(mesh->mNumVertices);				//Reserva espacio para el n�mero de v�rtices

	mesh->vVertices.emplace_back(0, 0, 0);						//Primer v�rtice (Centro) -Vertice en comun-

	//Primera estrella
	for (int i = 0; i < np; i++) {

		//Dividimos entre pares e impares (Unos est�n m�s arriba y otros m�s abajo)
		if (i % 2 == 0)	//Si es par
		{
			mesh->vVertices.emplace_back(re / 2 * cos(radians((360.0 / (np - 1)) * i + 90.0)), re / 2 * sin(radians((360.0 / (np - 1)) * i + 90)), h); //Se supone que pone el resto de v�rtices
		}
		else {
			mesh->vVertices.emplace_back(re / 4 * cos(radians((360.0 / (np - 1)) * i + 90.0)), re / 4 * sin(radians((360.0 / (np - 1)) * i + 90)), h); //Se supone que pone el resto de v�rtices
		}
	}

	//Colocamos el �ltimo en el mismo punto del primeros
	mesh->vVertices.push_back(mesh->vVertices[0]); // v14 = v1

	return mesh;
}

Mesh* Mesh::generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* mesh = new Mesh();
	mesh = generateStar3D(re, np, h);

	//Le ponemos las cosas de la textura
	//TexCoords
	mesh->vTexCoords.reserve(mesh->mNumVertices);

	//empiezo en 0.5, 0.5
	mesh->vTexCoords.emplace_back(0.5, 0.5);

	for (int i = 0; i < 4; i++) {
		mesh->vTexCoords.emplace_back(0.0, 1.0);
		mesh->vTexCoords.emplace_back(0.5, 1.0);
		mesh->vTexCoords.emplace_back(0.0, 1.0);
		mesh->vTexCoords.emplace_back(0.0, 0.5);
	}

	mesh->vTexCoords.emplace_back(0.0, 1.0);

	return mesh;
}

Mesh* Mesh::generateWingAdvancedTIE(GLdouble w, GLdouble h)
{
	Mesh* mesh = new Mesh();						//Creamos una nueva malla
	mesh->mPrimitive = GL_TRIANGLE_STRIP;			//Podemos utilizar la primitiva que queramos

	mesh->mNumVertices = 8;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(w / 2, h, h); //v0
	mesh->vVertices.emplace_back(w / 2, -h, h); //v1
	mesh->vVertices.emplace_back(h / 2, h, 0); //v2
	mesh->vVertices.emplace_back(h / 2, -h, 0); //v3
	mesh->vVertices.emplace_back(-h / 2, h, 0); //v4
	mesh->vVertices.emplace_back(-h / 2, -h, 0); //v5
	mesh->vVertices.emplace_back(-w / 2, h, h); //v6
	mesh->vVertices.emplace_back(-w / 2, -h, h); //v3


	mesh->vTexCoords.emplace_back(0.0, 0.0);	//v0
	mesh->vTexCoords.emplace_back(0.0, 1.0);	//v1
	mesh->vTexCoords.emplace_back(0.33, 0.0);	//v2
	mesh->vTexCoords.emplace_back(0.33, 1.0);	//v3
	mesh->vTexCoords.emplace_back(2 * 0.33, 0.0);	//v4
	mesh->vTexCoords.emplace_back(2 * 0.33, 1.0);	//v5
	mesh->vTexCoords.emplace_back(1.0, 0.0);	//v6
	mesh->vTexCoords.emplace_back(1.0, 1.0);	//v7

	return mesh;
}

Mesh* Mesh::createRGBAxes(GLdouble l)
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
#pragma endregion

#pragma region IndexMesh
//render y draw de la diap37
void IndexMesh::render() const
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
		if (vTexCoords.size() > 0) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(
				2, GL_DOUBLE, 0, vTexCoords.data());
		}
		//Apt61
		if (vNormals.size() > 0) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}

		if (nIndexes != nullptr) {
			glEnableClientState(GL_INDEX_ARRAY);
			glIndexPointer(GL_UNSIGNED_INT, 0, nIndexes);
		}

		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_FILL);

		draw();

		glDisableClientState(GL_INDEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_FILL);

	}
}

void IndexMesh::draw() const
{
	// Comando para renderizar la malla indexada enviada
	glDrawElements(mPrimitive, nNumIndices, GL_UNSIGNED_INT, nIndexes);
}

//apt63
IndexMesh* IndexMesh::generateIndexedBox(GLdouble l)
{

	//Versi�n de la profe
	const auto mesh = new IndexMesh();

	///V�rtices
	//Reservamos el n�mero de v�rtices
	mesh->mNumVertices = 8;
	mesh->vVertices.reserve(mesh->mNumVertices);

	const GLdouble m = l / 2;
	//Colocamos los v�rtices en su sitio
	mesh->vVertices.emplace_back(-m, m, m);		// v0
	mesh->vVertices.emplace_back(-m, -m, m);	// v1
	mesh->vVertices.emplace_back(m, m, m);		// v2
	mesh->vVertices.emplace_back(m, -m, m);		// v3
	//vertices de la cara de delante
	mesh->vVertices.emplace_back(m, m, -m);		// v4
	mesh->vVertices.emplace_back(m, -m, -m);	// v5
	mesh->vVertices.emplace_back(-m, m, -m);	// v6
	mesh->vVertices.emplace_back(-m, -m, -m);	// v7

	///�ndices
	//Definimos los 36 �ndices 
	//(3 v�rtices por cada tri�ngulo, 12 tri�ngulos) de 3 en 3
	//Se crean en sentido ANTIHORARIO para que las normales se coloquen correctamente

	mesh->nNumIndices = 36;
	mesh->nIndexes = new GLuint[mesh->nNumIndices];

	const GLuint arr[36] =
	{
		0, 1, 2, 1, 3, 2, 2, 3, 4,
		3, 5, 4, 4, 5, 6, 5, 7, 6,
		//diagonal al derecho en la cara lateral izquierda
		//6, 7, 0, 7, 1, 0,
		//diafonal  al contrario en la cara lateral izquierda
		0, 6, 1, 6, 7, 1,
		0, 2, 4, 4, 6, 0, 1, 5, 3, 1, 7, 5
	};

	for (int i = 0; i < mesh->nNumIndices; i++) {
		mesh->nIndexes[i] = arr[i];
	}

	///Caras
	int nV = 3;
	mesh->vCaras.resize(mesh->nNumIndices / nV);
	for (int i = 0; i < mesh->nNumIndices / nV; i++) {

		int realNv = i * nV;
		mesh->vCaras[i] = Cara(
			mesh->nIndexes[realNv],
			mesh->nIndexes[realNv + 1],
			mesh->nIndexes[realNv + 2]
		);
	}

	///Colores
	mesh->vColors.reserve(mesh->mNumVertices);
	for (int i = 0; i < mesh->mNumVertices; i++) {
		mesh->vColors.emplace_back(0, 1, 0, 1);
	}

	///Normales
	mesh->buildNormalVectors();

	return mesh;
}

IndexMesh* IndexMesh::generateIndexPyramid(GLdouble l)
{
	IndexMesh* mesh = new IndexMesh();

	mesh->mPrimitive = GL_TRIANGLES;
	mesh->mNumVertices = 5;	//Solo hacemos una mitad
	mesh->vVertices.reserve(mesh->mNumVertices);

	//Colocamos los vértices en su sitio
	GLdouble m = l / 2;
	mesh->vVertices.emplace_back(0, l, 0);	//v0
	mesh->vVertices.emplace_back(m, 0, m);	//v1
	mesh->vVertices.emplace_back(m, 0, -m);	//v2
	mesh->vVertices.emplace_back(-m, 0, -m);//v3
	mesh->vVertices.emplace_back(-m, 0, m);	//v4

	//hay 6 triangulos en total
	//(1 por cara 2 en la base)
	//Cada cara formada por 3 vértices
	//6*3 = 18
	mesh->nNumIndices = 18;
	mesh->nIndexes = new GLuint[mesh->nNumIndices];

	//Union de los vértices para hacer cada cara
	const GLuint arr[18]{
		0,4,1,
		1,4,2,
		2,3,0,
		0,3,4,
		4,3,2,
		2,0,1
	};

	//Asignamos los indices
	for (int i = 0; i < mesh->nNumIndices; i++) {
		mesh->nIndexes[i] = arr[i];
	}

	//Añadimos los vértices de color
	mesh->vColors.reserve(mesh->mNumVertices);
	for (int i = 0; i < mesh->mNumVertices; i++) {
		mesh->vColors.emplace_back(1, 0.75, 0.9, 1);
	}

	//Numero de vértices que hay por cada cara
	int vertices = 3;
	float numCaras = mesh->nNumIndices / vertices;
	mesh->vCaras.resize(numCaras);
	for (int i = 0; i < numCaras; i++) {

		mesh->vCaras[i] = Cara(
			mesh->nIndexes[i * vertices],
			mesh->nIndexes[i * vertices + 1],
			mesh->nIndexes[i * vertices + 2]);
	}

	mesh->buildNormalVectors();

	return mesh;
}

//hacemos la versi�n de la profe a ver si as� el cubo de ilumina bien
void IndexMesh::buildNormalVectors()
{
	for (int i = 0; i < mNumVertices; i++) {
		vNormals.emplace_back(0, 0, 0);
	}
	for (int i = 0; i < nNumIndices; i += 3) {
		glm::dvec3 n(0.0, 0.0, 0.0); //vector normal donde nos dara el resultado de las operaciones entre los vertices
		//obtener los 3 indices que corresponden al triangulo actual
		GLuint ind_a = nIndexes[i];
		GLuint ind_b = nIndexes[i + 1];
		GLuint ind_c = nIndexes[i + 2];
		//vectores entre vertices
		glm::dvec3 v1 = vVertices[ind_b] - vVertices[ind_a];
		glm::dvec3 v2 = vVertices[ind_c] - vVertices[ind_b];
		//producto cruz entre los vectores para obtener la norma
		n = glm::cross(v1, v2);

		//sumar la normal obtenida a los vertices de la cara actual
		vNormals[ind_a] += n;
		vNormals[ind_b] += n;
		vNormals[ind_c] += n;
	}
	//normalizar todas las normales resultantes
	for (auto& normal : vNormals) {
		normal = glm::normalize(normal);
	}
}
#pragma endregion

#pragma region MbR

// APT 70 - Siguiendo las diapositivas Mallas por Revolucion
// 3.
MbR* MbR::generateIndexMbR(int mm, int nn, glm::dvec3* perfil)
{

	// mm: numero de puntos del perfil
	// nn: numero de rotaciones
	// perfil: perfil en el plano XY

	MbR* mesh = new MbR(mm, nn, perfil);	//Creamos la malla

	mesh->mPrimitive = GL_TRIANGLES;		//Primitiva [Exclusiva de Mallas Indexadas]
	mesh->mNumVertices = nn * mm;			//N�mero de v�rtices

	mesh->vVertices.reserve(mesh->mNumVertices);

	auto vs = new dvec3[mesh->mNumVertices];	//Vector auxiliar de v�rtices

	for (int i = 0; i < nn; i++)
	{
		//Genera la muestra i-�sima de v�rtices
		GLdouble theta = i * 360 / nn;

		GLdouble c = cos(radians(theta));
		GLdouble s = sin(radians(theta));

		for (int j = 0; j < mm; j++)
		{
			GLdouble z = -s * perfil[j].x + c * perfil[j].z;
			GLdouble x = c * perfil[j].x + s * perfil[j].z;

			int Indice = i * mm + j;
			vs[Indice] = dvec3(x, perfil[j].y, z);
		}
	}

	// 4. Volcar el array auxiliar v�rtices en el array de v�rtices
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		mesh->vVertices.emplace_back(vs[i]);
	}
	delete[] vs;

	// 5. Construir los �ndices de las caras triangulares
	int indiceMayor = 0;
	mesh->nNumIndices = mesh->mNumVertices * 6;
	mesh->nIndexes = new GLuint[mesh->nNumIndices];

	// Inicializamos nIndexes a 0
	/*for (int i = 0; i < mesh->mNumVertices * 6; i++)
	{
		mesh->nIndexes[i] = 0;
	}*/

	// 6. Se rellena nIndexes
	// i recorre las muestras alrededor del eje Y
	//De alguna manera dejabamos alg�n indice suelto
	for (int i = 0; i < nn; i++)
	{
		// j recorre los vertices del perfil
		for (int j = 0; j < mm; j++)
		{
			// 7.
			//indice cuenta los indices generados hasta ahora
			const int indice = i * mm + j;

			mesh->nIndexes[indiceMayor] = indice;
			indiceMayor++;

			int n = (indice + mm) % (nn * mm);

			mesh->nIndexes[indiceMayor] = n;
			indiceMayor++;

			mesh->nIndexes[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;

			mesh->nIndexes[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;


			n = (indice + 1) % (nn * mm);

			mesh->nIndexes[indiceMayor] = n;
			indiceMayor++;

			mesh->nIndexes[indiceMayor] = indice % (nn * mm);
			indiceMayor++;

			/*
			�ndice0 , �ndice1 , �ndice2 ,
			�ndice2 , �ndice3 , �ndice0
			*/
		}
	}

	// 8. Construir los vectores normales y construir la malla.
	mesh->vNormals.reserve(mesh->mNumVertices);
	mesh->buildNormalVectors();

	/// DEBUG -> Dibuja las normales
	//for (int i = 0; i < mesh->mNumVertices; i++) {
	//	mesh->vColors.emplace_back(mesh->vNormals[i].x, mesh->vNormals[i].y, mesh->vNormals[i].z, 1);
	//}

	return mesh;
}

MbR* MbR::generatePartialIndexMbR(int mm, int nn, int grados, glm::dvec3* perfil)
{

	// mm: numero de puntos del perfil
	// nn: numero de rotaciones
	// perfil: perfil en el plano XY

	MbR* mesh = new MbR(mm, nn, perfil);	//Creamos la malla

	mesh->mPrimitive = GL_TRIANGLES;		//Primitiva [Exclusiva de Mallas Indexadas]
	mesh->mNumVertices = nn * mm;			//N�mero de v�rtices

	mesh->vVertices.reserve(mesh->mNumVertices);

	auto vs = new dvec3[mesh->mNumVertices];	//Vector auxiliar de v�rtices

	for (int i = 0; i < nn; i++)
	{
		//Genera la muestra i-�sima de v�rtices

		GLdouble theta = i * grados / (nn - 1);

		GLdouble c = cos(radians(theta));
		GLdouble s = sin(radians(theta));

		for (int j = 0; j < mm; j++)
		{
			GLdouble z = -s * perfil[j].x + c * perfil[j].z;
			GLdouble x = c * perfil[j].x + s * perfil[j].z;

			int Indice = i * mm + j;
			vs[Indice] = dvec3(x, perfil[j].y, z);
		}
	}

	// 4. Volcar el array auxiliar v�rtices en el array de v�rtices
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		mesh->vVertices.emplace_back(vs[i]);
	}
	delete[] vs;

	// 5. Construir los �ndices de las caras triangulares
	int indiceMayor = 0;
	mesh->nNumIndices = (nn - 1) * (mm - 1) * 6;
	mesh->nIndexes = new GLuint[mesh->nNumIndices];

	// Inicializamos nIndexes a 0
	/*for (int i = 0; i < mesh->mNumVertices * 6; i++)
	{
		mesh->nIndexes[i] = 0;
	}*/

	// 6. Se rellena nIndexes
	// i recorre las muestras alrededor del eje Y
	//De alguna manera dejabamos alg�n indice suelto
	for (int i = 0; i < nn - 1; i++)
	{
		// j recorre los vertices del perfil
		for (int j = 0; j < mm - 1; j++)
		{
			// 7.
			//indice cuenta los indices generados hasta ahora
			const int indice = i * mm + j;

			mesh->nIndexes[indiceMayor] = indice;
			indiceMayor++;

			int n = (indice + mm) % (nn * mm);

			mesh->nIndexes[indiceMayor] = n;
			indiceMayor++;

			mesh->nIndexes[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;

			mesh->nIndexes[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;


			n = (indice + 1) % (nn * mm);

			mesh->nIndexes[indiceMayor] = n;
			indiceMayor++;

			mesh->nIndexes[indiceMayor] = indice % (nn * mm);
			indiceMayor++;

			/*
			�ndice0 , �ndice1 , �ndice2 ,
			�ndice2 , �ndice3 , �ndice0
			*/
		}
	}

	// 8. Construir los vectores normales y construir la malla.
	mesh->vNormals.reserve(mesh->mNumVertices);
	mesh->buildNormalVectors();

	/// DEBUG -> Dibuja las normales
	//for (int i = 0; i < mesh->mNumVertices; i++) {
	//	mesh->vColors.emplace_back(mesh->vNormals[i].x, mesh->vNormals[i].y, mesh->vNormals[i].z, 1);
	//}

	return mesh;
}
#pragma endregion