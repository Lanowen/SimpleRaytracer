#include <iostream>
#include <algorithm>
#include <stack>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include "Scene.hpp"
#include "Sphere.hpp"
#include "Cone.hpp"
#include "Plane.hpp"
#include "CirularPlane.hpp"
#include <vector>
#include "SceneParser.hpp"
#include <future>
#include <thread>

using namespace std;

#define maxTravelDistance 7000
#define maxReflections 20
#define fadeDistance 500000.0f

void drawThreaded();

struct DrawPoint
{
	int x, y, i;
	Vec3 color;
	bool finished, processed;
};

mutex buffAccessTodo;
stack<std::reference_wrapper<DrawPoint>> screenBuffTodo;

vector<DrawPoint> screenBuffDone;

Vec3 camPos(0,0, -500);
Scene rayScene;
GLint m_viewport[4];

std::thread t1;
std::thread t2;
std::thread t3;
std::thread t4;
std::thread t5;
std::thread t6;
std::thread t7;
std::thread t8;
std::thread t9;
std::thread t10;
std::thread t11;
std::thread t12;

std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> timeStart;

// Initialization routine.
void setup()
{    
	glClearColor(0, 0, 0, 1.0); 
	glDisable(GL_DEPTH_TEST); 

	cout << "Specify scene filename (sceneData.txt):  ";
	string filename = "sceneData.txt";
	//cin >> filename;

	//SceneParser::parseScene("sceneData.txt", rayScene);	
	SceneParser::parseScene(filename, rayScene);	

	glClear(GL_COLOR_BUFFER_BIT);
	
	glGetIntegerv(GL_VIEWPORT, m_viewport);

	{
		screenBuffDone.resize(m_viewport[2] * m_viewport[3]);

		for(int x = 0; x < m_viewport[2]; x++)
		{
			for(int y = 0; y < m_viewport[3]; y++)
			{
				//screenBuffDone[x*m_viewport[3] + y].i = x*m_viewport[3] + y;
				screenBuffDone[x*m_viewport[3] + y].x = x - (m_viewport[2] >> 1);
				screenBuffDone[x*m_viewport[3] + y].y = y - (m_viewport[3] >> 1);

				screenBuffDone[x*m_viewport[3] + y].finished = false;
				screenBuffDone[x*m_viewport[3] + y].processed = false;
			}
		}

		//std::random_shuffle(screenBuffDone.begin(), screenBuffDone.end());

		for(unsigned int i = 0; i < screenBuffDone.size(); i++)
		{
			screenBuffDone[i].i = i;
			screenBuffTodo.push(screenBuffDone[i]);
		}
	}

	timeStart = std::chrono::high_resolution_clock::now();

	t1.swap(std::thread(drawThreaded));
	t2.swap(std::thread(drawThreaded));
	t3.swap(std::thread(drawThreaded));
	t4.swap(std::thread(drawThreaded));
	/*t5.swap(std::thread(drawThreaded));
	t6.swap(std::thread(drawThreaded));
	t7.swap(std::thread(drawThreaded));
	t8.swap(std::thread(drawThreaded));
	t9.swap(std::thread(drawThreaded));
	t10.swap(std::thread(drawThreaded));
	t11.swap(std::thread(drawThreaded));
	t12.swap(std::thread(drawThreaded));*/

	/*auto t1 = async(launch::async, drawThreaded);
	auto t2 = async(launch::async, drawThreaded);
	auto t3 = async(launch::async, drawThreaded);
	auto t4 = async(launch::async, drawThreaded);*/
	//auto t5 = async(launch::async, drawThreaded);
	//auto t6 = async(launch::async, drawThreaded);
	//auto t7 = async(launch::async, drawThreaded);
	//auto t8 = async(launch::async, drawThreaded);

	//y+ is down on screen, z+ is forward into screen

	//rayScene.addShape(new Sphere(Vec3(250, 0, 500), 250, Vec3(1,0,0), 0.8, 0.25));
	//rayScene.addShape(new Sphere(Vec3(-250, 0, 500), 250, Vec3(1,1,0), 0.2, 0.2));
	//rayScene.addShape(new Cone(Vec3(3, 2, 5), 100, 25, Vec3(0, 0, 100), Vec3(1,0,1), 0.8, 0));
	//rayScene.addShape(new Plane(Vec3(0,250, 0), Vec3(0,-1,0), Vec3(1,1,1), 0.5, 0.1));
	//rayScene.addShape(new Plane(Vec3(0,0, 3000), Vec3(0,0,-1), Vec3(0.1,1,0.1), 0.5, 0.2));
	////rayScene.addShape(new CircularPlane(Vec3(0,0, 100) - Vec3(1,2,5).getNormalized()*100, -Vec3(1,2,5).getNormalized(), 25, Vec3(1,0,0), 0.5, 0.2));

	///*rayScene.addShape(new Cone(Vec3(1, 0, 0), 100, 25, Vec3(50, 100, 0), Vec3(1,0,0), 0.8, 1.0));
	//rayScene.addShape(new Cone(Vec3(1, 0, 0), 100, 25, Vec3(0, 0, 0), Vec3(1,1,0), 0.8, 1.0));
	//rayScene.addShape(new Cone(Vec3(-1, 0, 0), 100, 25, Vec3(-50, -100, 0), Vec3(1,0,0), 0.8, 1.0));
	//rayScene.addShape(new Cone(Vec3(0, 1, 0), 100, 25, Vec3(0, 0, 0), Vec3(1,0,0), 0.8, 1.0));
	//rayScene.addShape(new Cone(Vec3(0,-1, 0), 100, 25, Vec3(0, 0, 0), Vec3(1,0,0), 0.8, 1.0));
	//rayScene.addShape(new Cone(Vec3(0, 0, 1), 100, 25, Vec3(0, 0, 0), Vec3(1,0,0), 0.8, 0));
	//rayScene.addShape(new Cone(Vec3(0, 0, -1), 100, 25, Vec3(0, 0, 0), Vec3(1,0,0), 0.8, 0));
	//rayScene.addShape(new Cone(Vec3(1, 0.5, -1), 100, 25, Vec3(0, 0, 0), Vec3(1,1,1), 0.8, 1.0));*/

	//rayScene.addShape(new Sphere(Vec3(200, 200, 0), 25, Vec3(1,0,0), 0.8, 0.2));

	//rayScene.addLight(new Light(Vec3(-250, -250, 100), 1, Vec3(1,1,1)));
	//rayScene.addLight(new Light(Vec3(150, 150, 100), 1, Vec3(0,1,1)));

	//rayScene.addLight(new Light(Vec3(100, -100, -200), 1, Vec3(1,1,1)));
}

