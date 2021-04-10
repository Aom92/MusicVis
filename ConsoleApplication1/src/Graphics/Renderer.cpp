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
	GlCall(glLineWidth(3.0));
    GlCall(glDrawElements(GL_LINES_ADJACENCY, ib.GetCount() , GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawPoints(const VertexArray& va,const Shader& shader ,unsigned int first ) const
{
	shader.Bind();
	va.Bind();
	

	unsigned int count = 2;
	
	GlCall(glDrawElements(GL_TRIANGLES, 2, GL_UNSIGNED_INT, nullptr));
}