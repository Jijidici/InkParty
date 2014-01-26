/* ***********************************************************************
	INKGLProgram.cpp - @Jijidici - 09/01/2014
************************************************************************ */

#include "renderer/INKGLProgram.h"

#include <iostream>
#include "GL/glew.h"
#include "gtc/type_ptr.hpp"

#include "renderer/INKRenderer.h"
#include "system/INKCamera.h"

#define GL_STRINGIFY(s) #s

const GLchar* INKGLProgram::defaultVS =
"#version 330 core\n"
GL_STRINGIFY(
    layout(location = 0) in vec3 vPosition;
	
	uniform mat4 uModelMat = mat4(1.);
	uniform mat4 uViewMat = mat4(1.);
	uniform mat4 uProjMat = mat4(1.);

    void main() {
        gl_Position = uProjMat * uViewMat * uModelMat * vec4(vPosition, 1.);
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
	: _program(0)
	, _modelMatrixLocation(-1)
	, _viewMatrixLocation(-1)
	, _projectionMatrixLocation(-1) {

}

INKGLProgram::~INKGLProgram() {

}

void INKGLProgram::buildProgram(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource) {
	 // Creation d'un Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Spécification du code source
    glShaderSource(vertexShader, 1, &vertexShaderSource, 0);

    // Compilation du shader
    glCompileShader(vertexShader);

    /// Vérification que la compilation a bien fonctionnée (très important !)
    GLint compileStatus;

    // Récupération du status de compilation
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
    if(compileStatus == GL_FALSE) {
        // Si echec, récupération de la taille du log de compilation
        GLint logLength;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);

        // Allocation d'une chaine de caractère suffisement grande pour contenir le log
        char* log = new char[logLength];

        glGetShaderInfoLog(vertexShader, logLength, 0, log);
        std::cerr << "Vertex Shader error:" << log << std::endl;
        std::cerr << vertexShaderSource << std::endl;

        delete [] log;
		throw std::runtime_error("Error while compiling vertex shader");
    }

    // Creation d'un Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Spécification du code source
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);

    // Compilation du shader
    glCompileShader(fragmentShader);

    /// Vérification que la compilation a bien fonctionnée (très important !)

    // Récupération du status de compilation
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatus);
    if(compileStatus == GL_FALSE) {
        // Si echec, récupération de la taille du log de compilation
        GLint logLength;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);

        // Allocation d'une chaine de caractère suffisement grande pour contenir le log
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

    // Désallocation des shaders: ils ne seront réellement supprimés que lorsque le programme sera supprimé
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Edition de lien
    glLinkProgram(program);

    /// Vérification que l'édition de liens a bien fonctionnée (très important aussi !)
    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if(linkStatus == GL_FALSE) {
        // Si echec, récupération de la taille du log de link
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

        // Allocation d'une chaine de caractère suffisement grande pour contenir le log
        char* log = new char[logLength];

        glGetProgramInfoLog(program, logLength, 0, log);
        std::cerr << "Program link error:" << log << std::endl;

        delete [] log;
        
		throw std::runtime_error("Error while linking shader program");
    }

	_program = program;

	initUniformLocations();
}

void INKGLProgram::use() {
	glUseProgram(_program);
}

void INKGLProgram::updateUniforms() {
	INKCamera* pCurrentCamera = INKRenderer::getInstance()->getCurrentCamera();
	if(pCurrentCamera != nullptr) {
		glUniformMatrix4fv(_viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(pCurrentCamera->getView()));
		glUniformMatrix4fv(_projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(pCurrentCamera->getProjection()));
	}
}

void INKGLProgram::sendModelUniform(const glm::mat4& modelMatrix) {
	glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void INKGLProgram::initUniformLocations() {
	_modelMatrixLocation = glGetUniformLocation(_program, "uModelMat");
	_viewMatrixLocation = glGetUniformLocation(_program, "uViewMat");
	_projectionMatrixLocation = glGetUniformLocation(_program, "uProjMat");

	updateUniforms();
}
