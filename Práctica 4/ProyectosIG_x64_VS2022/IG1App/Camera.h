#ifndef _H_Camera_H_
#define _H_Camera_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Viewport.h"

class Camera
{
public:
	explicit Camera(Viewport* vp);
	~Camera() = default;

	// viewPort
	Viewport const& viewPort() const { return *mViewPort; };

	// view matrix
	glm::dmat4 const& viewMat() const { return mViewMat; };

	void set2D();
	void set3D();
	
	//apt50
	void setCenital();

	void pitch(GLdouble a); // rotates a degrees on the X axis
	void yaw(GLdouble a);   // rotates a degrees on the Y axis
	void roll(GLdouble a);  // rotates a degrees on the Z axis

	//apt 46 -> hay demos en el campus virtual 
	//métodos para rotar la cámara en cada uno de sus ejes u, v y n :
	void pitchReal(GLdouble cs);
	void yawReal(GLdouble cs);
	void rollReal(GLdouble cs);

	// projection matrix
	glm::dmat4 const& projMat() const { return mProjMat; };

	// sets scene visible area size
	void setSize(GLdouble xw, GLdouble yh);
	// updates the scale factor
	void setScale(GLdouble s);

	// transfers its viewport, the view matrix and projection matrix to the GPU
	void upload() const
	{
		mViewPort->upload();
		uploadVM();
		uploadPM();
	};

	//APT 41
	void moveLR(GLdouble cs);
	void moveFB(GLdouble cs);
	void moveUD(GLdouble cs);

	//APT 42
	void changePrj();
	
	//APT 48
	void orbit(GLdouble incAng, GLdouble incY);

protected:
	glm::dvec3 mEye = {0.0, 0.0, 500.0}; // camera's position
	glm::dvec3 mLook = {0.0, 0.0, 0.0};  // target's position

	glm::dvec3 mUp = {0.0, 1.0, 0.0};    // the up vector

	//apt39
	glm::dvec3 mRight;    // the right vector (U)
	glm::dvec3 mUpward;    // the upward vector (V)
	glm::dvec3 mFront;    // the front vector (N)

	glm::dmat4 mViewMat;   // view matrix = inverse of modeling matrix					 MATRIZ DE VISTA?? APT40
	void uploadVM() const; // transfers viewMat to the GPU

	glm::dmat4 mProjMat;   // projection matrix
	void uploadPM() const; // transfers projMat to the GPU

	GLdouble xRight, xLeft, yTop, yBot;     // size of scene visible area
	GLdouble mNearVal = 1, mFarVal = 10000; // view volume
	GLdouble mScaleFact = 1;                // scale factor
	bool bOrto = true;                      // orthogonal or perspective projection

	Viewport* mViewPort; // the viewport

	glm::dvec3 row(glm::dmat4 matrix, int index); //apt39

	void setVM();
	void setPM();
	void setAxes(); //apt39

	//apt48 y diapo18 - radio y angulo de la circunferencia
	GLdouble mRadio = 0;
	GLdouble mAng = 0;
};

#endif //_H_Camera_H_
