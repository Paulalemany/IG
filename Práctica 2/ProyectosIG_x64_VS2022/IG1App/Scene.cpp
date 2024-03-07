#include "Scene.h"
#include "CheckML.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Scene::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new EjesRGB(400.0));
	//gObjects.push_back(new RegularPolygon(glm::dvec4 (0,1,1,1), 3.0, 100.0));						//Triángulo
	//gObjects.push_back(new RegularPolygon(glm::dvec4(1), 100.0, 200.0));							//Circunferencia
	//gObjects.push_back(new RGBTriangle(30.0));														//Triángulo RGB
	//gObjects.push_back(new RegularRectangle(400.0, 200.0));											//Rectángulo Línea
	//gObjects.push_back(new RGBRectangle(200.0, 100.0));												//Rectángulo RGB
	gObjects.push_back(new Ground(600.0, 600.0, 4, 4, "../BmpsP1/baldosaC.bmp"));					//Suelo
	//gObjects.push_back(new BoxOutline(200.0, "../BmpsP1/container.bmp","../BmpsP1/papelE.bmp" ));	//Caja
	//gObjects.push_back(new Star(200.0, 17.0, 100.0));												//Estrella
	//gObjects.push_back(new GlassParapet(200.0, 100.0, "../BmpsP1/windowV.bmp"));					//Parapet
	gObjects.push_back(new Photo(200.0, 100.0, "../BmpsP1/noche.bmp"));								//Photo
}
void
Scene::free()
{ // release memory and resources

	for (Abs_Entity* el : gObjects) {
		delete el;
		el = nullptr;
	}
}
void
Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0);; // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);          // enable Depth test
	glEnable(GL_TEXTURE_2D);
	glEnable(GLUT_MULTISAMPLE);
	glEnable(GL_BLEND);									// enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// enable Alpha channel
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
	glDisable(GL_TEXTURE_2D);
	glDisable(GLUT_MULTISAMPLE);
}

void
Scene::render(Camera const& cam) const
{
	cam.upload();

	for (Abs_Entity* el : gObjects) {
		el->render(cam.viewMat());
	}
}

void Scene::update()
{
	//Hace el update de cada objeto en la escena
	for (auto i : gObjects) i->update();
}

void Scene::addObject(Abs_Entity* e)
{
	gObjects.push_back(e);
}

