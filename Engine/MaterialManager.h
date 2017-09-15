#pragma once
#include "Material.h"
#include <vector>
#include "OGLUniformBufferObject.h"



namespace Engine
{
	class MaterialManager
	{
	public:	
		~MaterialManager();
		static MaterialManager* GetManager();

		bool CreateMaterials(const char* filename);		
		bool DeleteMaterial(int materialID);
		bool DeleteAllMaterials();

		int GetMaterialID(const char* materialName) const;
		const Material* GetMaterial(int materialID);

		bool ApplyMaterialToActiveShader(int materialID) const;

		int GetNumberOfMaterials() const {return _numOfMaterials;}

	private:
		int _numOfMaterials;
		std::vector<Material*> _materials;
		static MaterialManager* _pManager;

		OGLUniformBufferObject _ubo;

		MaterialManager() : _numOfMaterials(0) {}
		MaterialManager(const MaterialManager&);                 // Prevent copy-construction
		MaterialManager& operator=(const MaterialManager&);      // Prevent assignment
	};
}
