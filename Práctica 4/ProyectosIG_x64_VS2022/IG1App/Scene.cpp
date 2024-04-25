#include "Scene.h"
#include "CheckML.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;

void
Scene::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures
			//Creamos y cargamos todas las texturas que se van a utilizar
	Texture* baldosaC = new Texture();				//Suelo
	baldosaC->load("../BmpsP1/baldosaC.bmp");
	gTextures.push_back(baldosaC);

	Texture* container = new Texture();				//Caja exterior
	container->load("../BmpsP1/container.bmp");
	gTextures.push_back(container);

	Texture* papelE = new Texture();				//Caja interior
	papelE->load("../BmpsP1/papelE.bmp");
	gTextures.push_back(papelE);

	Texture* baldosaP = new Texture();				//Estrella
	baldosaP->load("../BmpsP1/baldosaP.bmp");
	gTextures.push_back(baldosaP);

	Texture* windowV = new Texture();				//Parapet
	windowV->load("../BmpsP1/windowV.bmp", 125);
	gTextures.push_back(windowV);

	Texture* noche = new Texture();					//Noche
	noche->load("../BmpsP1/noche.bmp");
	gTextures.push_back(noche);

	Texture* foto = new Texture();					//Foto
	foto->loadColorBuffer(800.0, 600.0);
	gTextures.push_back(foto);
	
	setScene(3);

}

void
Scene::free()
{ // release memory and resources

	for (Abs_Entity* el : gObjects) {
		delete el;
		el = nullptr;
	}

	for (Texture* t : gTextures) {
		delete t;
		t = nullptr;
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
	glEnable(GL_COLOR_MATERIAL);
}

void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
	glDisable(GL_TEXTURE_2D);
	glDisable(GLUT_MULTISAMPLE);
	glDisable(GL_COLOR_MATERIAL);
}

//Apt 56
void Scene::sceneDirLight(Camera const& cam) const
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
}

void
Scene::render(Camera const& cam) const
{
	sceneDirLight(cam); //Apt 56
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

void Scene::setScene(int i)
{
	QuadricEntity* eye = new Cylinder(20.0, 0.0);					//ojo der
	QuadricEntity* eye2 = new Cylinder(20.0, 0.0);					//ojo izq

	CompoundEntity* TIE;

	Abs_Entity* box = new IndexedBox(200.0);							//APT64

	switch (i)
	{
	case 0:
		//gObjects.push_back(new RegularCube(200.0));								//Cubo
		gObjects.push_back(new RGBCube(200.0));									//Cubo RGB
		break;
	case 1:
		// Graphics objects (entities) of the scene
		gObjects.push_back(new EjesRGB(400.0));
		//gObjects.push_back(new RegularPolygon(glm::dvec4 (0,1,1,1), 3.0, 100.0));						//Tri�ngulo
		//gObjects.push_back(new RegularPolygon(glm::dvec4(1), 100.0, 200.0));							//Circunferencia
		//gObjects.push_back(new RGBTriangle(30.0));													//Triangulo RGB
		//gObjects.push_back(new RegularRectangle(400.0, 200.0));										//Rectangulo L�nea
		//gObjects.push_back(new RGBRectangle(200.0, 100.0));											//Rectangulo RGB
		gObjects.push_back(new Ground(300.0, 300.0, 4, 4, gTextures[0]));								//Suelo
		gObjects.push_back(new BoxOutline(50.0, gTextures[1], gTextures[2]));							//Caja
		//gObjects.push_back(new Star(200.0, 17.0, 100.0, gTextures[3]));								//Estrella
		gObjects.push_back(new GlassParapet(300.0, 150.0, gTextures[4]));								//Parapet
		gObjects.push_back(new Photo(125.0, 70.0, gTextures[6]));										//Photo
		break;

	case 2:	//Apt 58
		gObjects.push_back(new Sphere(100.0));															//Esfera
		gObjects.push_back(new Disk(50.0, 150.0));														//Sombrero
		gObjects.push_back(new PartialDisk(70.0, 90.0, 0, 200));										//Sonrisa


		glm::dmat4 trans = translate(dmat4(1), dvec3(35, 30, 60));										//Ojos
		eye->setModelMat(trans);
		eye->QuadricColor(0, 0, 1);
		gObjects.push_back(eye);
		
		trans = translate(dmat4(1), dvec3(-35, 30, 60));
		eye2->setModelMat(trans);
		eye2->QuadricColor(0.6, 0.6, 0.6);
		gObjects.push_back(eye2);

		break;

	case 3: //Apt 60

		TIE = new AdvancedTIE();						//Entidad base

		TIE->setModelMat(
			translate(glm::dmat4(1.0), glm::dvec3(0, 1000, 0))
			* TIE->modelMat()
		);
		gObjects.push_back(TIE);
		break;
		
	case 4: //Apt 64
		gObjects.push_back(box);
		break;

	default:
		break;
	}
}

