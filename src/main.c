#include "../inc/fractol.h"

int main(void)
{
    t_mystruct      mystruct;
    t_pixel         pixel;

    // initializing SDL2, creating window, creating window surface
    init(&mystruct);

    // choosing colour of pixel
    pix_colour(&pixel);

    // displaying some pixels on window surface
    //surface(&mystruct, &pixel);

    mandelbrot(mystruct.my_window, mystruct.surface, &pixel);

    //making window still on screen untill pressing on "close" button
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

    //SDL_DestroyWindow(mystruct.my_window);
    //SDL_Quit ();
    return EXIT_SUCCESS;
}


//clang -c src/main.c -o obj/main.o -F/Library/Frameworks
//clang obj/main.o -o fractol -F/Library/Frameworks -framework SDL2