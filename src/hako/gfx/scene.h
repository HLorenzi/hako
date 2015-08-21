#ifndef HAKO_GFX_SCENE_H
#define HAKO_GFX_SCENE_H


#include <hako/util/ds_flattree.h>
#include <hako/util/math_vector.h>
#include <hako/bindings.h>


namespace Hako
{
	namespace Gfx
	{
		class SceneNode
		{
		public:
			enum class Kind
			{
				Renderer,
				Translation, Rotation, Scaling, CustomTransform
			};


			static SceneNode make_renderer();
			static SceneNode make_translation();
			static SceneNode make_rotation();
			static SceneNode make_scaling();
			static SceneNode make_custom_transform();

			void set_renderer_mesh    (Hako::Gfx::Mesh* mesh, Hako::Gfx::Material* material);
			void set_renderer_options (int layer, unsigned int mask);
			void set_translation      (Hako::Math::Vector3 position);
			void lerp_translation     (Hako::Math::Vector3 position);
			void set_rotation         (Hako::Math::Vector3 axis, float angle);
			void lerp_rotation        (Hako::Math::Vector3 axis, float angle);
			void set_scaling          (Hako::Math::Vector3 scale);
			void lerp_scaling         (Hako::Math::Vector3 scale);
			void set_custom_transform (Hako::Math::Matrix4 matrix);


			Kind kind;
			union
			{
				struct
				{
					Hako::Gfx::Mesh*     mesh;
					Hako::Gfx::Material* material;
					int                  layer;
					unsigned int         mask;
				} renderer;

                struct
                {
					Hako::Math::Vector3 position, position_last;
                } translation;

                struct
                {
					Hako::Math::Vector3 axis, axis_last;
					float angle, angle_last;
                } rotation;

                struct
                {
					Hako::Math::Vector3 scale, scale_last;
                } scaling;

                struct
                {
					Hako::Math::Matrix4 matrix;
                } custom_transform;
			} data;
		};


		class Scene
		{
			friend Hako::Gfx::RenderOperation;


		public:
			typedef Hako::DS::FlatTree<SceneNode>::Reference Reference;

			Scene();
			void init();

			Reference add       (SceneNode node);
			Reference add_child (Reference& parent, SceneNode node);


		protected:
			Hako::DS::FlatTree<SceneNode> tree;
		};
	}
}


#endif
