#include "Object.h"
#include "Keyboard.h"
#include "main.h"
#include "Config.h"
#include "Utility.h"

#include <iostream>
#include "GL/GLU.h"

void Keyboard::keyPressCb(unsigned char key, INT32 x, INT32 y)
{
    static Vector4 move_left(-10, 0, 0);
    static Vector4 move_right(10, 0, 0);
    static Vector4 move_up(0, 10, 0);
    static Vector4 move_down(0, -10, 0);
    static Vector4 move_in(0, 0, -10);
    static Vector4 move_out(0, 0, 10);
#if (DEBUG == TRUE)
    std::cout << "Press(" << key2str(key) << ")" << std::endl;
#endif
    switch (key)
    {
    case press::t:
        Globals::curr_obj->spinToggle();
        break;
    case press::x:
        Globals::curr_obj->applyForce(move_left);
        break;
    case press::X:
        Globals::curr_obj->applyForce(move_right);
        break;
    case press::y:
        Globals::curr_obj->applyForce(move_down);
        break;
    case press::Y:
        Globals::curr_obj->applyForce(move_up);
        break;
    case press::z:
        Globals::curr_obj->applyForce(move_in);
        break;
    case press::Z:
        Globals::curr_obj->applyForce(move_out);
        break;
    case press::r:
        Globals::curr_obj->reset();
        break;
    case press::o:
        Globals::curr_obj->rotateZ(5);
        break;
    case press::O:
        Globals::curr_obj->rotateZ(-5);
        break;
    case press::p:
        Globals::curr_obj->rotateX(5);
        break;
    case press::P:
        Globals::curr_obj->rotateX(-5);
        break;
    case press::l:
        Globals::curr_obj->rotateY(5);
        break;
    case press::L:
        Globals::curr_obj->rotateY(-5);
        break;
    case press::s:
        Globals::curr_obj->addScale(-1);
        break;
    case press::S:
        Globals::curr_obj->addScale(1);
        break;
    case press::b:
        if (Globals::curr_obj->obj_type == Object::ObjectType::Cube)
        {
            Globals::curr_obj = (Object*)&Globals::house;
        }
        else if (Globals::curr_obj->obj_type == Object::ObjectType::House)
        {
            Globals::curr_obj = (Object*)&Globals::ball;
        }
        else if (Globals::curr_obj->obj_type == Object::ObjectType::Ball)
        {
            Globals::curr_obj = (Object*)&Globals::cube;
        }
        break;
    case press::h:
        Globals::curr_obj->applyForce(Vector4(rand_int(-300, 300), rand_int(0, 300), rand_int(-300, 300)));
        break;
    }
    Globals::curr_obj->print();
}

void Keyboard::specialFuncCb(int key, int x, int y){
#if (DEBUG == TRUE)
    std::cout << "Press(" << key2str(key) << ")" << std::endl;
#endif
    switch (key)
    {
    case GLUT_KEY_F1:
        Globals::curr_obj = (Object*)&Globals::cube;
        break;
    case GLUT_KEY_F2:
        Globals::curr_obj = (Object*)&Globals::house;
        Globals::house.setCamera(Vector4(0, 10, 10), Vector4(0, 0, 0), Vector4(0, 1, 0));
        break;
    case GLUT_KEY_F3:
        Globals::curr_obj = (Object*)&Globals::house;
        Globals::house.setCamera(Vector4(-15, 5, 10), Vector4(-5, 0, 0), Vector4(0, 1, 0.5));
        break;
    case GLUT_KEY_F4:
        Globals::curr_obj = (Object*)&Globals::bunny;
        break;
    case GLUT_KEY_F5:
        Globals::curr_obj = (Object*)&Globals::dragon;
        break;
    }
}

std::string Keyboard::key2str(UINT8 key)
{
    switch (key)
    {
    case press::b: return "b";
    case press::h: return "h";
    case press::l: return "l";
    case press::L: return "L";
    case press::o: return "o";
    case press::O: return "O";
    case press::p: return "p";
    case press::P: return "P";
    case press::r: return "r";
    case press::s: return "s";
    case press::S: return "S";
    case press::t: return "t";
    case press::x: return "x";
    case press::X: return "X";
    case press::z: return "z";
    case press::Z: return "Z";
    case press::y: return "y";
    case press::Y: return "Y";
    case GLUT_KEY_F1: return "F1";
    case GLUT_KEY_F2: return "F2";
    case GLUT_KEY_F3: return "F3";
    case GLUT_KEY_F4: return "F4";
    case GLUT_KEY_F5: return "F5";
    default: return "Unknown key!";
    }
}