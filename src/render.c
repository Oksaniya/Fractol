#include "../inc/fractol.h"

void set_pixel(SDL_Surface *surface, int x, int y, t_pixel pixel)
{
  Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                             + y * surface->pitch
                                             + x * surface->format->BytesPerPixel);
  *target_pixel = pixel.color;
}