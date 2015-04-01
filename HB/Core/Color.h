#ifndef HB_COLOR_h
#define HB_COLOR_h

namespace hb
{
	struct Color {
		float r; //!< Red component of the color
		float g; //!< Green component of the color
		float b; //!< Blue component of the color
		float a; //!< Alpha component of the color (its opacity)

		/*!
		  \brief Default constructor. Initializes to color black.
		*/
		Color() {
			this->r = 0.0f;
			this->g = 0.0f;
			this->b = 0.0f;
			this->a = 1.0f;
		}

		/*!
		  \brief Floats contructor.
		  \param r Red component of the color
		  \param g Green component of the color
		  \param b Blue component of the color
		  \param a (optional) Alpha component of the color (its opacity).
		*/
		Color(float r, float g, float b, float a = 1.0f) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		/*!
		  \brief Int contructor.
		  \param r Red component of the color
		  \param g Green component of the color
		  \param b Blue component of the color
		  \param a (optional) Alpha component of the color (its opacity).

		  Values should be between 0 and 255. They will be divided by 255.0f.
		*/
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
 * \brief A color represented in the RGBA format.
 * 
 * The values of its components should be between 0.0 and 1.0.
 */