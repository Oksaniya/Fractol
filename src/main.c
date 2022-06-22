#include "../inc/fractol.h"

int main(void)
{
    t_mystruct      mystruct;
    t_pixel         pixel;

    init(&mystruct);
    pix_colour(&pixel);
    surface(&mystruct, &pixel);

    while (TRUE)
    {
        if (SDL_PollEvent(&(mystruct.window_event)))
        {
            if (SDL_QUIT == mystruct.window_event.type)
            {
                break ;
            }
        }
    }

    SDL_DestroyWindow(mystruct.my_window);
    SDL_Quit ();
    return EXIT_SUCCESS;
}


//clang -c src/main.c -o obj/main.o -F/Library/Frameworks
//clang obj/main.o -o fractol -F/Library/Frameworks -framework SDL2