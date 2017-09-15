#include "Parser.h"

Engine::Color ParseColor(const std::string &inString)
{
	int begin = (int)inString.find('(')+1;
	int mid1  = (int)inString.find(',');
	int mid2  = (int)inString.find(',', mid1+1); 
	int mid3  = (int)inString.find(',', mid2+1);
	int end   = (int)inString.find(')');						
	float r = (float)atof(inString.substr(begin, mid1-begin).c_str());
	float g = (float)atof(inString.substr(mid1+1, mid2-mid1-1).c_str());
	float b = (float)atof(inString.substr(mid2+1, mid3-mid2-1).c_str());
	float a = (float)atof(inString.substr(mid3+1, end-mid3-1).c_str());
	return Engine::Color(r,g,b,a);
}

Engine::Vector3f ParseVector2f(const std::string &inString)
{
	int begin = (int)inString.find('(')+1;
	int mid  = (int)inString.find(',');	
	int end   = (int)inString.find(')');
	float x = (float)atof(inString.substr(begin, mid-begin).c_str());	
	float y = (float)atof(inString.substr(mid+1, end-mid-1).c_str());
	return Engine::Vector3f(x, y, 0.f);
}

Engine::Vector3f ParseVector3f(const std::string &inString)
{
	int begin = (int)inString.find('(')+1;
	int mid1  = (int)inString.find(',');
	int mid2  = (int)inString.find(',', mid1+1);
	int end   = (int)inString.find(')');
	float x = (float)atof(inString.substr(begin, mid1-begin).c_str());
	float y = (float)atof(inString.substr(mid1+1, mid2-mid1-1).c_str());
	float z = (float)atof(inString.substr(mid2+1, end-mid2-1).c_str());
	return Engine::Vector3f(x, y, z);
}

Engine::Vector4f ParseVector4f(const std::string &inString)
{
	int begin = (int)inString.find('(')+1;
	int mid1  = (int)inString.find(',');
	int mid2  = (int)inString.find(',', mid1+1);
	int mid3  = (int)inString.find(',', mid2+1);
	int end   = (int)inString.find(')');
	float x = (float)atof(inString.substr(begin, mid1-begin).c_str());
	float y = (float)atof(inString.substr(mid1+1, mid2-mid1-1).c_str());
	float z = (float)atof(inString.substr(mid2+1, mid3-mid2-1).c_str());
	float w = (float)atof(inString.substr(mid3+1, end-mid3-1).c_str());
	return Engine::Vector4f(x, y, z, w);
}

int ParseInt(const std::string &inString)
{
	int begin = (int)inString.find('(')+1;
	int end = (int)inString.find(')');
	return atoi(inString.substr(begin, end-begin).c_str());
}

float ParseFloat(const std::string &inString)
{
	int begin = (int)inString.find('(')+1;
	int end = (int)inString.find(')');
	return (float)atof(inString.substr(begin, end-begin).c_str());
}