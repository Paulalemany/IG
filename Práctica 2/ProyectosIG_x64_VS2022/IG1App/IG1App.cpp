#include "IG1App.h"
#include "CheckML.h"
#include <iostream>

using namespace std;

// static single instance (singleton pattern)

IG1App IG1App::s_ig1app; // default constructor (constructor with no parameters)

void
IG1App::close()
{
	if (!mStop) { // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop(); // stops main loop and destroy the OpenGL context
		mStop = true;        // main loop stopped
	}
	free();
}

//apartado 16
void IG1App::update()
{
	scenes[scene_index]->update();
	glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to
	// display()
}

void
IG1App::run() // enters the main event processing loop
{
	if (mWinId == 0) {      // if not initialized
		init();         // initialize the application
		glutMainLoop(); // enters the main event processing loop
		mStop = true;   // main loop has stopped
	}
}

void
IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	//glutIdleFunc(update);

	// create the scene after creating the context
	// allocate memory and resources
	mViewPort =
	  new Viewport(mWinW, mWinH); // glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera = new Camera(mViewPort);
	//mScene = new Scene;

	//Array de escenas
	for (int i = 0; i < MAX_SCENES; i++) {
		scenes[i] = new Scene;
	}

	//Objetos de escena 0 -> Figuras planas
	//scenes[0]->addObject(new RegularPolygon(glm::dvec4 (0,1,1,1), 3.0, 100.0));	//Tri�ngulo
	//scenes[0]->addObject(new RegularPolygon(glm::dvec4(1), 100.0, 200.0));		//Circunferencia
	//scenes[0]->addObject(new RGBTriangle(30.0));								//Tri�ngulo RGB
	//scenes[0]->addObject(new RegularRectangle(400.0, 200.0));					//Rect�ngulo L�nea
	//scenes[0]->addObject(new RGBRectangle(200.0, 100.0));						//Rect�ngulo RGB
	scenes[0]->addObject(new Ground(600.0, 600.0, "../BmpsP1/baldosaC.bmp"));					//Rect�ngulo origen

	//Objetos de escena 1 -> Figuras 3D
	//scenes[1]->addObject(new RegularCube(200.0));								//Cubo
	scenes[1]->addObject(new RGBCube(200.0));									//Cubo RGB
	
	
	mCamera->set2D();
	//mScene->init();

	//Iniciamos cada escena
	for (auto i : scenes) i->init();
}

void
IG1App::iniWinOpenGL()
{ // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE); // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);                   // GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(mWinW, mWinH);		// window size
	glutInitWindowPosition (140, 140);		//Cambia la posici�n en la que aparece la pantalla

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE |
	                    GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth
	                                                    // buffer and stencil buffer

	mWinId = glutCreateWindow(
	  "Paula al cuadrado"); // with its associated OpenGL context, return window's identifier

	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}

void
IG1App::free()
{ // release memory and resources
	//delete mScene;
	for (auto i : scenes) delete i;
	//mScene = nullptr;
	delete mCamera;
	mCamera = nullptr;
	delete mViewPort;
	mViewPort = nullptr;
}

void IG1App::setScene(int id)
{
	scene_index = id;
}

void
IG1App::display() const
{ // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer

	//mScene->render(*mCamera); // uploads the viewport and camera to the GPU
	scenes[scene_index]->render(*mCamera);

	glutSwapBuffers(); // swaps the front and back buffer
}

void
IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth;
	mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
}

void
IG1App::key(unsigned char key, int x, int y)
{
	bool need_redisplay = true;

	switch (key) {
		case 27:                     // Escape key
			glutLeaveMainLoop(); // stops main loop and destroy the OpenGL context
			break;
		case '+':
			mCamera->setScale(+0.01); // zoom in  (increases the scale)
			break;
		case '-':
			mCamera->setScale(-0.01); // zoom out (decreases the scale)
			break;
		case 'l':
			mCamera->set3D();
			break;
		case 'o':
			mCamera->set2D();
			break;
		case '0':
			setScene(0);
			break;
		case '1' :
			setScene(1);
			break;
		case 'u' :
			update();
			break;
		case 'U':
			glutIdleFunc(update);
			break;
		default:
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to
		                     // display()
}

void
IG1App::specialKey(int key, int x, int y)
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	switch (key) {
		case GLUT_KEY_RIGHT:
			if (mdf == GLUT_ACTIVE_CTRL)
				mCamera->pitch(-1); // rotates -1 on the X axis
			else
				mCamera->pitch(1); // rotates 1 on the X axis
			break;
		case GLUT_KEY_LEFT:
			if (mdf == GLUT_ACTIVE_CTRL)
				mCamera->yaw(1); // rotates 1 on the Y axis
			else
				mCamera->yaw(-1); // rotate -1 on the Y axis
			break;
		case GLUT_KEY_UP:
			mCamera->roll(1); // rotates 1 on the Z axis
			break;
		case GLUT_KEY_DOWN:
			mCamera->roll(-1); // rotates -1 on the Z axis
			break;
		default:
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to
		                     // display()
}
