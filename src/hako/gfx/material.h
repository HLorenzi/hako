#ifndef HAKO_GFX_MATERIAL_H
#define HAKO_GFX_MATERIAL_H


namespace Hako
{
	namespace Gfx
	{
		enum class DepthTestFunc
		{
			Always,
			Less, LessOrEqual, Equal, Greater, GreaterOrEqual
		};


		enum class BlendFunc
		{
			Normal, Additive
		};


		enum class CullFunc
		{
			NoCull, Clockwise, CounterClockwise
		};
	}
}


#endif
