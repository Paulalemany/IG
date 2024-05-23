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
  glGenTextures(1, &mId); // Genera n=1 identificador y se guarda (en mId) para nueva textura

  //Filters and clamping / wrapping
  glBindTexture(GL_TEXTURE_2D, mId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // GL_CLAMP
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // GL_CLAMP
   
}
//-------------------------------------------------------------------------

void Texture::bind(GLuint mixMode) // GL_REPLACE, GL_MODULATE, GL_ADD
{
	glBindTexture(GL_TEXTURE_2D, mId); // activa la textura

	//[glTexEnvi] -> establecer parámetros de textura relacionados con el entorno de la textura,
	//				 afecta el estado global de OpenGL y no se almacena en el objeto de textura en sí
	glTexEnvi(GL_TEXTURE_ENV,          // configura el entorno de textura
			  GL_TEXTURE_ENV_MODE,	   // que parametro del entorno de textura se esta configurando (en este caso, mixMode)
			  mixMode);				   // modo de mezcla de colores que se desea establecer
}	
//-------------------------------------------------------------------------

void Texture::load(const std::string & BMP_Name, GLubyte alpha)
{
	if (mId == 0) init();
	
	PixMap32RGBA pixMap;	// Variable local para cargar la imagen del archivo.
							// Representación de una imagen donde cada píxel
							// está compuesto por 32 bits divididos en cuatro canales: Rojo, Verde, Azul y Alfa.
  
    pixMap.load_bmp24BGR(BMP_Name); // carga y añade alpha =255

    if (alpha != 255)
       pixMap.set_alpha(alpha);

	mWidth = pixMap.width();
	mHeight = pixMap.height();

    GLint level = 0;   //Base image level
	GLint border = 0;  //No border
	
	glBindTexture(GL_TEXTURE_2D, mId); 

	// Transfiere la imagen de CPU a GPU, e.d. pasa la imagen a la textura activa
    glTexImage2D(GL_TEXTURE_2D,		// puede ser tambien 1D o 3D
				level,				// mipmap level (no nos importa), nivel de detalle (poner 0 para un unico nivel) 
				GL_RGBA,			// Formato interno (GPU) de los datos de la textura	
				mWidth, mHeight,	// tamaño de la img (data), tienen que ser potencias de 2 (no necesariamente)
				border,				// booleano, indica si la imagen tiene borde
				GL_RGBA,			// formato de los datos de la imagen 
				GL_UNSIGNED_BYTE,	// tipo de datos de los datos de data 
				pixMap.data());		// array con la img que se quiere usar como textura, el formato se especifica y asi podra ser liberado
		
    glBindTexture(GL_TEXTURE_2D, 0);  // desactiva la textura (pone mId = 0)
}
//-------------------------------------------------------------------------

void Texture::setWrap(GLuint wp) // GL_REPEAT, GL_CLAMP
{
  glBindTexture(GL_TEXTURE_2D, mId);

  /// [glTexParameteri( GL_TEXTURE_2D , TipoProceso , Proceso );] *WRAPPING*
  // Especificamos independientemente para cada (s,t) de la textura:
  // -> Proceso: GL_CLAMP | GL_REPEAT (default)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wp);  // coordenada s
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wp);  // coordenada t

  glBindTexture(GL_TEXTURE_2D, 0); // activa la textura
}

//-------------------------------------------------------------------------

//Apt35 - diapo 36 de texturas
//cargue el buffer de color (frontal o trasero) dado por el tercer argumento, como una
//textura de dimensiones dadas por los parámetros primero y segundo.
void Texture::loadColorBuffer(GLsizei width, GLsizei height, GLuint buffer)
{
	if (buffer == GL_FRONT || buffer == GL_FRONT) //si el buffer es valido
	{
		//aseguramos que la textura esta inicializada
		if (mId == 0) init();

		mWidth = width;
		mHeight = height;

		//actualizamos el buffer al que queremos usar
		glReadBuffer(buffer);

		//enlazamos la textura, GL_MODULATE especifica como se combinarán los valores de la textura con los valores de fragmento
		bind(GL_MODULATE);

		// Copiar en la textura activa parte de la imagen del Color Buffer, los datos se copian del buffer de lectura activo (glReadBuffer)
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, width, height, 0); // en coordenadas de pantalla ( como el puerto de vista )

		/// Para obtener la imagen de la textura activa:
		// glGetTexImage(GL_TEXTURE_2D, level, format, type, pixels);
		// pixels - > array donde guardar los datos (de tipo y tamaño adecuado )
		
		//restaurar buffer (por defecto ya vendra por GL_BACK)
		glReadBuffer(GL_BACK);

		//liberamos la textura enlazada
		unbind();
	}
}
