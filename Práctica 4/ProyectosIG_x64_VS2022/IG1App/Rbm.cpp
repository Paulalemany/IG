#include "Rbm.h"

RbmSphere::RbmSphere(GLdouble r, GLint m, GLint p, int g)
{
	//r: radio de la esfera
	//p: puntos que tiene el perfil
	//m: revoluciones

	perfil = new glm::dvec3[p];

	//Variables para colocar los puntos
	const double alpha = 3.14 / (p - 1);	//�ngulo entre los puntos del perfil

	//Colocamos los puntos en el perfil
	for (int i = 0; i < p; i++)
	{
		perfil[i] = glm::dvec3(
			r * sin(alpha * i),
			r * cos(alpha * i),
			0 //Queremos que gire sobre este eje por lo que no debe cambiar
		);
	}

	//Una vez colocados creamos la malla
	//Depende de si es entera o no
	if (g == 360) mMesh = MbR::generateIndexMbR(p, m, perfil);
	else mMesh = MbR::generatePartialIndexMbR(p, m, g, perfil);
}

void RbmSphere::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		glm::dmat4 aMat = modelViewMat * mModelMat;	// glm matrix multiplication
		upload(aMat);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_COLOR_MATERIAL);

		if (mColor.a > 0.0)
			glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);

		if (material != nullptr) {
			glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
			material->upload();
		}
		
		mMesh->render();

		glColor4f(0, 0, 0, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (material != nullptr) {
			material->reset();
		}

		glDisable(GL_COLOR_MATERIAL);
	}
	
}

RbmToroid::RbmToroid(GLuint r, GLuint R, GLuint m, GLuint p, int g)
{
	// r: grosor de la rosquilla
	// R: radio de la rosquilla
	// m: numero de muestras
	// p: numero de puntos con que se aproxima la circunferencia
	// Perfil:
	// r: radio de la circunferencia
	// R: distancia del origen al centro de la circunferencia

	perfil = new glm::dvec3[p];

	/// PUNTOS DEL PERFIL
	for (int i = 0; i < p; i++)
	{
		//Variables para colocar los puntos
		const double alpha = (3.14 * 2 / (p - 1)) * i;	//�ngulo entre los puntos del perfil

		perfil[i] = { R + (r * sin(alpha)),	-(r * cos(alpha)), 0 };
	}

	//Depende de si es entera o no
	if (g == 360) mMesh = MbR::generateIndexMbR(p, m, perfil);
	else mMesh = MbR::generatePartialIndexMbR(p, m, g, perfil);
	
}

void RbmToroid::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glm::dmat4 aMat = modelViewMat * mModelMat;	// glm matrix multiplication
		upload(aMat);

		glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);

		mMesh->render();

		glColor4f(0, 0, 0, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

}

RbmPiramid::RbmPiramid(GLuint r, GLuint m, GLuint p)
{
	//r: radio de la esfera
	//p: puntos que tiene el perfil
	//m: numero de rotaciones que se va a dar

	perfil = new glm::dvec3[p];

	//Variables para colocar los puntos
	const double alpha = 3.14 / (p - 1);	//�ngulo entre los puntos del perfil

	//Colocamos los puntos en el perfil
	for (int i = 0; i < p; i++)
	{
		perfil[i] = glm::dvec3(
			r * sin(alpha * i),
			r * cos(alpha * i),
			0 //Queremos que gire sobre este eje por lo que no debe cambiar
		);
	}
}

void RbmPiramid::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glm::dmat4 aMat = modelViewMat * mModelMat;	// glm matrix multiplication
		upload(aMat);

		glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);

		mMesh->render();

		glColor4f(0, 0, 0, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
