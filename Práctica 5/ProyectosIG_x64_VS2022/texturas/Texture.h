//#pragma once
#ifndef _H_Texture_H_
#define _H_Texture_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Pixmap32RGBA.h"
#include <string>

//-------------------------------------------------------------------------

class Texture
{
public:
  Texture(){};
  ~Texture();

  Texture(const Texture & tex) = delete;  // no copy constructor
  Texture & operator=(const Texture & tex) = delete;  // no copy assignment

  void load(const std::string & BMP_Name, GLubyte alpha = 255); // load from file and upload to GPU
  
  void bind(GLuint mixMode);   // GL_REPLACE, GL_MODULATE, GL_ADD, ...
  void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); };

  GLuint width() const { return mWidth; };
  GLuint height() const { return mHeight; };
  
  void setWrap(GLuint wp);  // GL_REPEAT, GL_CLAMP 
  void loadColorBuffer(GLsizei width, GLsizei height, GLuint buffer = GL_FRONT); //buffer = GL_FRONT o GL_BACK

protected:

  void init();
  
  GLuint mWidth = 0;
  GLuint mHeight = 0;
  GLuint mId = 0;
  
};

/// Textura procedimental 
//(en vez de una imagen, colores, de tipo double)

// Ejemplo con un circulo. 
// Los puntos dentro del radio delcírculo(r) son más oscuros en elborde (d = r) y más claros en el centro(d = 0.0)
// 
//double TexturaProc(double s, double t) { // en [0 ,1]
//	double r = 0.4; // radio
//	// distancia al centro
//	double d = sqrt((s - 0.5) * (s - 0.5) + (t - 0.5) * (t - 0.5));
//	if (d < r) return 1 - (d / r); // intensidad del círculo
//	else return 0.2; // background
//}



#endif //_H_Texture_H_

