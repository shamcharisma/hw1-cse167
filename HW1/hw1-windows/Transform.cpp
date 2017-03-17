// Transform.cpp: implementation of the Transform class.

#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// YOUR CODE FOR HW1 HERE
	float radians = ((2 * pi) / 360) * degrees;
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;

	mat3 xmat(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);

	mat3 ymat(x*x, x*y, x*z, x*y, y*y, y*z, x*z, y*z, z*z);

	mat3 zmat(0.0, z, -y, -z, 0.0, x, y, -x, 0.0);

	mat3 rotMat((cos(radians)*xmat) + ((1 - cos(radians))*ymat) + (sin(radians)*(zmat)));
	return rotMat;
}

void Transform::left(float degrees, vec3& eye, vec3& up) {
	mat3 rotMat = rotate(degrees, up);
	eye = rotMat * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 unit = glm::cross(eye, up);
	vec3 unitNormal = glm::normalize(unit);

	mat3 rotMat = rotate(degrees, unitNormal);
	eye = (rotMat * eye);
	up = (rotMat * up);

	int dot1 = glm::dot(eye, up);
}


// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// YOUR CODE FOR HW1 HERE
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);
	mat4 transformMat = mat4(u.x, u.y, u.z, -glm::dot(u, eye),
		v.x, v.y, v.z, -glm::dot(v, eye),
		w.x, w.y, w.z, -glm::dot(w, eye),
		0, 0, 0, 1.0f);
	return transformMat;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	float yScale = 1.0F / (float)glm::tan(fovy / 2);
	float xScale = yScale / aspect;
	float range = zFar - zNear;
	float z = ((zNear + zFar) / range);

	mat4 transformMat = mat4(xScale, 0.0, 0.0, 0.0,
		0.0, yScale, 0.0, 0.0,
		0.0, 0.0, z, -1.0,
		0.0, 0.0, 2 * z, 0.0);

	return transformMat;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
	mat4 scaleMat = mat4(sx, 0.0, 0.0, 0.0,
		0.0, sy, 0.0, 0.0,
		0.0, 0.0, sz, 0.0,
		0.0, 0.0, 0.0, 1.0);

	return scaleMat;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
	mat4 translateMat = mat4(1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		tx, ty, tz, 1.0);

	return translateMat;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}