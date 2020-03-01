#pragma once
enum
{
	OBJ_VEHICLE,//mesh with physics and controls
	OBJ_JOINT,//mesh with no physics and rotates and scales with parent
	OBJ_RIGIDBODY,//mesh with physics
	OBJ_EMPTY,//mesh with no physics
};