#include "../inc/fractol.h"

/*
void zoom(int button, int state, int x, int y)
{
	if (state != GLUT_UP) return;
 
	cx += (x - width / 2) * scale;
	cy -= (y - height/ 2) * scale;
 
	switch(button) {
    // zoom in 
	case GLUT_LEFT_BUTTON: 
		if (scale > fabs(x) * 1e-16 && scale > fabs(y) * 1e-16)
			scale /= 2;
		break;

    // zoom out 
	case GLUT_RIGHT_BUTTON: 
		scale *= 2;
		break;
	// any other button recenters 
	}
	set_texture();
}
*/