#pragma once
#include <string>
#include "Color.h"
#include "Vector3f.h"
#include "Matrix4x4.h"

namespace Engine
{
	class Light
	{
	public:
		enum LightType
		{
			LIGHT_DIRECTIONAL,
			LIGHT_POINT,
			LIGHT_SPOT
		};

		Light() : _type(LIGHT_POINT),
				  _spotCutOff(0.f),
				  _spotExponent(0.f),
				  _constantAttenuation(0.f),
				  _linearAttenuation(0.f),
				  _quadraticAttenuation(0.f),
				  _ambient(Color::white()),
				  _diffuse(Color::white()),
				  _specular(Color::white()) {}

		Light(const char* lightName, 
			  const Color& ambient = Color::white(),
			  const Color& diffuse = Color::white(),
			  const Color& specular = Color::white()) : 
									   _lightName(lightName),
									   _spotCutOff(0.f),
									   _spotExponent(0.f),
									   _type(LIGHT_POINT),
									   _constantAttenuation(0.f),
									   _linearAttenuation(0.f),
									   _quadraticAttenuation(0.f),								   
									   _ambient(ambient),
									   _diffuse(diffuse),
									   _specular(specular) {}
		

		const char* GetLightName() const {return _lightName.data();}
		LightType GetLightType() const {return _type;}
		const Color& GetAmbient() const {return _ambient;}
		const Color& GetDiffuse() const {return _diffuse;}
		const Color& GetSpecular() const {return _specular;}

		const Vector3f& GetPosition() const {return _position;}
		const Vector3f& GetDirection() const {return _direction;}
		float GetSpotCutOff() const {return _spotCutOff;}
		float GetSpotExponent() const {return _spotExponent;}
		float GetConstantAttenuation() const {return _constantAttenuation;}
		float GetLinearAttenuation() const {return _linearAttenuation;}
		float GetQuadraticAttenuation() const {return _quadraticAttenuation;}

		void SetLightName(const char* lightName) {_lightName = lightName;}
		void SetLightType(LightType type) {_type = type;}
		void SetAmbient(const Color& ambient) {_ambient = ambient;}
		void SetDiffuse(const Color& diffuse) {_diffuse = diffuse;}
		void SetSpecular(const Color& specular) {_specular = specular;}

		void SetPosition(const Vector3f& position) {_position = position;}
		void SetDirection(const Vector3f& direction) {_direction = direction;}
		void SetSpotCutOff(float spotCutOff) {_spotCutOff = spotCutOff;}
		void SetSpotExponent(float spotExponent) {_spotExponent = spotExponent;}
		void SetConstantAttenuation(float constantAttenuation) {_constantAttenuation = constantAttenuation;}
		void SetLinearAttenuation(float linearAttenuation) {_linearAttenuation = linearAttenuation;}
		void SetQuadraticAttenuation(float quadraticAttenuation) {_quadraticAttenuation = quadraticAttenuation;}

		virtual ~Light(){}

		void PassLightToShader(int shaderID, const Matrix4x4 &matrix) const;
	private:
		LightType _type;

		Vector3f _position;
		Vector3f _direction;
		float _spotCutOff;
		float _spotExponent;
		float _constantAttenuation;
		float _linearAttenuation;
		float _quadraticAttenuation;

		Color _ambient;
		Color _diffuse;
		Color _specular;

		std::string _lightName;		
	};
}