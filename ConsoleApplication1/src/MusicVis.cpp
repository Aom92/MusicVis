#pragma comment(lib, "winmm.lib")



#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <fftw3.h>
#include <ctime>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "Graphics/Renderer.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexBufferLayout.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/VertexArray.h"
#include "Graphics/Shader.h"

struct wav_header {

    /*
        Basandonos en la estructura  canonica del formato WAVE:
        http://soundfile.sapp.org/doc/WaveFormat/

    */
    char* ChunkID = (char*)calloc(4, 4);
    unsigned int ChunkSize = 0;
    char* Format = (char*)calloc(4, 4);

    char* Subchunk1ID = (char*)calloc(4, 4);
    unsigned long int SubChunk1Size = 0;
    unsigned short int AudioFormat = 0;
    unsigned short int NumChannels = 0;
    unsigned long SampleRate = 0;
    unsigned long ByteRate = 0;
    unsigned short int BlockAlign = 0;
    unsigned short int BitsPerSample = 0;

    char* Subchunk2ID = (char*)calloc(4, 4);
    unsigned long int Subchunk2Size = 0;


public:
    short int* readWAV(std::string pathaudioFile) {

        FILE* audioin;
        fopen_s(&audioin, pathaudioFile.c_str(), "rb");

        fread(ChunkID, 4, 1, audioin);
        fread(&ChunkSize, 4, 1, audioin);
        fread(Format, 4, 1, audioin);
        fread(Subchunk1ID, 4, 1, audioin);
        fread(&SubChunk1Size, 4, 1, audioin);
        fread(&AudioFormat, 2, 1, audioin);
        fread(&NumChannels, 2, 1, audioin);
        fread(&SampleRate, 4, 1, audioin);
        fread(&ByteRate, 4, 1, audioin);
        fread(&BlockAlign, 2, 1, audioin);
        fread(&BitsPerSample, 2, 1, audioin);
        fread(Subchunk2ID, 4, 1, audioin);
        fread(&Subchunk2Size, 4, 1, audioin);

        //short int* data = (short int*) calloc(1, Subchunk2Size);
        //fread(data, Subchunk2Size, 1, audioin);


        int sample_size = BitsPerSample / 8; //Esto esta en Bytes.
        int sample_count = (Subchunk2Size) / BitsPerSample;
        std::cout << "Sample count: " << sample_count << '\n';

        short int* audio_dat = (short int*)calloc(sample_count, 2);
        for (int i = 0; i < sample_count; i++)
        {

            fread(&audio_dat[i], 2, 1, audioin);
            //std::cout << "Sample " << i << " Data: " << audio_dat[i] << '\n';


        }


        fclose(audioin);

        return audio_dat;

    }

    void print_header() {

        std::cout << "ChunkID: " << ChunkID << std::endl;
        std::cout << "ChunkSize: " << ChunkSize << std::endl;
        std::cout << "Format: " << Format << std::endl;
        std::cout << "Subchink1ID: " << Subchunk1ID << std::endl;
        std::cout << "SubChunk1Size: " << SubChunk1Size << std::endl;
        std::cout << "AudioFormat: " << AudioFormat << std::endl;
        std::cout << "NumChannels: " << NumChannels << std::endl;
        std::cout << "SampleRate: " << SampleRate << std::endl;
        std::cout << "ByteRate: " << ByteRate << std::endl;
        std::cout << "BlockAllign: " << BlockAlign << std::endl;
        std::cout << "BitsPerSample: " << BitsPerSample << std::endl;
        std::cout << "Subchunk2ID: " << Subchunk2ID << std::endl;
        std::cout << "Subchunk2Size: " << Subchunk2Size << std::endl;

    }



};


void PlayMusic(LPCWSTR pathname) {

    std::cout << "Playing music! " << std::endl;

    PlaySound(pathname, NULL, SND_FILENAME);
}

short int*  ProcessSound(std::string pathname) {

    wav_header header;

    short int* data = header.readWAV(pathname);
    header.print_header();



    return data;
}

void FFT() {
    fftw_complex* out;
    fftw_plan p;


}

int Draw() {
    GLFWwindow* window;

    /* Inicializamos la biblioteca */
    if (!glfwInit())
        return -1;

    /* Crear ventana y su contexto OpenGL*/
    window = glfwCreateWindow(640, 480, "MusicVis", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }


    /* Hacemos el contexto de la ventana actual */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

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
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, sizeof(indices));               /* Creamos un Index Buffer */


		Shader shader("res/Shader.shader");               /*Compilamos los shaders */
		shader.Bind();

		/* Cremaos una variable Uniform para pasar datos al shader */


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
			
			shader.SetUniform1f("iTime", currentTime); //Uniforms can only be binded when a shader is binded lol
			va.Bind();
			ib.Bind();
			renderer.Draw(va, ib, shader);


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

    
}





int main()
{
    std::cout << "Listen World!\n";




    LPCWSTR Pathname = L"riff.wav";


    std::thread Process(ProcessSound, "riff.wav");

    std::thread Playback(PlayMusic, Pathname);

    std::thread Render(Draw);

    Process.join();
    Playback.join();
    Render.join();


    return 0;



}