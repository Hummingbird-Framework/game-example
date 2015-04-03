#ifndef HB_MATERIAL_2D_H
#define HB_MATERIAL_2D_H

namespace hb
{
	struct Material2d
	{
		double friction;
		double bounciness;
		double density;

		Material2d(): friction(0.), bounciness(0.), density(0.){}
		Material2d(double friction, double bounciness, double density):
		friction(friction),
		bounciness(bounciness),
		density(density)
		{};
	};

}
#endif