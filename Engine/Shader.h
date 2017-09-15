#pragma once
#include "Texture.h"
#include <string>

namespace Engine
{
	enum ShaderType
	{
		SHADER_VERTEX,
		SHADER_GEOMETRY,
		SHADER_FRAGMENT,
		SHADER_TESS_CONTROL,
		SHADER_TESS_EVALUATION
	};

	class Shader
	{
	public:
		Shader() : _matIDLoc(-1),
			_modelViewMatrixLocation(-1),
			_projectMatrixLocation(-1),
			_normalMatrixLocation(-1)

		{
			_textureUnit[0] = _textureUnit[1] = _textureUnit[2] = _textureUnit[3] = 0;
		}

		virtual ~Shader(){}

		Shader(const char* shaderName) : _shaderName(shaderName){}
		void SetShaderName(const char* shaderName) { _shaderName = shaderName; }
		const char* GetShaderName() const { return _shaderName.data(); }

		int GetMaterialIDLocation() const { return _matIDLoc; }

		int GetTextureLocation(unsigned int textureUnit) const { return (textureUnit < 7) ? _textureUnit[textureUnit] : -1; }

		int GetModelViewMatrixLocation() const { return _modelViewMatrixLocation; }
		int GetProjectionMatrixLocation() const { return _projectMatrixLocation; }
		int GetNormalMatrixLocation() const { return _normalMatrixLocation; }

		virtual bool LoadShaderFromMemory(ShaderType type, const char* shader) = 0;
		virtual bool LoadShaderFromFile(ShaderType type, const char* shader) = 0;
		virtual bool LinkShader() = 0;
		virtual void ApplyTextureToShader(const Texture* texture, int textureIndex) const = 0;
		virtual int GetVariableLocation(const char* variableName) const = 0;
		virtual void ApplyShader() const = 0;
		virtual void CleanUp() = 0;

	private:
		std::string _shaderName;
	protected:
		// locations of material 
		int _matIDLoc;
		int _textureUnit[8];

		// locations of matrices
		int _modelViewMatrixLocation;
		int _projectMatrixLocation;
		int _normalMatrixLocation;
	};

}