#include <SDL2/SDL.h>

#define TRUE 1
#define WINDOW_WiDTH 750
#define WINDOW_HEIGHT 500

#define RED 2
#define GREEN 1
#define BLUE 0
#define OPACITY 3

typedef union   s_pixel
{
    uint8_t     channel[4];
    uint32_t    color;
}               t_pixel;

void set_pixel(SDL_Surface *surface, int x, int y, t_pixel pixel);


int main(void)
{
    SDL_Window      *my_window;
    SDL_Event       window_event;
    SDL_Surface		*surface;
    char            window_name[] = "my_window";
    t_pixel         pixel;

    my_window = NULL;
    surface = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    my_window = SDL_CreateWindow(window_name, 
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, 
                                WINDOW_WiDTH, 
                                WINDOW_HEIGHT, 
                                SDL_WINDOW_ALLOW_HIGHDPI);

    if (my_window == NULL)
    {
        fprintf(stderr, "could not create a window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    surface = SDL_GetWindowSurface(my_window);

    /* init surface with 0 */
    SDL_LockSurface(surface);
    SDL_memset(surface->pixels, 0, surface->h * surface->pitch);
    SDL_UnlockSurface(surface);
    SDL_UpdateWindowSurface(my_window);

    /* set pixel in the center of the window to blue */
    pixel.channel[RED] = 0xff;
    pixel.channel[GREEN] = 0xff;
    pixel.channel[BLUE] = 0xff;
    pixel.channel[OPACITY] = 0xff;
    SDL_LockSurface(surface);
    for (int x = 300; x < 450; x++)
    {
        for (int y = 175; y < 325; y++)
        {
            set_pixel(surface, x, y, pixel);
        }
    }
    SDL_UnlockSurface(surface);
    SDL_UpdateWindowSurface(my_window);

    while (TRUE)
    {
        if (SDL_PollEvent(&window_event))
        {
            if (SDL_QUIT == window_event.type)
            {
                break ;
            }
        }
    }
    
    SDL_DestroyWindow(my_window);
    SDL_Quit ();
    return EXIT_SUCCESS;
}
//clang -c src/main.c -o obj/main.o -F/Library/Frameworks
//clang obj/main.o -o fractol -F/Library/Frameworks -framework SDL2

void set_pixel(SDL_Surface *surface, int x, int y, t_pixel pixel)
{
  Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                             + y * surface->pitch
                                             + x * surface->format->BytesPerPixel);
  *target_pixel = pixel.color;
}
