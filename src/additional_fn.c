#include "../inc/fractol.h"


void if_multithr(t_mystruct *mystruct, pthread_t *thread_id)
{
    for (int i = 0; i < mystruct->numCPU; i++) 
    {
        ft_memset((void *)(&thread_id[i]), 0, sizeof(pthread_t));
        mystruct->iterator = i;
        pthread_create(&thread_id[i], NULL, *coord_calc, ((void *)mystruct));
    }
    for (int i = 0; i < mystruct->numCPU; i++)
    {
        pthread_join(thread_id[i], NULL);
    }
}

void if_no_multithr(t_mystruct *mystruct, pthread_t *thread_id)
{
    mystruct->numCPU = 1;
    mystruct->iterator = 0;
    coord_calc((void *)mystruct);
}

void fractol_type_ident(char **argv, t_mystruct *mystruct)
{
    char Julia[] = "julia";
    char Mandelbrot[] = "mandelbrot";

    if (ft_strcmp(argv[1], Mandelbrot) == 0)
    {
        mystruct->fract_change = 0;
    }
    else if (ft_strcmp(argv[1], Julia) == 0)
    {
        mystruct->fract_change = 1;
    }
    else
    {
        printf("Pleace enter the name of fractal: %s or %s. \n", Julia, Mandelbrot);
        exit(1);
    }
}

