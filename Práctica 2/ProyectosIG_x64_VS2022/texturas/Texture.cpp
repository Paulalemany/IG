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

//Apt35
//cargue el buffer de color (frontal o trasero) dado por el tercer argumento, como una
//textura de dimensiones dadas por los par�metros primero y segundo.
void Texture::loadColorBuffer(GLsizei width, GLsizei height, GLuint buffer)
{
	glBindTexture(GL_TEXTURE_2D, mId);

	//CHAT GPT:
	// Leer el contenido del buffer de color y cargarlo en la textura
	//glReadBuffer(buffer);
	// Restaurar el buffer de lectura a su valor predeterminado (GL_FRONT)
	//glReadBuffer(GL_FRONT);


	glBindTexture(GL_TEXTURE_2D, 0);


	//CYNTHIA HA PUESTO ESTO AQUI�?:
	//Mesh::generateRectangleTexCor(width, height); 
}
