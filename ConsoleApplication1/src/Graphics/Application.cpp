
#include <glew.h>
#include <gl3w.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);              //GLEW needs a valid OpenGL context to be initiated. 

    glfwSwapInterval(1);                        //Ponemos el sync para estabilizar el frame rate.

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW ERROR " << std::endl;


    std::cout << glGetString(GL_VERSION) << std::endl;

    {

        float positions[] = {
            -0.5f, -0.5f,
             0.5f,  -0.5f,
             0.5f, 0.5f,
             -0.5f, 0.5f,
        };

        unsigned int indices[] = { //Deber ser de tipo unsigned SIEMPRE
            0,1,2,
            2,3,0
        };


       
        VertexArray va;                                         /* Creamos un Vertex Array */

        VertexBuffer vb(positions, 4 * 2 * sizeof(positions));  /* Creamos un Vertex Buffer */

        VertexBufferLayout layout; 
        layout.Push<float>(2); //Number of components in positions
        va.AddBuffer(vb,  layout);
       
        IndexBuffer ib(indices, sizeof(indices));               /* Creamos un Index Buffer */


        Shader shader("res/shaders/Cool.shader");               /*Compilamos los shaders */
        shader.Bind();

        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);   /* Cremaos una variable Uniform para pasar datos al shader */

       
		va.UnBind();
        vb.UnBind();
        shader.UnBind();
        ib.UnBind();
		

        Renderer renderer; /* Creamos una instancia de nuestro Renderizador */
        
        /* Loop until the user closes the window */


        //GLint iTime = glGetUniformLocation(shader, "iTime");
        float r = 0.0f;
        float increment = 0.05f;
        float initialTime = clock() / (float)CLOCKS_PER_SEC;
        int frames = 0;
        double elapsed = 0;

        while (!glfwWindowShouldClose(window))
        {

            float currentTime = clock() / (float)CLOCKS_PER_SEC * 12;
            elapsed = (clock() / (double)CLOCKS_PER_SEC) - initialTime;

            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
            shader.SetUniform1f("iTime", currentTime); //Uniforms can only be binded when a shader is binded lol
			va.Bind();
			ib.Bind();
            renderer.Draw(va, ib, shader);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;


            r += increment;


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

            //Contador de Frames y tiempo transcurrido
#if 0
            frames++;
            std::cout << "Frame Count: " << frames << "  Elapsed: (seconds) " << elapsed << std::endl;
#endif    
        }

        
    }
    glfwTerminate();
    return 0;
}