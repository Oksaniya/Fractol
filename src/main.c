#include "../inc/fractol.h"

int main(int argc, char **argv)
{
    t_calculation_values      s_calculation_values;

    CLOCK_START;
    fractol_type_ident(argv, &s_calculation_values);
    s_calculation_values.struct_iterators.numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    init(&s_calculation_values, &s_calculation_values.SDL_data);
    SDL_UpdateWindowSurface(s_calculation_values.SDL_data.my_window);
    clock_t end = window_update(&s_calculation_values);
    TIME_SPENT;
    
    return EXIT_SUCCESS;
}