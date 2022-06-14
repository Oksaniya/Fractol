#include <SDL2/SDL.h>

#define TRUE 1
#define WINDOE_WiDTH 750
#define WINDOW_HEIGHT 500

int main(void)
{
    SDL_Window      *my_window;
    SDL_Event       window_event;
    SDL_Surface		*surface;
    char            window_name[] = "my_window";
    uint8_t         *pixels;

    my_window = NULL;
    surface = NULL;
    pixels = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    my_window = SDL_CreateWindow(window_name, 
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, 
                                WINDOE_WiDTH, 
                                WINDOW_HEIGHT, 
                                SDL_WINDOW_ALLOW_HIGHDPI);

    if (my_window == NULL)
    {
        fprintf(stderr, "could not create a window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    surface = SDL_GetWindowSurface(my_window);
    SDL_LockSurface(surface);
    SDL_memset(surface->pixels, 0, surface->h * surface->pitch);
    SDL_UnlockSurface(surface);
    SDL_UpdateWindowSurface(my_window);
    // SDL_FillRect(/*3 arguments*/); // poczytaj na wiki, pyszut szczo szwydsze praciuje niż wrucznu
    //SDL_LockSurface(surface);
    pixels = (uint8_t *)surface->pixels;
    //SDL_UnlockSurface(surface);
    SDL_LockSurface(surface);
    // for (int i = 0; i < 5; i++)
    // {
    //     for (int j = 0; j < 5; j++)
    //     {
    //         pixels[i * surface->pitch + j + 10] = 255;
    //     }
    // }
    //memcpy(surface->pixels, pixels, surface->pitch * surface->h);
    for (int i = 250; i < 500; i++)
    {
        pixels[i + 750] = 255;
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
