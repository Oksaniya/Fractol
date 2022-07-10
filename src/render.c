#include "../inc/fractol.h"

void set_pixel(SDL_Surface *surface, int x, int y, t_pixel pixel)
{
  Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                             + y * surface->pitch
                                             + x * surface->format->BytesPerPixel);
  *target_pixel = pixel.color;
}
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