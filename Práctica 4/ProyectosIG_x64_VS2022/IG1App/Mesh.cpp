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

		draw();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
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
	//glPolygonMode(GL_BACK, GL_POINT);					//Dibuja los puntos detras
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);					//Dibuja los puntos detras

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
	mesh->vColors.reserve(mesh->mNumVertices);			//reserva para el color

	GLdouble altura = -75; //apt 38
	GLdouble offset = 0; // 150; //199; //apt 38

	mesh->vVertices.emplace_back(-w/2, 0, -h / 2);
	mesh->vVertices.emplace_back(w/2, 0, -h / 2);
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

Mesh* Mesh::generateCube(GLdouble l)
{
	Mesh* mesh = new Mesh();					//Creamos una nueva malla
	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 14;							
	mesh->vVertices.reserve(mesh->mNumVertices);		//Reserva espacio para el número de vértices

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
	mesh->vVertices.reserve(mesh->mNumVertices);		//Reserva espacio para el número de vértices
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

	//Color
	//Automatización???
	//double r = -1.0;
	//double g = 1.0;
	//double b = 1.0;
	//for (int i = 0; i < 6; i++) {
	//	for (int j = 0; j < 6; j++) {
	//		mesh->vColors.emplace_back(r, g, b, 1.0);
	//	}
	//	r *= -1;
	//	g *= -1;
	//	//b *= -1;
	//}
	 
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
	Mesh* mesh = generateRectangle(w,h);
	mesh->vTexCoords.reserve(mesh -> mNumVertices);
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
	mesh->vVertices.reserve(mesh->mNumVertices);		//Reserva espacio para el número de vértices

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
	mesh->vVertices.reserve(mesh->mNumVertices);		//Reserva espacio para el número de vértices

	//lo que hace el triangle strip -> coge dos vertices anteriores para hacer el triangulo

	GLdouble a = w / 2;
	GLdouble b = h / 2;

	GLdouble altura = 0; // 150; //apt 38
	GLdouble offset = 0; // 150; //apt 38

	mesh->vVertices.emplace_back(a+offset, -b + altura, a + offset); //v0
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

	mesh->mPrimitive = GL_TRIANGLE_FAN;			//Hacemos que las lineas empiencen y terminen en el mismo punto??
	mesh->mNumVertices = 2*(np + 1);
	mesh->vVertices.reserve(mesh->mNumVertices);				//Reserva espacio para el número de vértices

	mesh->vVertices.emplace_back(0, 0, 0);						//Primer vértice (Centro) -Vertice en comun-
	
	//Primera estrella
	for (int i = 0; i < np; i++) {

		//Dividimos entre pares e impares (Unos están más arriba y otros más abajo)
		if (i % 2 == 0)	//Si es par
		{
			mesh->vVertices.emplace_back(re / 2 * cos(radians((360.0 / (np - 1)) * i + 90.0)), re / 2 * sin(radians((360.0 / (np - 1)) * i + 90)), h); //Se supone que pone el resto de vértices
		}
		else {
			mesh->vVertices.emplace_back(re / 4 * cos(radians((360.0 / (np - 1)) * i + 90.0)), re / 4 * sin(radians((360.0 / (np - 1)) * i + 90)), h); //Se supone que pone el resto de vértices
		}
	}

	//Colocamos el último en el mismo punto del primeros
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

Mesh* Mesh::generateWingAdvancedTIE(GLdouble tam)
{
	Mesh* mesh = new Mesh();						//Creamos una nueva malla
	mesh->mPrimitive = GL_TRIANGLE_STRIP;			//Podemos utilizar la primitiva que queramos

	mesh->mNumVertices = 7;							//Si no he contado mal son 7 y no se repite ninguno (No he tenido muy encuenta el sentido antihorario)
	mesh->vVertices.reserve(mesh->mNumVertices);

	//Tamaño utilizado para las alas
	GLdouble a = tam / 2;
	GLdouble b = tam / 4;

	//La distancia con el centro va a ser igual a "a" (Lo dejamos para luego el offset, Aun no se que parametros me hará falta pasarle)
	mesh->vVertices.emplace_back(a, -b, a); //v0
	mesh->vVertices.emplace_back(a, b, a); //v1
	mesh->vVertices.emplace_back(a, -b, -a); //v2

	mesh->vVertices.emplace_back(a, b, -a); //v3

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

		glColorMaterial(GL_FRONT_AND_BACK, GL_FILL);

		draw();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_INDEX_ARRAY);
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
	IndexMesh* mesh = new IndexMesh();

	// Elena mando un correo el 19 de abril diciendo como se hacia el cubo:

	mesh->mPrimitive = GL_TRIANGLES;

	/// VERTICES
	mesh->mNumVertices = 8;
	mesh->vVertices.reserve(mesh->mNumVertices);

	//vertices de la cara de detras
	mesh->vVertices.emplace_back(l, l, -l); // v0
	mesh->vVertices.emplace_back(l, -l, -l); // v1
	mesh->vVertices.emplace_back(-l, -l, -l); // v2
	mesh->vVertices.emplace_back(-l, l, -l); // v3
	//vertices de la cara de delante
	mesh->vVertices.emplace_back(l, l, l); // v4
	mesh->vVertices.emplace_back(l, -l, l); // v5
	mesh->vVertices.emplace_back(-l, -l, l); // v6
	mesh->vVertices.emplace_back(-l, l, l); // v7

	/// VECTOR DE INDICES
	mesh->nNumIndices = 36;
	mesh->nIndexes = new GLuint[mesh->nNumIndices];

	// cara de abajo
	mesh->nIndexes[0] = 0;
	mesh->nIndexes[1] = 3;
	mesh->nIndexes[2] = 2;

	mesh->nIndexes[3] = 0;
	mesh->nIndexes[4] = 2;
	mesh->nIndexes[5] = 1;

	// cara de arriba
	mesh->nIndexes[6] = 4;
	mesh->nIndexes[7] = 5;
	mesh->nIndexes[8] = 6;

	mesh->nIndexes[9] = 4;
	mesh->nIndexes[10] = 6;
	mesh->nIndexes[11] = 7;

	// cara lateral cercana izquierda
	mesh->nIndexes[12] = 0;
	mesh->nIndexes[13] = 4;
	mesh->nIndexes[14] = 7;

	mesh->nIndexes[15] = 0;
	mesh->nIndexes[16] = 7;
	mesh->nIndexes[17] = 3;

	// cara lateral trasera derecha
	mesh->nIndexes[18] = 1;
	mesh->nIndexes[19] = 2;
	mesh->nIndexes[20] = 6;

	mesh->nIndexes[21] = 1;
	mesh->nIndexes[22] = 6;
	mesh->nIndexes[23] = 5;

	// cara lateral cercana derecha
	mesh->nIndexes[24] = 0;
	mesh->nIndexes[25] = 1;
	mesh->nIndexes[26] = 5;

	mesh->nIndexes[27] = 0;
	mesh->nIndexes[28] = 5;
	mesh->nIndexes[29] = 4;

	// cara lateral trasera izquierda
	mesh->nIndexes[30] = 2;
	mesh->nIndexes[31] = 3;
	mesh->nIndexes[32] = 7;

	mesh->nIndexes[33] = 2;
	mesh->nIndexes[34] = 7;
	mesh->nIndexes[35] = 6;

	/// CARAS
	//int nV = 3;
	//mesh->vCaras.resize(mesh->nNumIndices / nV);
	//for (int i = 0; i < mesh->nNumIndices / nV; i++)
	//{
	//	//std::cout << mesh->vIndices[i * nV] << std::endl;
	//	//std::cout << mesh->vIndices[i * nV + 1] << std::endl;
	//	//std::cout << mesh->vIndices[i * nV + 2] << std::endl;

	//	mesh->vCaras[i] = Cara(
	//		mesh->nIndexes[i * nV],
	//		mesh->nIndexes[i * nV + 1],
	//		mesh->nIndexes[i * nV + 2]
	//	);
	//}

	/// COLORES
	mesh->vColors.reserve(mesh->mNumVertices);
	for (int i = 0; i < mesh->mNumVertices; i++)
		mesh->vColors.emplace_back(0, 1, 0, 1);

	/// NORMALES
	//mesh->buildNormalVectors();

	return mesh;
}

//glm::dvec3 IndexMesh::calculoVectorNormalPorNewell(Cara c)
//{
//	glm::dvec3 n = { 0, 0, 0 };
//	for (int i = 0; i < c.numeroVertices; i++)
//	{
//		const auto vertActual = vVertices[c.getIndice(i)];
//		const auto vertSiguiente = vVertices[c.getIndice((i + 1) % c.numeroVertices)];
//
//		n.x += (vertActual.y - vertSiguiente.y) * (vertActual.z + vertSiguiente.z);
//		n.y += (vertActual.z - vertSiguiente.z) * (vertActual.x + vertSiguiente.x);
//		n.z += (vertActual.x - vertSiguiente.x) * (vertActual.y + vertSiguiente.y);
//	}
//	return normalize(n);
//}
