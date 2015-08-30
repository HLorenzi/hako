#ifndef HAKO_GFX_CAMERA_H
#define HAKO_GFX_CAMERA_H


#include <hako/bindings.h>
#include <hako/util/math_vector.h>


namespace Hako
{
	namespace Gfx
	{
		class Camera
		{
			friend Hako::Gfx::RenderOperation;


		public:
			Camera();
			~Camera();
			void init();

            void set_projection_ortho        (float left, float right, float top, float bottom, float znear, float zfar);
            void lerp_projection_ortho       (float left, float right, float top, float bottom, float znear, float zfar);
            void set_projection_perspective  (float fovy, float aspect_w_by_h, float znear, float zfar);
            void lerp_projection_perspective (float fovy, float aspect_w_by_h, float znear, float zfar);
            void set_projection_frustum      (float left, float right, float top, float bottom, float znear, float zfar);
            void lerp_projection_frustum     (float left, float right, float top, float bottom, float znear, float zfar);
            void set_projection_custom       (Hako::Math::Matrix4 matrix);

			void set_lookat  (Hako::Math::Vector3 eye, Hako::Math::Vector3 target, Hako::Math::Vector3 up);
			void lerp_lookat (Hako::Math::Vector3 eye, Hako::Math::Vector3 target, Hako::Math::Vector3 up);

			void advance_interpolation_frame();
			Hako::Math::Matrix4 get_matrix_projview(float interpolation);


		protected:
			enum class ProjectionKind
			{
				Orthographic,
				Perspective, Frustum,
				Custom
			};


			ProjectionKind      projection_kind;
			Hako::Math::Vector3 eye,    eye_last;
			Hako::Math::Vector3 target, target_last;
			Hako::Math::Vector3 up,     up_last;
			union
			{
				struct
				{
					float left, left_last, right, right_last;
					float top, top_last, bottom, bottom_last;
					float znear, znear_last, zfar, zfar_last;
				} orthographic;

				struct
				{
					float fovy, fovy_last, aspect, aspect_last;
					float znear, znear_last, zfar, zfar_last;
				} perspective;

				struct
				{
					float left, left_last, right, right_last;
					float top, top_last, bottom, bottom_last;
					float znear, znear_last, zfar, zfar_last;
				} frustum;

				struct
				{
					Hako::Math::Matrix4 matrix;
				} custom;
			} projection_data;
		};
	}
}


#endif
