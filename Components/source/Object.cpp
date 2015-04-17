#include "Object.h"
#include "DataType.h"

#include <iostream>
#include <string>
#include <sstream>

Object::Object()
{
    reset();
    spin_clockwise = FALSE;
    model2world.identity();
}

Object::~Object()
{
}

void Object::update()
{
    Vector4 acceleration;
    force -= velocity * friction;
    acceleration = force / mass;
    velocity += acceleration * dt;
    position += velocity * dt;
    force.set(0, 0, 0, 1);
    
    updateMatrix();
}

void Object::render()
{
    // Tell OpenGL what ModelView matrix to use:
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixd(this->getGLrotateX());
    glMultMatrixd(this->getMatrix().getPointer());
    glMultMatrixd(this->getGLrotateY());
    glMultMatrixd(this->getGLrotateZ());
}

Matrix4& Object::getMatrix()
{
    return model2world;
}

void Object::rotateX(double deg)
{
    angleX += deg;
    if (angleX > 360.0 || angleX < -360.0)
        angleX = 0.0;
}

void Object::rotateY(double deg)   // deg is in degrees
{
    angleY += deg;
    if (angleY > 360.0 || angleY < -360.0)
        angleY = 0.0;
}

void Object::rotateZ(double deg)
{
    angleZ += deg;
    if (angleZ > 360.0 || angleZ < -360.0)
        angleZ = 0.0;
}

Matrix4& Object::getRotationMatrixX()
{
    return m_rotateX;
}

Matrix4& Object::getRotationMatrixY()
{
    return m_rotateY;
}

Matrix4& Object::getRotationMatrixZ()
{
    return m_rotateZ;
}

GLdouble* Object::getGLrotateX()
{
    return m_rotateX.getPointer();
}

GLdouble* Object::getGLrotateY()
{
    return m_rotateY.getPointer();
}

GLdouble* Object::getGLrotateZ()
{
    return m_rotateZ.getPointer();
}

void Object::addScale(double sca)
{
    scale += sca;
    if (scale <= 0.1)
        scale = 0.1;
}

void Object::updateMatrix()
{
    /* Update translation and scale */
    Matrix4 m_scale, m_translate;
    m_translate.makeTranslate(position[0], position[1], position[2]);
    m_scale.makeScale(scale, scale, scale);
    model2world = m_translate * m_scale;
    model2world.transpose();
    
    /* Update rotations */
    m_rotateX.makeRotateX(angleX);
    m_rotateY.makeRotateY(angleY);
    m_rotateZ.makeRotateZ(angleZ);
    m_rotateX.transpose();
    m_rotateY.transpose();
    m_rotateZ.transpose();
}

void Object::spinToggle()
{
    spin_clockwise = !spin_clockwise;
}

void Object::applyForce(const Vector4& force)
{
    this->force += force;
}

Vector4& Object::getPosition()
{
    return this->position;
}

void Object::reset()
{
    position.set(0, 0, 0, 1);
    force = velocity = position;
    angleX = 0.0;
    angleY = 0.0;
    angleZ = 0.0;
    scale = 1.0;
    mass = 0.5;
    friction = 4;
    dt = 1.0 / 60.0;
}

void Object::print()
{
    std::cout << toString() << std::endl;
}

std::string Object::toString()
{
    std::stringstream buffer;
    buffer << "position: " << this->position.toString() << std::endl;
#if (DEBUG == TRUE)
    buffer << "matrix: " << std::endl << this->model2world.toString();
#endif
    return buffer.str();
}