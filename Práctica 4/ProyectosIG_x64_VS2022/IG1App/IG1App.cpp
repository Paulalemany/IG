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

void IG1App::update()
{
	int startTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (startTime - oldTimeStart) / 1000;
	oldTimeStart = startTime;

	timeToFrameUpdate += deltaTime;

	if (rotate) {
		mScene->rotate(deltaTime);
	}
	if (orbit) {
		mScene->orbit(deltaTime);
	}

	if (timeToFrameUpdate > timeToUpdate) {
		mScene->update();
		glutPostRedisplay();
	}
}

////apartado 16
//void IG1App::s_update()
//{
//	scenes[scene_index]->update();
//	glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to
//	// display()
//}

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
	mScene = new Scene;

	mCamera->set2D();
	mScene->init();

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
	glutInitWindowPosition(140, 140);		//Cambia la posición en la que aparece la pantalla

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

	//apt53
	glutMouseFunc(s_mouse);
	glutMotionFunc(s_motion);
	glutMouseWheelFunc(s_mouseWheel);

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
	mScene->setScene(id);
}

void
IG1App::display() const
{ // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer

	if (m2Vistas)
	{
		doubleViewport();
	}
	else 
	{
		mViewPort->setSize(mWinW, mWinH);
		mViewPort->setPos(0, 0);
		mScene->render(*mCamera); // uploads the viewport and camera to the GPU
	}

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
	case '1':
		setScene(1);
		break;
	case '2':
		setScene(2);
		break;
	case '3':
		setScene(3);
		break;
	case '4':
		setScene(4);
		break;
	case '5':
		setScene(5);
		break;
	case '6':
		setScene(6);
		break;
	case '7':
		setScene(7);
		break;
	case '8':
		setScene(8);
		break;
	case '9':
		setScene(9);
	case 'u':
		update();
		break;
	case 'U':
		glutIdleFunc(s_update);
		break;
	case 'p': //apt 44
		mCamera->changePrj();
		break;
	case 'k': //apt 51
		m2Vistas = !m2Vistas;
		break;
	/*case 'a':
		mCamera->moveLR(1);
		break;
	case 'd':
		mCamera->moveLR(-1);
		break;
	case 's':
		mCamera->moveUD(1);
		break;
	case 'w':
		mCamera->moveUD(-1);
		break;*/
	case 'f': //apt68
		orbit = !orbit;
		break;
	case 'g': //apt68
		rotate = !rotate;
		break;

		//luces
	case 'q':
		mScene->switchDirLight(true);
		break;
	case 'w':
		mScene->switchDirLight(false);
		break;

	case 'a':
		mScene->switchPosLight(true);
		break;
	case 's':
		mScene->switchPosLight(false);
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
		mCamera->rollReal(1);

		break;
	case GLUT_KEY_LEFT:
		if (mdf == GLUT_ACTIVE_CTRL)
			mCamera->yawReal(1);
		else
			mCamera->rollReal(-1);
		break;
	case GLUT_KEY_UP:
		mCamera->pitchReal(-1); //rota camara en su eje X
		break;
	case GLUT_KEY_DOWN:
		mCamera->pitchReal(1);
		break;
	default:
		need_redisplay = false;
		break;
	} // switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to
	// display()
}

void IG1App::doubleViewport() const
{
	Camera doubleCamera = *mCamera;	// Camara auxiliar copiando mCamera

	mViewPort->setSize(mWinW / 2, mWinH);
	doubleCamera.setSize(mViewPort->width(), mViewPort->height());

	//renderizamos la camara dos veces en distintas posiciones

	mViewPort->setPos(0, 0);
	mScene->render(doubleCamera);

	mViewPort->setPos(mWinW / 2, 0);
	doubleCamera.setCenital();
	mScene->render(doubleCamera);
}

void IG1App::mouse(int button, int state, int x, int y)
{
	//captura en mMouseCoord las coordenadas del raton (x,y), y en mMouseButt, el boton pulsado
	mInitialMouseCoord = glm::vec2(x, y); 
	mMouseButt = button;
}

void IG1App::motion(int x, int y)
{
	mMouseCoord = glm::vec2(x, y);

	if (mMouseButt == 0) //click izquierdo
	{
		//mueve la camara en sus ejes mRight(horizontal) y mUpward(vertical) el correspondiente desplazamiento
		mCamera->moveLR(mInitialMouseCoord.x - x);
		mCamera->moveUD(-mInitialMouseCoord.y + y);
	}
	else if (mMouseButt == 2) //click derecho
	{ 
		//rota la cámara alrededor de la escena.
		mCamera->orbit((mInitialMouseCoord.x - x) * 0.15, mInitialMouseCoord.y - y);
	}

	mInitialMouseCoord = mMouseCoord;

	glutPostRedisplay();
}

void IG1App::mouseWheel(int n, int d, int x, int y)
{
	//si no está pulsada ninguna tecla modificadora, desplaza la cámara en su dirección de vista(eje mFront), 
	//hacia delante / atrás según sea d positivo / negativo; si se pulsa la tecla Ctrl, escala la escena,
	//	de nuevo según el valor de d

	int auxmodifiers = glutGetModifiers();

	if (auxmodifiers == GLUT_ACTIVE_CTRL) //si se pulsa ctrl
	{
		mCamera->setScale(d * 0.01);
	}
	else if (auxmodifiers == 0) 
	{
		mCamera->moveFB(d * 5);
	}

	glutPostRedisplay();
}
