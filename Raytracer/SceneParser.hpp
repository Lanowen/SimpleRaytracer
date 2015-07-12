

#include "IFileHandle.hpp"
#include "Utils.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Cone.hpp"
#include "Plane.hpp"
#include "CirularPlane.hpp"

#include <string>
#include <limits>

using namespace std;

class SceneParser {

private:
	static Vec3 parseVector(IFileHandle& file){
		char c;
		Vec3 temp(0);

		while (file >> c){
			if (c == '('){
				file >> temp.x >> temp.y >> temp.z;
			}
			else if(c == ')'){
				return temp;
			}
		}

		return temp;
	}

public:

	static void parseScene(string filename, Scene& scene){
		IFileHandle file(filename);

		string tag;

		while(!file.eof()){
			file >> tag;

			if(tag == "//" || tag.find("//") != tag.npos){
				//do nothing
			}
			else if(tag == "colourmode"){
				string mode;
				file >> mode;

				if(mode == "solid"){
					scene.mode = Scene::solid;
				}
				else if(mode == "shaded"){
					scene.mode = Scene::shaded;
				}
				else if(mode == "normals"){
					scene.mode = Scene::normals;
				}
				else if(mode == "fullNormals"){
					scene.mode = Scene::fullNormals;
				}
			}
			else if(tag == "cone"){
				Vec3 position, direction, colour;
				double height, radius, diffuse, reflectivity;
				position = parseVector(file);
				file >> height >> radius;
				direction = parseVector(file);
				colour = parseVector(file);
				file >> diffuse >> reflectivity;
				scene.addShape(new Cone(direction, height, radius, position, colour, diffuse, reflectivity));
			}
			else if(tag == "sphere"){
				Vec3 position, colour;
				double radius, diffuse, reflectivity;
				position = parseVector(file);
				file >> radius;
				colour = parseVector(file);
				file >> diffuse >> reflectivity;
				scene.addShape(new Sphere(position, radius, colour, diffuse, reflectivity));
			}
			else if(tag == "plane"){
				Vec3 position, normal, colour;
				double diffuse, reflectivity;
				position = parseVector(file);
				normal = parseVector(file);
				colour = parseVector(file);
				file >> diffuse >> reflectivity;
				scene.addShape(new Plane(position, normal, colour, diffuse, reflectivity));
			}
			else if(tag == "circularplane"){
				Vec3 position, normal, colour;
				double radius, diffuse, reflectivity;
				position = parseVector(file);
				normal = parseVector(file);
				file >> radius;
				colour = parseVector(file);
				file >> diffuse >> reflectivity;
				scene.addShape(new CircularPlane(position, normal, radius, colour, diffuse, reflectivity));
			}
			else if(tag == "light"){
				Vec3 position, colour;
				double intensity;
				position = parseVector(file);
				file >> intensity;
				colour = parseVector(file);
				scene.addLight(new Light(position, intensity, colour));
			}

			file.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}



};