#ifndef HB_CAMERA_H
#define HB_CAMERA_H

namespace hb
{
	class Camera
	{
	public:
		struct DrawingOrder
		{
			DrawingOrder(const Camera& camera):m_camera(camera){};
			bool operator()();
		private:
			const Camera& m_camera;
		};

		Camera();
		~Camera();
		
	};
}
#endif