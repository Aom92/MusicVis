#include "Renderer.h"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "Error de OpenGL:  (" << std::hex << error << ")" << " In function: " << function << " " << file << std::dec << " line: " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
    GlCall(glDrawElements(GL_TRIANGLES, ib.GetCount() , GL_UNSIGNED_INT, nullptr));
}