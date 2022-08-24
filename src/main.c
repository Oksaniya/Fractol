#include "../inc/fractol.h"

int main(int argc, char **argv)
{
    t_mystruct      mystruct;
    pthread_t       *thread_id;

    clock_t         begin;
    clock_t         end;

    int_fast64_t mouse_x_prev, mouse_y_prev;
    char Julia[] = "julia";
    char Mandelbrot[] = "mandelbrot";
    int_fast64_t zero = 0;
    
    mouse_x_prev = 0;
    mouse_y_prev = 0;
    // clock init
    begin = clock();

    if (ft_strcmp(argv[1], Mandelbrot) == 0)
    {
        mystruct.fract_change = 0;
    }
    else if (ft_strcmp(argv[1], Julia) == 0)
    {
        mystruct.fract_change = 1;
    }
    else
    {
        printf("Pleace enter the name of fractal: %s or %s. \n", Julia, Mandelbrot);
        return EXIT_FAILURE;
    }

    mystruct.numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    
    //printf("Number of free cores are: %d \n", mystruct.numCPU);

    // initializing SDL2, creating window, creating window surface
    init(&mystruct, &mystruct.SDL_data);
    thread_id = (pthread_t *)malloc(sizeof(pthread_t) * mystruct.numCPU);

    // calculating pixel coordinates from index and call fractol function
#ifndef MULTITHREAD
    if_no_multithr(&mystruct, *thread_id);

#else
   if_multithr(&mystruct, thread_id);
    
#endif

    // time calculation
    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time = %f \n", time_spent);

    SDL_UpdateWindowSurface(mystruct.SDL_data.my_window);
    //making window still on screen untill pressing on "close" button

    while (TRUE)
    {
        mystruct.Mouse_pos = SDL_GetMouseState(&mystruct.mouse_x, &mystruct.mouse_y);
        //printf(" (!!!) Mouse_pos = %u\tmouse_x = %d\tmouse_y = %d\n", mystruct.Mouse_pos, mystruct.mouse_x, mystruct.mouse_y);
        if (mystruct.mouse_x != mouse_x_prev || mystruct.mouse_y != mouse_y_prev)
        {
#ifndef MULTITHREAD
            if_no_multithr(&mystruct, *thread_id);

#else
            if_multithr(&mystruct, thread_id);
#endif
            SDL_UpdateWindowSurface(mystruct.SDL_data.my_window);
            mouse_x_prev = mystruct.mouse_x;
            mouse_y_prev = mystruct.mouse_y;
            //printf("Mouse_pos = %u\tmouse_x = %d\tmouse_y = %d\n", mystruct.Mouse_pos, mystruct.mouse_x, mystruct.mouse_y);
        }
        if (SDL_PollEvent(&(mystruct.SDL_data.window_event)))
        {
            if (SDL_QUIT == mystruct.SDL_data.window_event.type)
            {
                break ;
            }
        }
    }
    //SDL_DestroyWindow(SDL_struct.my_window);
    //SDL_Quit ();
    return EXIT_SUCCESS;
}

void *coord_calc(void *my_s)
{
    int32_t i;
    int64_t increment;
    t_mystruct *mystruct;
    t_SDL_struct SDL_struct;

    mystruct = (t_mystruct *)my_s;
    SDL_struct = mystruct->SDL_data;
    mystruct->Px = 0.0f;
    mystruct->Py = 0.0f;
    mystruct = my_s;
    i = mystruct->iterator * (WINDOW_WIDTH * WINDOW_HEIGHT / mystruct->numCPU);
    increment = mystruct->numCPU;
    while (i < mystruct->pix_num)
    {
        mystruct->Py = i / WINDOW_WIDTH;
        mystruct->Px = i % WINDOW_WIDTH;

        switch (mystruct->fract_change)
        {
        case 0:
            mandelbrot(mystruct, &SDL_struct);
            break;
        case 1:
            julia(mystruct, &SDL_struct);
        default:
            break;
        }

        i += increment;
    }
    return NULL;
}

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

void if_no_multithr(t_mystruct *mystruct, pthread_t thread_id)
{
    mystruct->numCPU = 1;
    mystruct->iterator = 0;
    coord_calc((void *)mystruct);
}

//clang -c src/main.c -o obj/main.o -F/Library/Frameworks
//clang obj/main.o -o fractol -F/Library/Frameworks -framework SDL2

//time = 1.726272 - no threads 