// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>

struct wav_header {

    char* ChunkID = (char*)calloc(4, 4);
    unsigned int ChunkSize;
    char* Format = (char*)calloc(4, 4);

    char* Subchunk1ID = (char*)calloc(4, 4);
    char* SubChunk1Size = (char*)calloc(4, 4);
    char* AudioFormat = (char*)calloc(2, 2);
    char* NumChannels = (char*)calloc(2, 2);
    long SampleRate;
    unsigned long ByteRate;
    unsigned short int BlockAlign;
    unsigned short int BitsPerSample;
    
    char Subchunk2ID[4];
    unsigned long Subchunk2Size;


public:
    void readWAV( std::ifstream &audioFile  )  { 
  
        FILE* audioin; 
        fopen_s(&audioin, "UGO.wav", "rb");
        
        fread(ChunkID, 4, 1, audioin);
        fread(&ChunkSize,4,1,audioin);
        fread(Format, 4, 1,audioin);
        fread(Subchunk1ID, 4, 1, audioin);
        fread(SubChunk1Size, 4, 1, audioin);
        fread(AudioFormat, 2, 1, audioin);
        fread(NumChannels, 2, 1, audioin);
        fread(&SampleRate, 4, 1, audioin);
        fread(&ByteRate, 4, 1, audioin);
        fread(&BlockAlign, 2, 1, audioin);
        fread(&BitsPerSample, 2, 1, audioin);


#if 0
        audioFile.read(ChunkID, 4 );

        audioFile.read(Buffer , 4);  ChunkSize = (unsigned long)Buffer;
        audioFile.read(Format, 4);
        audioFile.read(Subchunk1ID, 4); 
        audioFile.read(SubChunk1Size, 4); 
        realloc(Buffer, 2);
        audioFile.read(AudioFormat, 2); 
        audioFile.read(NumChannels, 2); 
     
        realloc(Buffer, 4);
        //audioFile.read(SampleRate, 4); 
        audioFile.read(Buffer, 4); ByteRate = (unsigned long)Buffer;
       
        realloc(Buffer, 2);
        audioFile.read(Buffer, 2); BlockAlign = (unsigned long)Buffer;
        audioFile.read(Buffer, 2); BitsPerSample = (unsigned long)Buffer;

        free(Buffer);
#endif
    }

    void print() {

        std::cout << "ChunkID: " << ChunkID << std::endl;
        std::cout << "ChunkSize: " << ChunkSize << std::endl;
        std::cout << "Format: " << Format  << std::endl;
        std::cout << "Subchink1ID: " << Subchunk1ID << std::endl;
        std::cout << "SubChunk1Size: "<< (int)SubChunk1Size[0] << std::endl;
        std::cout << "AudioFormat: " << (int)AudioFormat[0] << std::endl;
        std::cout << "NumChannels: " << (int)NumChannels[0] << std::endl;
        std::cout << "SampleRate: " << (UINT16)SampleRate << std::endl;
        std::cout << "ByteRate: " << ByteRate << std::endl;
        std::cout << "BlockAllign: " << BlockAlign << std::endl;
        std::cout << "BitsPerSample: " << BitsPerSample << std::endl;

    }



};






void PlayMusic(LPCWSTR pathname) {

    PlaySound(pathname, NULL, SND_FILENAME);
}

void ProcessSound(LPCWSTR pathname) {
    wav_header header;

    std::ifstream Sonido(pathname, std::ifstream::binary);
    std::string outtext;


    header.readWAV( Sonido );
    header.print();


#if 0
    while (std::getline(Sonido, outtext)) {
       
        std::cout << outtext;
    }
#endif

}


int main()
{
    std::cout << "Listen World!\n";

    

    LPCWSTR Pathname = L"UGO.wav";
    

    //std::thread Process(ProcessSound, Pathname);

    //std::thread Playback(PlayMusic, Pathname);


    //Playback.join();
    //Process.join();
    

    wav_header header;

    std::ifstream Sonido(Pathname, std::ifstream::binary);
    std::string outtext;


    header.readWAV(Sonido);
    header.print();

    
    return 0;
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
  