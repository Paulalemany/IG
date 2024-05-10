#include "Light.h"

#include "Entity.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Light::Light()
{
	if (cont < GL_MAX_LIGHTS) {
		id = GL_LIGHT0 + cont;
		++cont;
		glEnable(id);
	}
}

	void Light::uploadL()
	{
		// Transfiere las características de la luz a la GPU
		glLightfv(id, GL_AMBIENT, value_ptr(ambient));
		glLightfv(id, GL_DIFFUSE, value_ptr(diffuse));
		glLightfv(id, GL_SPECULAR, value_ptr(specular));

	}
