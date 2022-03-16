#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene1.h"
#include "MMath.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

Scene1::Scene1()  {
	Debug::Info("Created Scene1: ", __FILE__, __LINE__);
}

Scene1::~Scene1() {
	Debug::Info("Deleted Scene1: ", __FILE__, __LINE__);
}

bool Scene1::OnCreate() {
	engineFail = false;
	time = 0.0f;
	timeTrack = 0.0f;
	torqueValue = 0.0f;
	Force = Vec3(50000000.0f, 0.0f, 0.0f);

	ship = new PhysicsObject(1000000.0f, 26700000000.0f);	
	ship->OnCreate();

	mesh = new Mesh(nullptr, "meshes/Normandy.obj");
	if (mesh->OnCreate() == false)
	{
		Debug::Error("Can't load Mesh()", __FILE__, __LINE__);
	}

	shader = new Shader(nullptr, "shaders/phongVert.glsl", "shaders/phongFrag.glsl");
	if (shader->OnCreate() == false)
	{
		Debug::Error("Shader failed to render", __FILE__, __LINE__);
	};

	texture = new Texture();
	if (texture->LoadImage("textures/NR2_InGame.png") == false)
	{
		Debug::Error("Can't load Normandy texture", __FILE__, __LINE__);
	};

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 6.5f), Vec3(0.0f, 0.0f, 0.0f), (Vec3(0.0f, 1.0f, 0.0f)));
	//viewMatrix.print();
	modelMatrix.loadIdentity();
	lightPos = Vec3(0.0f, 0.0f, 0.0f);


	Debug::Info("Loading assets Scene1: ", __FILE__, __LINE__);
	return true;
}	

void Scene1::OnDestroy() {
	ship->OnDestroy();
	delete ship;

	mesh->OnDestroy();
	delete mesh;

	shader->OnDestroy();
	delete shader;

	delete texture;


	Debug::Info("Deleting assets Scene1: ", __FILE__, __LINE__);
}

void Scene1::HandleEvents(const SDL_Event &sdlEvent) {
	switch( sdlEvent.type ) {
    case SDL_KEYDOWN:
		break;

	case SDL_MOUSEMOTION:          
		break;

	case SDL_MOUSEBUTTONDOWN:              
		break; 

	case SDL_MOUSEBUTTONUP:            
	break;

	default:
		break;
    }
}

void Scene1::Update(const float deltaTime) {
	
	time += deltaTime;	
		
	timeTrack += deltaTime;
	if (timeTrack >= 1.0) // calling the funcions and print statemens in every 60 frames, apprx in every 1 second.
	{
		ship->csv(time, torqueValue);

		//printf("Time, Torque, AngAccel, AngVel, Angle, Force.x, Force.y, Accel.x, Accel.y, Vel.x, Vel.y, Pos.x, Pos.y\n");			
		std::cout 
			<< std::setfill(' ') << std::setw(1) << "|" << std::setw(7) << std::left << "Time" << std::setprecision(2) << std::setw(1) << "|" << std::setw(10)
			<< "Torque" << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << "AngAccel" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< "AngVel" << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << "Angle" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< "Force.x" << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << "Force.y" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< "Accel.x" << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << "Accel.y" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< "Vel.x" << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << "Vel.y" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< "Pos.x" << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << "Pos.y" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12) 
			<< std::endl;

		/*printf("%f %f %f %f %f %f %f %f %f %f %f %f %f\n",Time, "torque", Ship->GetAngularAccel(), Ship->GetAngularVel(), Ship->GetAngle(), Ship->GetForce().x,
			Ship->GetForce().y, Ship->GetAccel().x, Ship->GetAccel().y, Ship->GetVel().x, Ship->GetVel().y, Ship->GetPos().x, Ship->GetPos().y);*/
		std::cout 
			<< std::setfill(' ') << std::setw(1) << "|" << std::setw(7) << std::left << time << std::setprecision(2) << std::setw(1) << "|" << std::setw(10)
			<< torqueValue << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << ship->GetAngularAccel() << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< ship->GetAngularVel() << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << ship->GetAngle() << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< ship->GetForce().x << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << ship->GetForce().y << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< ship->GetAccel().x << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << ship->GetAccel().y << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< ship->GetVel().x << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << ship->GetVel().y << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< ship->GetPos().x << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << ship->GetPos().y << std::setprecision(5) << std::setw(1) << "|" << std::setw(12) 
			<< std::endl;	
		timeTrack = 0.0f;
	}	

	// Calling all the functions!!!
	
	Physics::ApplyForce(Force, *ship);
	Physics::SimpleNewtonMotion(*ship, deltaTime);	

	if (time >= 5.0 && engineFail == false) { engineFail = true; Force.x *= 0.5; }

	if (engineFail == true) 
	{
		torqueValue = 629100000.0f;
		Physics::ApplyTorque(torqueValue, *ship);
		Physics::RigidBodyRotation(*ship, deltaTime);
		Force = Physics::rotateZ(Force, *ship);
	}

	if (time >= 35.0 && engineFail == true) { torqueValue = 0.0; Force = Vec3(0.0f, 0.0f, 0.0f); }

	modelMatrix =	MMath::translate(Vec3(-15, -5, 0)) *
					MMath::translate(ship->GetPos() * 0.0004) *
					MMath::rotate(ship->GetAngle() * RADIANS_TO_DEGREES, 0.0, 0.0, 1.0) *
					MMath::rotate(90, 1.0, 0.0, 0.0) *
					MMath::rotate(90, 0.0, 2.0, 0.0) *
					MMath::scale(0.4f, 0.4f, 0.4f);
}

void Scene1::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrix);
	glUniform3fv(shader->GetUniformID("lightPos"), 1, lightPos);
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	mesh->Render(GL_LINES);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}



	