void getColourRecursive(Ray& ray, Vec3& endColour, Vec3& tempColour, double& previousRelfec, double& reflec, double& distanceTravelled, int& numReflections){
	Vec3 point, normal, temp2;
	Shape* shape = NULL;
	double tempDis = 0;
	vector<pair<Light*, Vec3>> lightsHit;

	if(distanceTravelled < maxTravelDistance && rayScene.raycastAll(ray, point, normal, shape, tempDis)){	
		distanceTravelled += tempDis;
		//vector<pair<Light*,Vec3>>* lightsHit = new vector<pair<Light*,Vec3>>;

		//if check if lights are directly visible on surface point
		if(rayScene.lightcastAll(point, normal, lightsHit)){

			//iterate through all lights and set colour accordingly
			lightNormalPairItr lightsEnd = lightsHit.end();
			for(lightNormalPairItr itr = lightsHit.begin(); itr != lightsEnd; itr++){
				//doesn't work out too well, need to use HSB model maybe
				//temp2 = shape->colour.minimum(itr->first->colour) * shape->diffuse; //more realistic based lighting. Red illuminates red, green->green, blue->blue

				temp2 = shape->colour * shape->diffuse;


				double invSq = fadeDistance / powf(distanceTravelled, 2);

				//diffuse
				if(shape->diffuse > 0){
					//double luma = normal.dot(itr->second) * itr->first->intensity * invSq;
					double luma = itr->first->intensity * invSq;
					temp2 *= luma;
				}
						
				//specular
				if(shape->specular > 0){
					temp2 += itr->first->colour * pow(normal.dot(itr->second), 50) * shape->specular;
				}


				tempColour += temp2;

				if(previousRelfec > 0 && numReflections <  maxReflections && invSq > 1e-3){
					//delete lightsHit;
					//lightsHit = NULL;

					endColour+=tempColour*previousRelfec;

					reflec *= previousRelfec;
					previousRelfec = shape->reflection;

					ray = Ray(point, ray.direction - 2*ray.direction.dot(normal) * normal);

					tempColour = Vec3(0);
					numReflections++;

					return getColourRecursive(ray, endColour, tempColour, previousRelfec, reflec, distanceTravelled, numReflections);
				}
				else if (previousRelfec > 0){
					endColour+=tempColour*previousRelfec;
				}
			}
			//if(lightsHit)
			//	delete lightsHit;
		}
		
	}		
}

