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

  // Carga del archivo una imagen y la transfiere al GPU
  void load(const std::string & BMP_Name, GLubyte alpha = 255); // load from file and upload to GPU
  
  // Metodos para activar/desactivar la textura en la GPU
  void bind(GLuint mixMode);   // GL_REPLACE, GL_MODULATE, GL_ADD, ... (*)
  void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); };

  /// (*) Mezcla de textura con el color
  // Cada fragmento de un triangulo contiene las coordenadas (x,y) de un pixel, un color C, y las coordenadas de textura (s,t).
  // El color C se mezcla con el color de la textura, hay distintas formas de combinar estos colores:
  // -> GL_REPLACE: Utiliza exclusivamente la textura: C = T(s,t)
  // -> GL_MODULATE: Modula ambos colores : C = C * T(s, t).
  // -> GL_ADD : Suma ambos colores : C = C + T(s, t).
  // El color resultante se escribira en el Color Buffer. 

  GLuint width() const { return mWidth; };
  GLuint height() const { return mHeight; };
  
  /// Texture Wrapping: ¿Qué se hace cuando las coordenadas de textura caen fuera del rango[0, 1] ?
  // -> GL_REPEAT: la textura se repite (tiling). Se ignora la parte entera de las coordenadas de textura. 
  // -> GL_CLAMP: coordenadas de textura superiores a 1 se ajustan a 1, y las coordenadas inferiores a 0 se ajustan a 0.
  // Para esto usamos el metodo:
  void setWrap(GLuint wp);  // GL_REPEAT, GL_CLAMP 
  
  void loadColorBuffer(GLsizei width, GLsizei height, GLuint buffer = GL_FRONT); //buffer = GL_FRONT o GL_BACK

protected:

  void init();

  // dimensiones de la imagen
  GLuint mWidth = 0, mHeight = 0; 

  // identificador interno (GPU) de la textura.
  GLuint mId = 0; // se inicializa en 0, no hay ninguna textura asociada al principio
  // La función glGenTextures genera un nuevo identificador de textura y lo almacena en mId. 
  // Este identificador sera válido.
  // En bind() se verifica si mId es distinto de 0.
				
  
};

/// [ Textura procedimental ]
//(en vez de una imagen, colores, de tipo double)

// Ejemplo con un circulo. 
// Los puntos dentro del radio delcírculo(r) son más oscuros en elborde (d = r) y más claros en el centro(d = 0.0)

	//double TexturaProc(double s, double t) { // en [0 ,1]
	//	 double r = 0.4; // radio
	//	 // distancia al centro
	//	 double d = sqrt((s - 0.5) * (s - 0.5) + (t - 0.5) * (t - 0.5));
	//	 if (d < r) return 1 - (d / r); // intensidad del círculo
	//	 else return 0.2; // background
	//}

/// [ Filtros ]
// En caso de tener que aumentar o reducir la imagen durante el renderizado, se pueden aplicar filtros.
// · Un téxel para varios píxeles -> gl.TEXTURE_MAG_FILTER (hara la imagen mas grande)
// · Varios téxeles para un píxel -> gl_TEXTURE_MIN_FILTER (mas pequeña)

/// [ Aplicacion de textura a una malla ]
// Mapping.
// 
// -> A cada vértice hay que asignarle sus coordenadas de textura (s,t) añadiendo a la clase
// Mesh un vector de coordenadas de textura	(std::vector<glm::dvec2> vTexCoords;)
// -> El método Mesh::render() tiene que activar (y desactivar) el array de coordenadas de textura:
		// glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		// glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
// -> Añadimos una nueva clase, Texture, con métodos para cargar de archivo una imagen y
// transferirla a la GPU(load), y para activar(bind) y desactivar(unbind) la textura en la GPU.
// -> Añadimos a la clase Abs_Entity un atributo para la textura (Texture* mTexture), que
// habrá que establecer al crear la entidad (método setTexture), y activar / desactivar al
// renderizarla.



/// (*) Texturas 2D en OpenGL
// Las texturas se gestionan por objetos de textura, son estructuras GPU que contienen la imagen
// y la configuracion de la textura (filtros, wrapping, pero no el modo de mezcla (ver en Texture::bind)). 

// [ Gestion de objetos de texturas ]
// 



#endif //_H_Texture_H_

