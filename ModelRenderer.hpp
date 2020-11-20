#pragma once
#include <vector>
#include "Entity.hpp"
#include "ModelShader.hpp"
#include "Camera.hpp"

class ModelRenderer {
public:

    void init();
    void render(Camera& camera);
    void destroy();

    std::vector<Entity> entities;

private:

    ModelShader m_shader;

};
