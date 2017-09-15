#pragma once
#include "Shader.h"
#include "Vector3f.h"
#include "Vector4f.h"
#include "Color.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include <vector>

namespace Engine
{
	class ShaderManager
	{
	public:
		~ShaderManager();
		static ShaderManager* GetManager();

		bool CreateShaders(const char* filename);
		bool ApplyShader(int shaderID) const;
		bool ApplyShader(const char* shaderName) const;
		int GetShaderID(const char* shaderName) const;
		bool DeleteShader(int shaderID);
		bool DeleteAllShaders();

		int GetActiveShaderID() const {return _activeShader;}

		int GetVariableLocation(int shaderID, const char* variableName) const;
		
		void SetVariable(int variableLocation, int value) const;
		void SetVariable(int variableLocation, unsigned int value) const;
		void SetVariable(int variableLocation, float value) const;
		void SetVariable(int variableLocation, const Vector3f& value) const;
		void SetVariable(int variableLocation, const Color& value) const;
		void SetVariable(int variableLocation, const Vector4f& value) const;
		void SetVariable(int variavleLocation, const Matrix3x3& value) const;
		void SetVariable(int variableLocation, const Matrix4x4& value) const;

		int GetMaterialIDLocation(int shaderID) const;

		int GetTextureLocation(int shaderID, unsigned int textureUnit) const;
		void ApplyTextureToShader(int shaderID, const Texture* texture, int textureBindingPoint) const;
		
		int GetModelViewMatrixLocation(int shaderID) const;
		int GetProjectionMatrixLocation(int shaderID) const;
		int GetNormalMatrixLocation(int shaderID) const;

		const Shader* GetShader(int shaderID) const { return _shaders[shaderID]; }

	private:
		int _numOfShaders;
		mutable int _activeShader;
		std::vector<Shader*> _shaders;
		static ShaderManager* _pManager;

		ShaderManager() : _numOfShaders(0), _activeShader(0){};
		ShaderManager(const ShaderManager&){};
		ShaderManager& operator= (const ShaderManager&){};	
	};
}