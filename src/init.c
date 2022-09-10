#include "../inc/fractol.h"

void init(t_calculation_values *s_calculation_values, t_SDL_struct *s_SDL_struct)
{
    s_SDL_struct->my_window = NULL;
    s_calculation_values->struct_iterators.pix_num = (WINDOW_HEIGHT * WINDOW_WIDTH);
    s_calculation_values->mouse_x = 0;
    s_calculation_values->mouse_y = 0;
    s_calculation_values->Mouse_pos = 0;
    
    ft_strcpy(s_calculation_values->window_name, "my_window");
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        exit(1);
    }
    s_SDL_struct->my_window = SDL_CreateWindow(s_calculation_values->window_name, 
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, 
                                WINDOW_WIDTH, 
                                WINDOW_HEIGHT, 
                                SDL_WINDOW_ALLOW_HIGHDPI);

    if (s_SDL_struct->my_window == NULL)
    {
        fprintf(stderr, "could not create a window: %s\n", SDL_GetError());
        exit(1);
    }
    s_SDL_struct->surface = NULL;
    s_SDL_struct->surface = SDL_GetWindowSurface(s_SDL_struct->my_window);

    /* init surface with 0 */
    SDL_LockSurface(s_SDL_struct->surface);
    SDL_memset(s_SDL_struct->surface->pixels, 0, s_SDL_struct->surface->h * s_SDL_struct->surface->pitch);
    SDL_UnlockSurface(s_SDL_struct->surface);
    SDL_UpdateWindowSurface(s_SDL_struct->my_window);
}
