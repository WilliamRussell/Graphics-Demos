#include "Light.h"
#include "ShaderManager.h"
#include <iostream>

namespace Engine
{
	void Light::PassLightToShader(int shaderID, const Matrix4x4 &matrix) const
	{
		int ambientLoc = ShaderManager::GetManager()->GetVariableLocation(shaderID, "light_ambient");
		int diffuseLoc = ShaderManager::GetManager()->GetVariableLocation(shaderID, "light_diffuse");
		int specularLoc = ShaderManager::GetManager()->GetVariableLocation(shaderID, "light_specular");

		ShaderManager::GetManager()->SetVariable(ambientLoc, GetAmbient());
		ShaderManager::GetManager()->SetVariable(diffuseLoc, GetDiffuse());
		ShaderManager::GetManager()->SetVariable(specularLoc, GetSpecular());
		

		if (GetLightType() == LIGHT_DIRECTIONAL)
		{
			int directionLoc = ShaderManager::GetManager()->GetVariableLocation(shaderID, "light_direction");
			ShaderManager::GetManager()->SetVariable(directionLoc, GetDirection());
		}
		else if (GetLightType() == LIGHT_POINT)
		{
			int positionLoc = ShaderManager::GetManager()->GetVariableLocation(shaderID, "light_position");
			int contAttenLoc = ShaderManager::GetManager()->GetVariableLocation(shaderID, "light_const_attenuation");
			int linAttenLoc = ShaderManager::GetManager()->GetVariableLocation(shaderID, "light_linear_attenuation");
			int quadAttenLoc = ShaderManager::GetManager()->GetVariableLocation(shaderID, "light_quadratic_attenuation");

			
			//Vector4f temp = matrix * Vector4f(_position.getX(), _position.getY(), _position.getZ(), 1.f);
			
			ShaderManager::GetManager()->SetVariable(positionLoc, matrix * Vector4f(_position.getX(), _position.getY(), _position.getZ(), 1.f));
			ShaderManager::GetManager()->SetVariable(contAttenLoc, GetConstantAttenuation());
			ShaderManager::GetManager()->SetVariable(linAttenLoc, GetLinearAttenuation());
			ShaderManager::GetManager()->SetVariable(quadAttenLoc, GetQuadraticAttenuation());
		}
	}
}