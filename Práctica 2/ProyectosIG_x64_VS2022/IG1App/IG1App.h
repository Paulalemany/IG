#ifndef _H_IG1App_H_
#define _H_IG1App_H_

// #include <gl/GL.h>    // OpenGL
// #include <gl/GLU.h>   // OpenGL Utility Library
// #include <GL/glut.h>  // OpenGL Utility Toolkit

#include <array>
#include <GL/freeglut.h> // OpenGL Utility Toolkit
#include <glm/glm.hpp>   // OpenGL Mathematics

#include "Camera.h"
#include "Scene.h"
#include "Viewport.h"

//Por ahora solo tenemos dos escenas
static const int MAX_SCENES = 2;

static int scene_index = 0;
//Creamos un array con todas las escenas
static std::array<Scene*, MAX_SCENES> scenes;

class IG1App
{
public:
	// static single instance (singleton pattern)
	static IG1App s_ig1app;

	IG1App(IG1App const& J) = delete;         // no copy constructor
	void operator=(IG1App const& J) = delete; // no copy assignment

	// Viewport position and size
	Viewport const& viewPort() { return *mViewPort; };
	// Camera position, view volume and projection
	Camera const& camera() { return *mCamera; };
	// Graphics objects of the scene
	//Scene const& scene() { return *mScene; };

	void run();   // the main event processing loop
	void close(); // the application
	void update();

protected:
	IG1App() {};
	~IG1App() { close(); };

	void init();
	void iniWinOpenGL();
	void free();
	void setScene(int id);

	void display() const;                      // the scene
	void resize(int newWidth, int newHeight);  // the viewport (without changing the scale)
	void key(unsigned char key, int x, int y); // keypress event
	void specialKey(int key, int x, int y);    // keypress event for special characters

	// static callbacks
	static void s_display() { s_ig1app.display(); };
	static void s_resize(int newWidth, int newHeight) { s_ig1app.resize(newWidth, newHeight); };
	static void s_key(unsigned char key, int x, int y) { s_ig1app.key(key, x, y); };
	static void s_specialKey(int key, int x, int y) { s_ig1app.specialKey(key, x, y); };
	static void s_update() { s_ig1app.update(); };

	// Viewport position and size
	Viewport* mViewPort = nullptr;
	// Camera position, view volume and projection
	Camera* mCamera = nullptr;
	Scene* mScene = nullptr;

	bool mStop = false; // main event processing loop
	int mWinId = 0;     // window's identifier
	int mWinW = 800;    // window's width
	int mWinH = 600;    // window's height
};

#endif //_H_IG1App_H_