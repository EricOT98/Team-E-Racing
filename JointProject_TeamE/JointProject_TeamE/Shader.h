#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL\gl3w.h>

/// Loads and compiles vertex, fragment and geometry shaders
/// 
/// Loads and compiles vertex, fragment and geometry shaders by reading
/// in each file into a buffer and calling opengl calls to compile
class Shader
{
public:
	// The shader program ID
	GLuint Program;
	void Use();

	// NOTE(Darren): We might need geometry shaders?? Maybe. Textures can be manipulated with textures
	//					coords instead of actually vertex geometry.
	void LoadShader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath = nullptr);
private:
	void Compile(const GLchar *vShaderCode, const GLchar *fShaderCode, const GLchar *gShaderCode = nullptr);
};

#endif