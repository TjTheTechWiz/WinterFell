#pragma once

#include "BREnums.h"

namespace BRDataType {
	struct Vector2 {
		float x;
		float y;

		//Constructors
		Vector2() {
			x = 0; y = 0;
		}

		Vector2(float getX, float getY) {
			x = getX; y = getY;
		}
	};

	struct Vector3 {
		float x;
		float y;
		float z;

		//Constructors
		Vector3() {
			x = 0; y = 0; z = 0;
		}

		Vector3(float getX, float getY, float getZ) {
			x = getX; y = getY; z = getZ;
		}
	};

	struct Vector4 {
		float x;
		float y;
		float z;
		float w;

		//Constructors
		Vector4() {
			x = 0; y = 0; z = 0; w = 0;
		}

		Vector4(float getX, float getY, float getZ, float getW) {
			x = getX; y = getY; z = getZ; w = getW;
		}
	};

	struct AABB {
		Vector2 min; //Bottom Left
		Vector2 max; //Top Right

		AABB() {
			min.x = 0; min.y = 0; 
			max.x = 0; max.y = 0;
		}

		AABB(Vector2 getMin, Vector2 getMax) {
			min = getMin;
			max = getMax;
		}
	};
}


