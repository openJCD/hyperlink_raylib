//
// Created by openjcd on 20/12/2024.
//

#ifndef ORBITAL3DBACKGROUNDCONTROL_H
#define ORBITAL3DBACKGROUNDCONTROL_H
#include "Control.h"

class Orbital3DBackgroundControl : public Control {
private:
    Model *m_model;
    Shader m_shader;
    Camera3D m_camera = Camera3D();
protected:
    void Draw() override;

    void PostDraw() override;

    void Update(float Gametime) override;

public:
    explicit Orbital3DBackgroundControl(Model* model) : m_model(model), Control() {
        m_camera.fovy = 40;
        m_camera.up = Vector3(0, 1, 0);
        m_camera.position = Vector3(15, 15, 15);
        m_camera.target = Vector3(0, 0, 0);
        m_camera.projection = CAMERA_PERSPECTIVE;
    };
    ~Orbital3DBackgroundControl() override = default;
};



#endif //ORBITAL3DBACKGROUNDCONTROL_H
