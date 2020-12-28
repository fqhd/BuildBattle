#ifndef CHUNK_SHADER_H
#define CHUNK_SHADER_H
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include "Utils.hpp"
#include "Shader.hpp"


class ChunkShader : public Shader {
public:


	void loadMatrix(const glm::mat4& matrix);
	void getUniformLocations();


private:

	GLint m_matrixLocation = 0;

};

#endif