bool getColour(Ray& ray, Vec3& endColour, double& distanceTravelled) {
	Vec3 point, normal, tempColour;
	Shape* shape = NULL;
	double tempDis = 0;

	if(distanceTravelled < maxTravelDistance && rayScene.raycastAll(ray, point, normal, shape, tempDis)){	
		distanceTravelled += tempDis;
		vector<pair<Light*,Vec3>> lightsHit;
		
		if(rayScene.mode == Scene::shaded){
			endColour = Vec3(0);

			//if check if lights are directly visible on surface point
			if(rayScene.lightcastAll(point, normal, lightsHit)){

				//iterate through all lights and set colour accordingly
				lightNormalPairItr lightsEnd = lightsHit.end();
				for(lightNormalPairItr itr = lightsHit.begin(); itr != lightsEnd; itr++){
					//doesn't work out too well, need to use HSB model maybe
					//tempColour = shape->colour.minimum(itr->first->colour) * shape->diffuse; //more realistic based lighting. Red illuminates red, green->green, blue->blue

					tempColour = shape->colour * shape->diffuse;

					double invSq = fadeDistance / powf(distanceTravelled, 2);

					//diffuse
					if(shape->diffuse > 0){
						//double luma = normal.dot(itr->second) * itr->first->intensity * invSq;
						double luma = itr->first->intensity * invSq;
						tempColour *= luma;
					}
						
					//specular
					if(shape->specular > 0){
						tempColour += itr->first->colour * pow(normal.dot(itr->second), 50) * shape->specular;
					}


					endColour += tempColour;

					if(shape->reflection > 0){
						/*if(getColour(Ray(point, ray.direction - 2*ray.direction.dot(normal) * normal), tempColour, distanceTravelled))
							endColour += tempColour * shape->reflection;*/

						tempColour = Vec3(0);
						Vec3 otherEnd(0);
						double reflec = shape->reflection, otherReflec = 1;
						int numReflections = 1;
						Ray otherRay = Ray(point, ray.direction - 2.0*ray.direction.dot(normal) * normal);

						getColourRecursive(otherRay, otherEnd, tempColour, reflec, otherReflec, distanceTravelled, numReflections);
						endColour += otherEnd;
					}
				}
			}

			//make sure everything is cool, no element over 1
			endColour = endColour.minimum(Vec3(1,1,1));
		}
		else if(rayScene.mode == Scene::solid){
			endColour = shape->colour;
		}
		else if(rayScene.mode == Scene::normals){
			endColour = Vec3((normal.x + 1)/2.0, (normal.y + 1)/2.0, abs(normal.z));
		}
		else if(rayScene.mode == Scene::fullNormals){
			endColour = Vec3((normal.x + 1)/2.0, (normal.y + 1)/2.0, (normal.z + 1)/2.0); //shows reverse z also
		}

		return true;
	}

	return false;
}

void drawThreaded()
{
	double distance;
	Ray ray(camPos, camPos);

	while(true)
	{
		buffAccessTodo.lock();
		if(screenBuffTodo.size() == 0)
		{
			buffAccessTodo.unlock();
			return;
		}
		DrawPoint& dp = screenBuffTodo.top();
		screenBuffTodo.pop();
		buffAccessTodo.unlock();

		Vec3& endColour = dp.color;
		endColour.x = 0;
		endColour.y = 0;
		endColour.z = 0;

		distance = 0;
		ray.setDirection(Vec3(dp.x, dp.y, 0) - camPos);

		getColour(ray, endColour, distance);

		//buffAccessDone.lock();
		screenBuffDone[dp.i].color = endColour;
		screenBuffDone[dp.i].finished = true;
		//buffAccessDone.unlock();

		std::this_thread::yield();
		//std::this_thread::sleep_for(std::chrono::nanoseconds(1));
	}
}

// Drawing routine.
void drawScene(void)
{
	bool bFlushable = false;

	static int i = screenBuffDone.size()-1;
	
	for(; i >= 0; i--)
	{
		if(!screenBuffDone[i].finished)// || screenBuffDone[i].processed)
		{
			break;
		}

		bFlushable = true;

		DrawPoint& dp = screenBuffDone[i];

		dp.processed = true;

		glColor3dv(&dp.color.x);

		glBegin(GL_POINTS);
		glVertex2f(dp.x + (m_viewport[2] >> 1), dp.y + (m_viewport[3] >> 1));

		glEnd();
	}

	if(i == -1)
	{
		std::cout << "Scene took: " << std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::high_resolution_clock::now() - timeStart)).count()/1000.0 << " seconds to render." << std::endl;
		i--;//dumb
	}

	if(bFlushable)
	{
		glFlush();

		bFlushable = false;
	}
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho (0, (GLsizei)w, (GLsizei)h, 0, 0, 1);
	//glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch(key) 
	{
		case 27:
			exit(0);
		default:
			break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
}

void updateGame()
{
	glutPostRedisplay();
}

// Main routine.
int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ridge Racer");
	setup();
	glutDisplayFunc(drawScene);
	glutIdleFunc(updateGame);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);
	glutMainLoop();

	return 0; 
}
