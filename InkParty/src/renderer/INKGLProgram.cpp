/* ***********************************************************************
	INKGLProgram.cpp - @Jijidici - 09/01/2014
************************************************************************ */

#include "renderer/INKGLProgram.h"

#include <iostream>
#include "GL/glew.h"

#define GL_STRINGIFY(s) #s

const GLchar* INKGLProgram::defaultVS =
"#version 330 core\n"
GL_STRINGIFY(
    layout(location = 0) in vec2 vPosition;

    void main() {
        gl_Position = vec4(vPosition, 0., 1.);
    }
);

const GLchar* INKGLProgram::defaultFS = 
"#version 330 core\n"
GL_STRINGIFY(
	out vec4 fragColor;

	void main() {
		fragColor = vec4(1., 0., 0., 1.);
	}
);

INKGLProgram::INKGLProgram()
	: _program(0) {

}

INKGLProgram::~INKGLProgram() {

}

void INKGLProgram::buildProgram(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource) {
	 // Creation d'un Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Sp�cification du code source
    glShaderSource(vertexShader, 1, &vertexShaderSource, 0);

    // Compilation du shader
    glCompileShader(vertexShader);

    /// V�rification que la compilation a bien fonctionn�e (tr�s important !)
    GLint compileStatus;

    // R�cup�ration du status de compilation
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
    if(compileStatus == GL_FALSE) {
        // Si echec, r�cup�ration de la taille du log de compilation
        GLint logLength;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);

        // Allocation d'une chaine de caract�re suffisement grande pour contenir le log
        char* log = new char[logLength];

        glGetShaderInfoLog(vertexShader, logLength, 0, log);
        std::cerr << "Vertex Shader error:" << log << std::endl;
        std::cerr << vertexShaderSource << std::endl;

        delete [] log;
		throw std::runtime_error("Error while compiling vertex shader");
    }

    // Creation d'un Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Sp�cification du code source
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);

    // Compilation du shader
    glCompileShader(fragmentShader);

    /// V�rification que la compilation a bien fonctionn�e (tr�s important !)

    // R�cup�ration du status de compilation
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatus);
    if(compileStatus == GL_FALSE) {
        // Si echec, r�cup�ration de la taille du log de compilation
        GLint logLength;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);

        // Allocation d'une chaine de caract�re suffisement grande pour contenir le log
        char* log = new char[logLength];

        glGetShaderInfoLog(fragmentShader, logLength, 0, log);
        std::cerr << "Fragment Shader error:" << log << std::endl;
        std::cerr << fragmentShaderSource << std::endl;

        delete [] log;
		throw std::runtime_error("Error while compiling fragment shader");
    }

    GLuint program;

    // Creation d'un programme
    program = glCreateProgram();

    // Attachement des shaders au programme
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // D�sallocation des shaders: ils ne seront r�ellement supprim�s que lorsque le programme sera supprim�
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Edition de lien
    glLinkProgram(program);

    /// V�rification que l'�dition de liens a bien fonctionn�e (tr�s important aussi !)
    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if(linkStatus == GL_FALSE) {
        // Si echec, r�cup�ration de la taille du log de link
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

        // Allocation d'une chaine de caract�re suffisement grande pour contenir le log
        char* log = new char[logLength];

        glGetProgramInfoLog(program, logLength, 0, log);
        std::cerr << "Program link error:" << log << std::endl;

        delete [] log;
        
		throw std::runtime_error("Error while linking shader program");
    }

	_program = program;
}

void INKGLProgram::use() {
	glUseProgram(_program);
}
