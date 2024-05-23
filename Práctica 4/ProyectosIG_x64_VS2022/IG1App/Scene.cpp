#include "Scene.h"
#include "CheckML.h"
#include <iostream>
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
	setLights();
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
	
	setScene(6);

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
	
	/// [ Blending ] 
	// Que es? -> proceso de combinar colores de la fuente (src) y el destino (dst) para lograr efectos visuales como transparencia.
	// Ecuacion -> dstColor = srcBFactor * srcColor + dstBFactor * dstColor 
					// donde:
					//  · srcColor = (srcR, srcG, srcB, srcA) el color RGBA del fragmento en proceso,
					//  · dstColor = (dstR, dstG, dstB, dstA) el color del Color Buffer correspondiente al mismo pixel
					//  · srcBFactor y dstBFactor los correspondientes factores de blending.
					// Usamos para esto glBlendFunc(srcBFactor, dstBFactor).
					 
	// glBlendFunc(GL_ONE, GL_ZERO) es el valor por defecto
	// glBlendFunc(GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR) modula cada canal conu n peso constante fijado con glBlendColor(r, g, b, a)
	// glBlendFunc(GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA) solo usa el valor a para todos los canales
	/// ------------


	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);			  // activar la iluminacion
}

void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
	glDisable(GL_TEXTURE_2D);
	glDisable(GLUT_MULTISAMPLE);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ZERO);
	glDisable(GL_LIGHTING);
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
	//sceneDirLight(cam); //Apt 56
	cam.upload();
	//luz
	dirLight->upload(cam.viewMat());
	posLight->upload(cam.viewMat());
	spotLight->upload(cam.viewMat());
	

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
	deleteObjects();
	mId = i;

#pragma region Creación de objetos
	QuadricEntity* eye = new Cylinder(20.0, 0.0, 50);					//ojo der
	QuadricEntity* eye2 = new Cylinder(20.0, 0.0, 50);					//ojo izq

	QuadricEntity* cabeza = new Sphere(100.0); //cabeza
	cabeza->QuadricColor(1, 0, 0);

	TIE = new AdvancedTIE();

	//Apt64
	Abs_Entity* box = new IndexedBox(200.0);

	//Apt66
	CompoundEntity* node = new CompoundEntity();
	RGBTriangle* triangle = new RGBTriangle(30);

	node->addEntity(triangle);
	triangle->setModelMat(glm::translate(node->modelMat(), glm::dvec3(200, 0, 0)));


	//Apt 67
	QuadricEntity* tatooine = new Sphere(200.0);
	tatooine->QuadricColor(1, 255 / 233, 0);

	//apt 71
	RbmSphere* rbmSphere = new RbmSphere(100, 10, 20);

	//apt 72
	RbmToroid* rbmToroid = new RbmToroid(50, 100, 30, 20);

	gObjects.push_back(new EjesRGB(400.0));

	//apt74
	RbmSphere* tatooineColor = new RbmSphere(100, 10, 20);
	RbmSphere* tatooineMaterial = new RbmSphere(100, 10, 20);
	Material* goldMaterial = new Material();

#pragma endregion

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

		gObjects.push_back(cabeza);																		//Esfera
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
		
		gObjects.push_back(TIE);
		break;
		
	case 4: //Apt 64
		gObjects.push_back(box);
		break;

	case 5: //APT 66

		gObjects.push_back(new RegularPolygon(glm::dvec4(1), 100.0, 200.0));
		gObjects.push_back(new RGBRectangle(200, 100));
		gObjects.push_back(triangle);

		break;

	case 6: //APT 67

		gObjects.push_back(tatooine); // Añadimos el planeta

		//Inicializamos los nodos ficticios
		inventedNode = new CompoundEntity();		// Nodo para la translacion
		inventedNodeRotate = new CompoundEntity();	// Nodo para la rotacion

		TIE->setModelMat(
			scale(dmat4(1), dvec3(0.3, 0.3, 0.3))
			* translate(dmat4(1), dvec3(-100.0, 620.0, -100.0))
			* TIE->modelMat()
		);

		gObjects.push_back(TIE);

		inventedNode->addEntity(TIE);
		inventedNodeRotate->addEntity(TIE);

		break;

	case 7:
		/*rbmSphere->setColor(dvec4(0, 0, 1, 1));
		gObjects.push_back(rbmSphere);*/

		rbmToroid->setColor(dvec4(0, 1, 0, 1));
		gObjects.push_back(rbmToroid);
		break;

	case 8:
		tatooineColor->setColor(dvec4(1, 1, 0, 1));
		tatooineColor->setModelMat(
			translate(dmat4(1), dvec3(200, 0, 0))
		);
		gObjects.push_back(tatooineColor);

		goldMaterial->setGold();
		tatooineMaterial->setMaterial(goldMaterial);
		tatooineMaterial->setModelMat(
			translate(dmat4(1), dvec3(0, 0, 200))
		);
		gObjects.push_back(tatooineMaterial);
		break;

	case 9:
		
		break;

	default:
		break;
	}

	if (i == 6) {
		glClearColor(0, 0, 0, 1);
	}
	else {
		glClearColor(0.6, 0.7, 0.8, 1);
	}
}

