#include "ShaderManager.h"
#include "OGLShader.h"
#include <fstream>
#include <string>

namespace Engine
{
	ShaderManager* ShaderManager::_pManager = 0;

	//	GetManager	
	//	Returns the instance of ShaderManager
	ShaderManager* ShaderManager::GetManager()
	{
		if (!_pManager)	
			_pManager = new ShaderManager();
		return _pManager;
	}

	//
	//dtor
	ShaderManager::~ShaderManager()
	{
		DeleteAllShaders();
	}

	//	CreateShaders
	//	Create shaders from text file
	bool ShaderManager::CreateShaders(const char *filename)
	{
		std::ifstream filein(filename);

		// check file opened correctly
		if (!filein)
			return false;

		std::string word;		
		while(filein >> word)
		{
			if (word.compare("shader") == 0)
			{
				// read the next 
				filein >> word;
				if (word.compare("{") == 0)
				{
					std::string data;	

					Shader* newShader = new OGLShader();
					
					while((word.compare("}") != 0) && (filein >> word))
					{
						if (word.compare("name") == 0)
						{											
							filein >> data;
							newShader->SetShaderName(data.c_str());
							continue;
						}
						if (word.compare("vertex") == 0 )
						{							
							filein >> data;
							newShader->LoadShaderFromFile(SHADER_VERTEX, data.c_str());
							continue;
						}
						if (word.compare("fragment") == 0)
						{
							filein >> data;
							newShader->LoadShaderFromFile(SHADER_FRAGMENT, data.c_str());
							continue;
						}
						if (word.compare("geometry") == 0)
						{
							filein >> data;
							newShader->LoadShaderFromFile(SHADER_GEOMETRY, data.c_str());
							continue;
						}
						if (word.compare("tessellation_control") == 0)
						{
							filein >> data;
							newShader->LoadShaderFromFile(SHADER_TESS_CONTROL, data.c_str());
							continue;
						}
						if (word.compare("tessellation_evaluation") == 0)
						{
							filein >> data;
							newShader->LoadShaderFromFile(SHADER_TESS_EVALUATION, data.c_str());
							continue;
						}
					}					

					if (newShader->LinkShader())
					{
						_shaders.push_back(newShader);
						_numOfShaders++;
						continue;
					}
					else
					{
						delete newShader;
					}
				}
			}
		}
		if (_numOfShaders)
			return true;
		return false;
	}

	//	DeleteShader
	//	Delete a Shader corresponding to the material ID
	bool ShaderManager::DeleteShader(int ShaderID)
	{
		delete _shaders[ShaderID];
		_shaders[ShaderID] = 0;
		return true;
	}

	//	DeleteAllShaders
	//	Delete every Shader managed by Shader manager
	bool ShaderManager::DeleteAllShaders()
	{
		for (unsigned int i = 0; i < _shaders.size(); i++)
		{
			if (_shaders[i])
			{
				delete _shaders[i];
				_shaders[i] = 0;
			}
		}
		_shaders.clear();
		_numOfShaders = 0;
		return true;
	}

	// ApplyShader
	// Apply a shader given a shader ID
	bool ShaderManager::ApplyShader(int ShaderID) const
	{
		if (ShaderID <= _numOfShaders && _shaders[ShaderID])
		{
			_activeShader = ShaderID;
			_shaders[ShaderID]->ApplyShader();
			return true;
		}
		return false;
	}

	// ApplyShader
	// Apply a shader given a shader name
	bool ShaderManager::ApplyShader(const char* shaderName) const
	{
		for (int i = 0; i < _numOfShaders; i++)
		{
			if (std::string(shaderName) == std::string(_shaders[i]->GetShaderName()))
			{
				_activeShader = i;
				_shaders[i]->ApplyShader();
				return true;
			}
		}
		return false;
	}

	// GetShaderID
	// Find and return the shader ID associated with a given shader name
	int ShaderManager::GetShaderID(const char* shaderName) const
	{
		for (int i = 0; i < _numOfShaders; i++)
		{
			if (std::string(shaderName) == std::string(_shaders[i]->GetShaderName()))
			{
				return i;				
			}
		}
		return 0;
	}

