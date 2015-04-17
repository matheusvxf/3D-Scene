#pragma once

#include "Matrix4.h"
#include "Vector4.h"

class Camera
{
private:
    void calculate_camera_matrix();
protected:
    Vector4 e; /**< Center of projection */
    Vector4 d; /**< Look at */
    Vector4 up;/**< Up */

    Matrix4 world2camera;
public:
    Camera();
    Camera(const Vector4& e, const Vector4& d, const Vector4& up);
    ~Camera();

    Matrix4& getMatrix();
    double* getGLMatrix();
    void set_center_of_proj(const Vector4&);
    void set_center_of_proj(double x, double y, double z);
    void look_at(const Vector4&);
    void look_at(double x, double y, double z);
    void set_up(const Vector4&);
    void set_up(double x, double y, double z);
};

