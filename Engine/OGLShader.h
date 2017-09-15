#pragma once
#include "Shader.h"
#include <GL/glew.h>

namespace Engine
{
	class OGLShader : public Shader
	{
	public:
		OGLShader() : _program(0), _vertex(0), _fragment(0),
			_geometry(0), _tessControl(0), _tessEvaluation(0) {}
		~OGLShader(){ CleanUp(); }

		bool LoadShaderFromMemory(ShaderType type, const char* shader);
		bool LoadShaderFromFile(ShaderType type, const char* shader);
		bool LinkShader();
		int GetVariableLocation(const char* variableName) const;
		void ApplyTextureToShader(const Texture* texture, int textureIndex) const;
		void ApplyShader() const;
		void CleanUp();

		GLuint GetOGLProgram() const { return _program; }
	private:
		const GLchar* LoadSource(const char *filename) const;
		GLuint _vertex;
		GLuint _fragment;
		GLuint _geometry;
		GLuint _tessControl;
		GLuint _tessEvaluation;
		GLuint _program;
	};
}