#include "../inc/fractol.h"

int main(int argc, char **argv)
{
    t_mystruct      mystruct;

    CLOCK_START;
    fractol_type_ident(argv, &mystruct);
    mystruct.numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    init(&mystruct, &mystruct.SDL_data);
    SDL_UpdateWindowSurface(mystruct.SDL_data.my_window);
    clock_t end = win_still_and_update(&mystruct);
    TIME_SPENT;
    
    return EXIT_SUCCESS;
}