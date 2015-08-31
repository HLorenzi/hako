#ifndef HAKO_BINDINGS_H
#define HAKO_BINDINGS_H


namespace Hako
{
	class Engine;
	class Allocator;


	namespace Dummy
	{
		class MemoryManager;
		class LoopManager;
		class GfxManager;


		namespace Gfx
		{
			class Mesh;
			class Texture;
			class Material;
			class FrameBuffer;
			class RenderOperation;
		}
	}


	namespace Std
	{
		class MemoryManager;
	}


	namespace Win32
	{
		class LoopManager;
		class GfxManager;
	}


	namespace OpenGL
	{
		class Mesh;
		class Texture;
		class Material;
		class FrameBuffer;
		class RenderOperation;
	}


	#ifdef HAKO_MODULE_MEM_STD
		typedef Hako::Std::MemoryManager MemoryManager;
	#else
		typedef Hako::Dummy::MemoryManager MemoryManager;
	#endif


	#ifdef HAKO_MODULE_OS_WIN32
		typedef Hako::Win32::LoopManager LoopManager;
	#else
		typedef Hako::Dummy::LoopManager LoopManager;
	#endif


	#ifdef HAKO_MODULE_OS_WIN32
		typedef Hako::Win32::GfxManager GfxManager;
	#else
		typedef Hako::Dummy::GfxManager GfxManager;
	#endif


	namespace Gfx
	{
		class Scene;
		class SceneNode;
		class Camera;
		class MaterialProperties;
		enum class DepthTestFunc;
		enum class BlendFunc;
		enum class CullFunc;
		enum class TextureKind;
		enum class TextureFormat;
		enum class TextureFilter;
		enum class TextureWrapping;

		#ifdef HAKO_MODULE_GFX_OPENGL
			typedef Hako::OpenGL::Mesh            Mesh;
			typedef Hako::OpenGL::Texture         Texture;
			typedef Hako::OpenGL::Material        Material;
			typedef Hako::OpenGL::FrameBuffer     FrameBuffer;
			typedef Hako::OpenGL::RenderOperation RenderOperation;
		#else
			typedef Hako::Dummy::Gfx::Mesh            Mesh;
			typedef Hako::Dummy::Gfx::Texture         Texture;
			typedef Hako::Dummy::Gfx::Material        Material;
			typedef Hako::Dummy::Gfx::FrameBuffer     FrameBuffer;
			typedef Hako::Dummy::Gfx::RenderOperation RenderOperation;
		#endif
	}


	Engine*           singleton();
	Hako::Allocator   singleton_allocator();
	Hako::GfxManager* singleton_gfx();
}


#endif