void Scene::deleteObjects()
{
	for (Abs_Entity* el : gObjects) {
		delete el;
		el = nullptr;
	}

	gObjects.resize(0);
}

void Scene::orbit(float time)
{
	//Si estamos en la escena correcta
	if (mId == 6) {

		//Lo hacemos con el método del nodo inventado
		//Colocamos la entidad encima del nodo (Ambos vectores deben ser iguales??)
		TIE->setModelMat(
			translate(inventedNode->modelMat(), dvec3(0, 0, 0))
			* TIE->modelMat()
		);

		//Colocamos la luz
		//TIELight->setPosDir(inventedNode->modelMat());

		//Hay que girarlo y moverlo
		dvec3 direction = glm::normalize(glm::dvec3(TIE->modelMat() * glm::dvec4(0.0, 0.0, 1.0, 0.0)));
		inventedNode->setModelMat(
			glm::rotate(dmat4(1), radians(-0.3), direction)
		);

	}
}

void Scene::rotate(float time)
{
	//habria que ver cual es el tie para darle el setRot
	if (mId == 6) {

		//Necesito que siempre rote sobre si mismo
		// coloca la entidad justo encima del nodo
		TIE->setModelMat(
			translate(inventedNodeRotate->modelMat(), dvec3(0, 0, 0))
			* TIE->modelMat()
		);

		dvec3 eje = glm::normalize(glm::dvec3(TIE->modelMat() * glm::dvec4(0.0, 1.0, 0.0, 0.0)));
		inventedNodeRotate->setModelMat(
			glm::rotate(dmat4(1), radians(-0.5), eje)
		);
	}
}

void Scene::setLights()
{
	dirLight = new DirLight();
	dirLight->setAmb(glm::fvec4(0.0, 0.0, 0.0, 1.0));
	dirLight->setDiff(glm::fvec4(1.0, 1.0, 1.0, 1.0));
	dirLight->setSpec(glm::fvec4(0.5, 0.5, 0.5, 1.0));
	dirLight->setPosDir(glm::fvec3(1, 1, 1));
	dirLight->setId(GL_LIGHT0);

	posLight = new PosLight();
	posLight->setAmb(glm::fvec4(0.0, 0.0, 0.0, 1.0));
	posLight->setDiff(glm::fvec4(1.0, 1.0, 0.0, 1.0));
	posLight->setSpec(glm::fvec4(0.5, 0.5, 0.5, 1.0));
	posLight->setPosDir(glm::fvec3(100.0, 1500.0, 0));
	posLight->setId(GL_LIGHT1);

	spotLight = new SpotLight();
	spotLight->setAmb(glm::fvec4(0.0, 0.0, 0.0, 1.0));
	spotLight->setDiff(glm::fvec4(1.0, 1.0, 1.0, 1.0));
	spotLight->setSpec(glm::fvec4(0.5, 0.5, 0.5, 1.0));
	spotLight->setPosDir(glm::fvec3(0, 300.0, 3000.0));
	spotLight->setId(GL_LIGHT2);

	TIELight = new PosLight();
	TIELight->setAmb(glm::fvec4(0.0, 0.0, 0.0, 1.0));
	TIELight->setDiff(glm::fvec4(1.0, 1.0, 0.0, 1.0));
	TIELight->setSpec(glm::fvec4(0.5, 0.5, 0.5, 1.0));
	TIELight->setId(GL_LIGHT3);
	//Ahora en el 0,0,0, en el update lo pondremos con el nodo ficticio
	TIELight->setPosDir(glm::fvec3(0, 0, 0));
}

