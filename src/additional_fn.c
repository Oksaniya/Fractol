#include "../inc/fractol.h"


void if_multithr(t_calculation_values *s_calculation_values, pthread_t *thread_id)
{
    for (int i = 0; i < s_calculation_values->struct_iterators.numCPU; i++) 
    {
        ft_memset((void *)(&thread_id[i]), 0, sizeof(pthread_t));
        s_calculation_values->struct_iterators.iterator = i;
        pthread_create(&thread_id[i], NULL, *coord_calc, ((void *)s_calculation_values));
    }
    for (int i = 0; i < s_calculation_values->struct_iterators.numCPU; i++)
    {
        pthread_join(thread_id[i], NULL);
    }
}

void if_no_multithr(t_calculation_values *s_calculation_values, pthread_t *thread_id)
{
    s_calculation_values->struct_iterators.numCPU = 1;
    s_calculation_values->struct_iterators.iterator = 0;
    coord_calc((void *)s_calculation_values);
}

void fractol_type_ident(char **argv, t_calculation_values *s_calculation_values)
{
    char Julia[] = "julia";
    char Mandelbrot[] = "mandelbrot";

    if (ft_strcmp(argv[1], Mandelbrot) == 0)
    {
        s_calculation_values->struct_iterators.fract_change = 0;
    }
    else if (ft_strcmp(argv[1], Julia) == 0)
    {
        s_calculation_values->struct_iterators.fract_change = 1;
    }
    else
    {
        printf("Pleace enter the name of fractal: %s or %s. \n", Julia, Mandelbrot);
        exit(1);
    }
}

