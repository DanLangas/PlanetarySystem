#include "FlyCamera.h"
#include "GLFW\glfw3.h">
#include <cstdio>
#include <list>
#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include "Input.h"
#include "Time.h"


FlyCamera::FlyCamera(double fov, double aspect, double zNear, double zFar) : Camera(fov, aspect, zNear, zFar)
{
	
}

void FlyCamera::OnRender(Display& display){
	//manage camera input
	ManageInput(display);
}

void FlyCamera::ManageInput(Display& display){
	//move the camera only if the mouse is visible
	if (!Input::MouseVisible){
		float speed = m_speed;

		m_velocity = glm::dvec3(0, 0, 0);

		//Shift Hyper speed
		if (glfwGetKey(display.GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
			speed = m_speed * 5;
		}

		m_velocity.x = Input::GetHorizontalInput(INPUT_SMOOTH) * speed * Time::GetDeltaTime(TIME_DLETA_SMOOTH);
		m_velocity.z = Input::GetVerticalInput(INPUT_SMOOTH) * speed  * Time::GetDeltaTime(TIME_DLETA_SMOOTH);

		m_viewRotation += Input::GetMouseDelta();

		glm::dquat HRotation = glm::angleAxis(m_viewRotation.x * m_sensitivity, glm::dvec3(0, 1, 0));
		glm::dquat VRotation = glm::angleAxis(m_viewRotation.y * m_sensitivity, glm::dvec3(1, 0, 0) * HRotation);


		transform.position += m_velocity * transform.rotation;
		transform.rotation = m_initialRotation * HRotation * VRotation;

		
	}
}


FlyCamera::~FlyCamera()
{
}
