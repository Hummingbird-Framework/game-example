#ifndef HB_MATERIAL_2D_DEFINITION
#define HB_MATERIAL_2D_DEFINITION

struct Material2dDef
{
	double friction;
	double bounciness;

	Material2dDef(): friction(0.), bounciness(0.){}
	Material2dDef(double friction, double bounciness): friction(friction), bounciness(bounciness){};
};
#endif