	// ApplyTextureToShader
	// Apply texture to specified shader
	void ShaderManager::ApplyTextureToShader(int shaderID, const Texture* texture, int textureBindingPoint) const
	{
		_shaders[shaderID]->ApplyTextureToShader(texture, textureBindingPoint);
	}

	// GetVariableLocation
	// Get the location of a variable in a specific shader
	int ShaderManager::GetVariableLocation(int shaderID, const char* variableName) const
	{
		return _shaders[shaderID]->GetVariableLocation(variableName);
	}

	// SetVariable
	// Set a single int variable in a shader
	void ShaderManager::SetVariable(int variableLocation, int value) const
	{
		glUniform1i(variableLocation, value); // OGL code in non OGL section? consider moving?
	}

	// SetVariable
	// Set a single int variable in a shader
	void ShaderManager::SetVariable(int variableLocation, unsigned int value) const
	{
		glUniform1ui(variableLocation, value); // OGL code in non OGL section? consider moving?
	}

	// SetVariable
	// Set a single float variable in a shader
	void ShaderManager::SetVariable(int variableLocation, float value) const
	{
		glUniform1f(variableLocation, value); // OGL code in non OGL section? consider moving?
	}

	// SetVariable
	// Set a vec3 variable in a shader
	void ShaderManager::SetVariable(int variableLocation, const Vector3f& value) const
	{
		glUniform3f(variableLocation, value.getX(), value.getY(), value.getZ());
	}

	// SetVariable
	// Set a color variable in a shader
	void ShaderManager::SetVariable(int variableLocation, const Color& value) const
	{
		glUniform3f(variableLocation, value.rgba()[0], value.rgba()[1], value.rgba()[2]);
	}

	// SetVariable
	// Set a vec4 variable in a shader
	void ShaderManager::SetVariable(int variableLocation, const Vector4f& value) const
	{
		glUniform4f(variableLocation, value.getX(), value.getY(), value.getZ(), value.getW());
	}

	// SetVariable
	// Set a mat3 variable in a shader
	void ShaderManager::SetVariable(int variableLocation, const Matrix3x3& value) const
	{
		glUniformMatrix3fv(variableLocation, 1, GL_FALSE, value.Element());
	}

	// SetVariable
	// Set a mat4 variable in a shader
	void ShaderManager::SetVariable(int variableLocation, const Matrix4x4& value) const
	{
		glUniformMatrix4fv(variableLocation, 1, GL_FALSE, value.Element());		
	}

	// GetMaterialIDLocation
	// Return the material ID location in a shader
	int ShaderManager::GetMaterialIDLocation(int shaderID) const
	{
		if (_shaders[shaderID] && shaderID <= _numOfShaders)					
			return _shaders[shaderID]->GetMaterialIDLocation();		
		return -1;
	}


	// GetMaterialBaseTextureLocation
	// Return the base texture location in a shader
	int ShaderManager::GetTextureLocation(int shaderID, unsigned int textureUnit) const
	{
		if (_shaders[shaderID] && shaderID <= _numOfShaders)					
			return _shaders[shaderID]->GetTextureLocation(textureUnit);		
		return -1;
	}	

	// GetModelViewProjectionMatrixLocation
	// Return the model view projection matrix location in the shader
	int ShaderManager::GetModelViewMatrixLocation(int shaderID) const
	{
		if (_shaders[shaderID] && shaderID <= _numOfShaders)					
			return _shaders[shaderID]->GetModelViewMatrixLocation();		
		return -1;
	}

	// GetModelViewProjectionMatrixLocation
	// Return the model view projection matrix location in the shader
	int ShaderManager::GetProjectionMatrixLocation(int shaderID) const
	{
		if (_shaders[shaderID] && shaderID <= _numOfShaders)					
			return _shaders[shaderID]->GetProjectionMatrixLocation();		
		return -1;
	}

	// GetNormalMatrixLocation
	// Return the normal matrix location in the shader
	int ShaderManager::GetNormalMatrixLocation(int shaderID) const
	{
		if (_shaders[shaderID] && shaderID <= _numOfShaders)					
			return _shaders[shaderID]->GetNormalMatrixLocation();		
		return -1;
	}
}