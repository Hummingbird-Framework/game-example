#ifndef HB_COLOR_h
#define HB_COLOR_h

namespace hb
{
	struct Color {
		float r;
		float g;
		float b;
		float a;

		Color() {
			this->r = 0.0f;
			this->g = 0.0f;
			this->b = 0.0f;
			this->a = 1.0f;
		}

		Color(float r, float g, float b, float a = 1.0f) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		Color(int r, int g, int b, int a = 255) {
			this->r = (float)r/255.0f;
			this->g = (float)g/255.0f;
			this->b = (float)b/255.0f;
			this->a = (float)a/255.0f;
		}
	};
}

#endif

/**
 * \struct hb::Color
 * \ingroup core
 * 
 * Struct representing a color RGBA of floats [0, 1]
 */