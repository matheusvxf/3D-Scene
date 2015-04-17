#ifndef _MAIN_H_
#define _MAIN_H_

#include "World.h"
#include "Cube.h"
#include "Ball.h"
#include "Camera.h"
#include "House.h"
#include "Bunny.h"
#include "Dragon.h"
#include "TestObject.h"

class World;
class TestObject;

namespace Globals
{
    extern Cube cube;
    extern Ball ball;
    extern House house;
    extern Bunny bunny;
    extern Dragon dragon;
    extern TestObject testObject;
    extern World world;
    extern Object* curr_obj;
    extern Camera camera;
    extern GLuint texture[128];
};

#endif