#include "OGLShader.h"
#include "OGLTexture.h"
#include <iostream>


namespace Engine
{
	void OGLShader::CleanUp()
	{
		glDeleteShader(_vertex);
		glDeleteShader(_fragment);
		glDeleteShader(_geometry);
		glDeleteShader(_tessControl);
		glDeleteShader(_tessEvaluation);
		glDeleteProgram(_program);

		_vertex = _fragment = _geometry = _tessControl = _tessEvaluation = _program = 0;
	}

	bool OGLShader::LoadShaderFromFile(ShaderType type, const char* shader)
	{
		const GLchar *shaderSource = 0;
		shaderSource = LoadSource(shader);

		if (!shaderSource)
		{
			delete[] shaderSource;
			return false;
		}

		bool result = LoadShaderFromMemory(type, shaderSource);

		if (result == false)
		{
			std::cout << shader << " failed to compile." << std::endl;
		}

		delete[] shaderSource;
		return result;
	}

	bool OGLShader::LoadShaderFromMemory(ShaderType type, const char* shader)
	{

		GLenum oglType = 0;
		GLuint *pShaderId = 0;
		switch (type)
		{
		case SHADER_VERTEX:
			oglType = GL_VERTEX_SHADER;
			pShaderId = &_vertex;
			break;
		case SHADER_GEOMETRY:
			oglType = GL_GEOMETRY_SHADER;
			pShaderId = &_geometry;
			break;
		case SHADER_FRAGMENT:
			oglType = GL_FRAGMENT_SHADER;
			pShaderId = &_fragment;
			break;
		case SHADER_TESS_CONTROL:
			oglType = GL_TESS_CONTROL_SHADER;
			pShaderId = &_tessControl;
			break;
		case SHADER_TESS_EVALUATION:
			oglType = GL_TESS_EVALUATION_SHADER;
			pShaderId = &_tessEvaluation;
			break;
		}

		*pShaderId = glCreateShader(oglType);
		glShaderSource(*pShaderId, 1, &shader, NULL);
		glCompileShader(*pShaderId);
		GLint done = 0;
		glGetShaderiv(*pShaderId, GL_COMPILE_STATUS, &done);

		if (!done)
		{
			int length;
			glGetShaderiv(*pShaderId, GL_INFO_LOG_LENGTH, &length);
			char *log = new char[length];
			glGetShaderInfoLog(*pShaderId, length, NULL, log);
			std::cout << log << std::endl;
			delete[] log;
			return false;
		}

		if (!_program)
			_program = glCreateProgram();

		glAttachShader(_program, *pShaderId);
		return true;
	}

	bool OGLShader::LinkShader()
	{
		if (!_program)
			return false;

		glBindAttribLocation(_program, 0, "vertex");
		glBindAttribLocation(_program, 1, "normal");
		glBindAttribLocation(_program, 2, "tangent");
		glBindAttribLocation(_program, 3, "binormal");
		glBindAttribLocation(_program, 4, "texcoord");

		glBindFragDataLocation(_program, 0, "fragData0");
		glBindFragDataLocation(_program, 1, "fragData1");
		glBindFragDataLocation(_program, 2, "fragData2");
		glBindFragDataLocation(_program, 3, "fragData3");
		glBindFragDataLocation(_program, 4, "fragData4");

		glLinkProgram(_program);
		GLint done = 0;
		glGetProgramiv(_program, GL_LINK_STATUS, &done);

		if (!done)
		{
			return false;
		}

		_matIDLoc = GetVariableLocation("mat_ID");

		_textureUnit[0] = GetVariableLocation("textureUnit0");
		_textureUnit[1] = GetVariableLocation("textureUnit1");
		_textureUnit[2] = GetVariableLocation("textureUnit2");
		_textureUnit[3] = GetVariableLocation("textureUnit3");
		_textureUnit[4] = GetVariableLocation("textureUnit4");
		_textureUnit[5] = GetVariableLocation("textureUnit5");
		_textureUnit[6] = GetVariableLocation("textureUnit6");
		_textureUnit[7] = GetVariableLocation("textureUnit7");

		_modelViewMatrixLocation = GetVariableLocation("modelViewMat");
		_projectMatrixLocation = GetVariableLocation("projectionMat");
		_normalMatrixLocation = GetVariableLocation("normalMat");
		return true;
	}

	const GLchar* OGLShader::LoadSource(const char* filename) const
	{
		if (!filename) return NULL;
		FILE *fp;
		fopen_s(&fp, filename, "r");
		if (!fp) return NULL;

		fseek(fp, 0, SEEK_END);
		long size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		GLchar *buff = new GLchar[size + 1];
		if (!buff)
		{
			fclose(fp);
			return NULL;
		}

		size_t count = fread(buff, 1, size, fp);
		buff[count] = 0;
		if (!count || ferror(fp))
		{
			delete[] buff;
			buff = NULL;
		}
		fclose(fp);
		return buff;
	}

	int OGLShader::GetVariableLocation(const char* variableName) const
	{
		return glGetUniformLocation(_program, variableName);
	}

	void OGLShader::ApplyShader() const
	{
		glUseProgram(_program);
	}

	void OGLShader::ApplyTextureToShader(const Texture* texture, int textureIndex) const
	{
#ifdef USE_BINDLESS_TEXTURES		
		GLuint64 handle = glGetTextureHandleARB(static_cast<const OGLTexture*>(texture)->GetOGLHandle());
		glMakeTextureHandleResidentARB(handle);
		glProgramUniformHandleui64ARB(_program, textureIndex, handle);
#else
		texture->ApplyTexture(textureIndex);
		glProgramUniform1i(_program, textureIndex, textureIndex);
#endif				
	}

}
