#ifndef HAKO_GFX_SCENE_H
#define HAKO_GFX_SCENE_H


#include <hako/util/ds_flattree.h>
#include <hako/util/math_vector.h>
#include <hako/bindings.h>


namespace Hako
{
	namespace Gfx
	{
		class Scene;
		class SceneRenderer;


		class SceneNode
		{
			friend Hako::Gfx::RenderOperation;
			friend Hako::Gfx::Scene;
			friend Hako::Gfx::SceneRenderer;


		public:
			enum class Kind
			{
				Renderer,
				Translation, Rotation, Scaling, CustomTransform
			};


			static SceneNode make(Kind kind);


		protected:
			bool active;
			bool dirty;
			Kind kind;
			union
			{
				struct
				{
					Hako::DS::RefVector<SceneRenderer>::Reference renderer_reference;
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


		class SceneRenderer
		{
			friend Hako::Gfx::RenderOperation;
			friend Hako::Gfx::Scene;
			friend Hako::Gfx::SceneNode;


		protected:
			bool                                     active;
			Hako::Math::Matrix4                      transform_matrix;
			Hako::DS::FlatTree<SceneNode>::Reference tree_reference;
			Hako::Gfx::Mesh*                         mesh;
			Hako::Gfx::Material*                     material;
			int                                      layer;
			unsigned int                             mask;
		};


		class Scene
		{
			friend Hako::Gfx::RenderOperation;


		public:
			typedef Hako::DS::FlatTree<SceneNode>::Reference Reference;


			Scene();
			void init();

			Reference add_renderer         (Reference* parent);
			Reference add_translation      (Reference* parent);
			Reference add_rotation         (Reference* parent);
			Reference add_scaling          (Reference* parent);
			Reference add_custom_transform (Reference* parent);

			void set_active           (Reference* parent, bool active);
			void set_renderer_mesh    (Reference* parent, Hako::Gfx::Mesh* mesh, Hako::Gfx::Material* material);
			void set_renderer_options (Reference* parent, int layer, unsigned int mask);
			void set_translation      (Reference* parent, Hako::Math::Vector3 position);
			void lerp_translation     (Reference* parent, Hako::Math::Vector3 position);
			void set_rotation         (Reference* parent, Hako::Math::Vector3 axis, float angle);
			void lerp_rotation        (Reference* parent, Hako::Math::Vector3 axis, float angle);
			void set_scaling          (Reference* parent, Hako::Math::Vector3 scale);
			void lerp_scaling         (Reference* parent, Hako::Math::Vector3 scale);
			void set_custom_transform (Reference* parent, Hako::Math::Matrix4 matrix);

			void refresh_matrices(float interpolation);


		protected:
			Reference add(Reference* parent, SceneNode node);


			unsigned int refresh_matrices_recursive(
				float               interpolation,
				unsigned int        node_index,
				Hako::Math::Matrix4 cur_matrix,
				bool                dirty);


			Hako::DS::FlatTree<SceneNode>      tree;
			Hako::DS::RefVector<SceneRenderer> renderers;
		};
	}
}


#endif
