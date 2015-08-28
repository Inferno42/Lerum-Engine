#ifndef CAMERA_H
#define CAMERA_H
#include "Definitions.h"

class CCamera
{
	public:
		CCamera() {};
		//Camera controls
		SDL_Rect GetCamera() {return Camera;}
		void SetCamera(int x, int y) {Camera.x = x; Camera.y = y;}
		void MoveCameraRight(int amount) {Camera.x += amount;}
		void MoveCameraLeft(int amount) {Camera.x -= amount;}
		void MoveCameraUp(int amount) {Camera.y -= amount;}
		void MoveCameraDown(int amount) {Camera.y += amount;}
		SDL_Rect Camera;

}; extern CCamera gCam;

#endif // CAMERA_H