#include "Toroid.h"

Toroid::Toroid(GLuint r, GLuint R, GLuint p, GLuint m) : Abs_Entity()
{
	// r: grosor de la rosquilla
	// R: radio de la rosquilla
	// m: numero de muestras
	// p: numero de puntos con que se aproxima la circunferencia

	// Perfil:
	// p = 12 
	// r: radio de la circunferencia
	// R: distancia del origen al centro de la circunferencia

	glm::dvec3* perfil = new glm::dvec3[p];

	//Variables para colocar los puntos
	const double alpha = 3.14 * 2 / (p - 1);	//ángulo entre los puntos del perfil

	//Colocamos los puntos en el perfil
	for (int i = 1; i < p; i++)
	{
		perfil[i] = glm::dvec3(
			cos(alpha * i) * r,
			sin(alpha * i) * r,
			0);
	}

	mMesh = MbR::generateIndexMbR(p, m, perfil);
}

Toroid::~Toroid()
{
	delete mMesh;
	mMesh = nullptr;
}

void Toroid::render(glm::dmat4 const& modelViewMat) const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glm::dmat4 aMat = modelViewMat * mModelMat;	// glm matrix multiplication
	upload(aMat);

	//set
	if (mColor.a > 0) {
		glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);
	}

	mMesh->render();

	//reset
	glColor3f(1.0, 1.0, 1.0);
	glColor4f(0, 0, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
