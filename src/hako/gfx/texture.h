#ifndef HAKO_GFX_TEXTURE_H
#define HAKO_GFX_TEXTURE_H


namespace Hako
{
	namespace Gfx
	{
		enum class TextureKind
		{
			TwoDimensions,
			ThreeDimensions,
			CubeMap
		};


		enum class TextureFilter
		{
			Nearest, Linear
		};


		enum class TextureWrapping
		{
			Repeat, Clamp
		};


		enum class TextureFormat
		{
			LinearRGBA8
		};
	}
}


#endif
