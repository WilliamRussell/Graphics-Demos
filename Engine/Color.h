#pragma once
namespace Engine
{
	class Color 
	{
	private:
		float _rgba[4];

	public:
		void Assign(float r, float g, float b, float a);

		Color();

		Color(float r, float g, float b, float a);

		Color(float rgba[]);

		const float* rgba() const	{return _rgba;};

		static Color black() {return Color(0.0, 0.0, 0.0, 1.0);}

		static Color white() {return Color(1.0, 1.0, 1.0, 1.0);}

		static Color red() {return Color(1.0, 0.0, 0.0, 1.0);}

		static Color green(){return Color(0.0, 1.0, 0.0, 1.0);}

		static Color blue() {return Color(0.0, 0.0, 1.0, 1.0);}

		static Color yellow() {return Color(1.0, 1.0, 0.0, 1.0);}

		static Color null() {return Color(0.0, 0.0, 0.0, 0.0);}

		static Color inf() { return Color(999999.0, 999999.0, 999999.0, 1.0); }
	};
}