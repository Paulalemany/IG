#include "Texture.h"

//-------------------------------------------------------------------------

Texture::~Texture() 
{
	if(mId!=0)
    glDeleteTextures(1, &mId);
}
//-------------------------------------------------------------------------

void Texture::init()
{
  glGenTextures(1, &mId);
  glBindTexture(GL_TEXTURE_2D, mId);
 
  //Filters and clamping
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // GL_CLAMP
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // GL_CLAMP
   
}
//-------------------------------------------------------------------------

void Texture::bind(GLuint mixMode) // GL_REPLACE, GL_MODULATE, GL_ADD
{
  glBindTexture(GL_TEXTURE_2D, mId);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mixMode);  
}
//-------------------------------------------------------------------------

void Texture::load(const std::string & BMP_Name, GLubyte alpha)
{
	if (mId == 0) init();
	
	PixMap32RGBA pixMap;
  
    pixMap.load_bmp24BGR(BMP_Name);

    if (alpha != 255)
       pixMap.set_alpha(alpha);

	mWidth = pixMap.width();
	mHeight = pixMap.height();

    GLint level = 0;   //Base image level
	GLint border = 0;  //No border
	
	glBindTexture(GL_TEXTURE_2D, mId);
    glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, mWidth, mHeight, border, GL_RGBA, GL_UNSIGNED_BYTE, pixMap.data());
		
    glBindTexture(GL_TEXTURE_2D, 0); 
}
//-------------------------------------------------------------------------

void Texture::setWrap(GLuint wp) // GL_REPEAT, GL_CLAMP
{
  glBindTexture(GL_TEXTURE_2D, mId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wp);  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wp);  
  glBindTexture(GL_TEXTURE_2D, 0); 
}

//-------------------------------------------------------------------------

//Apt35 - diapo 36 de texturas
//cargue el buffer de color (frontal o trasero) dado por el tercer argumento, como una
//textura de dimensiones dadas por los parámetros primero y segundo.
void Texture::loadColorBuffer(GLsizei width, GLsizei height, GLuint buffer)
{
	if (buffer != GL_FRONT && buffer != GL_BACK) {
		return;
	}
	
	//tamaño de la textura
	mWidth = width;
	mHeight = height;

	//genera un nombre para la textura
	glGenTextures(1, &mId);

	//crea la textura y la activa
	glBindTexture(GL_TEXTURE_2D, mId);

	bind(GL_REPLACE);

	//modificar buffer
	GLenum format = GL_RGBA;
	if (buffer == GL_FRONT) {
		glReadBuffer(GL_FRONT);
	}
	else
		glReadBuffer(GL_BACK);


	//pasa imagen a la textura activa
	//glTexImage2D (GL_TEXTURE_2D, Level, GL_RGB [A], NCols, NFils, Border, GL_RGB[A], GL_UNSIGNED_BYTE, Data );
	//glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, );

	//restaurar buffer
	glReadBuffer(GL_BACK);

	unbind();

	//desactiva textura activa
	glBindTexture(GL_TEXTURE_2D, 0);
}
