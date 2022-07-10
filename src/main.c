#include "../inc/fractol.h"

int main(void)
{
    t_mystruct      mystruct;
    pthread_t       *thread_id;

    clock_t         begin;
    clock_t         end;

    int mouse_x_prev, mouse_y_prev;
    
    mouse_x_prev = 0;
    mouse_y_prev = 0;
    // clock init
    begin = clock();

    mystruct.numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    thread_id = (pthread_t *)malloc(sizeof(pthread_t) * mystruct.numCPU);
    //printf("Number of free cores are: %d \n", mystruct.numCPU);

    // initializing SDL2, creating window, creating window surface
    init(&mystruct);

    // calculating pixel coordinates from index and call fractol function
#ifndef MULTITHREAD
    mystruct.numCPU = 1;
    mystruct.iterator = 0;
    coord_calc((void *)&mystruct);

#else
    for (int i = 0; i < mystruct.numCPU; i++) 
    {
        //ft_memset((void *)thread_id[i], 0, sizeof(pthread_t));
        mystruct.iterator = i;
        pthread_create(&thread_id[i], NULL, coord_calc, ((void *)&mystruct));
    }
    for (int i = 0; i < mystruct.numCPU; i++)
    {
        pthread_join(thread_id[i], NULL);
    }
#endif

    // time calculation
    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time = %f \n", time_spent);
    
    SDL_UpdateWindowSurface(mystruct.my_window);
    //making window still on screen untill pressing on "close" button
    while (TRUE)
    {
        mystruct.Mouse_pos = SDL_GetMouseState(&mystruct.mouse_x, &mystruct.mouse_y);
        //printf(" (!!!) Mouse_pos = %u\tmouse_x = %d\tmouse_y = %d\n", mystruct.Mouse_pos, mystruct.mouse_x, mystruct.mouse_y);
        if (mystruct.mouse_x != mouse_x_prev || mystruct.mouse_y != mouse_y_prev)
        {
#ifndef MULTITHREAD
            mystruct.numCPU = 1;
            mystruct.iterator = 0;
            coord_calc((void *)&mystruct);

#else
            for (int i = 0; i < mystruct.numCPU; i++) 
            {
                //ft_memset((void *)thread_id[i], 0, sizeof(pthread_t));
                mystruct.iterator = i;
                pthread_create(&thread_id[i], NULL, coord_calc, ((void *)&mystruct));
            }
            for (int i = 0; i < mystruct.numCPU; i++)
            {
                pthread_join(thread_id[i], NULL);
            }
#endif
            SDL_UpdateWindowSurface(mystruct.my_window);
            mouse_x_prev = mystruct.mouse_x;
            mouse_y_prev = mystruct.mouse_y;
            //printf("Mouse_pos = %u\tmouse_x = %d\tmouse_y = %d\n", mystruct.Mouse_pos, mystruct.mouse_x, mystruct.mouse_y);
        }
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

void *coord_calc(void *my_s)
{
    int Px;
    int Py;
    int i;
    int increment;
    t_mystruct *mystruct;

    mystruct = my_s;
    i = mystruct->iterator;
    increment = mystruct->numCPU;
    while (i < mystruct->pix_num)
    {
        Py = i / WINDOW_WIDTH;
        Px = i % WINDOW_WIDTH;
        //mandelbrot(mystruct, Px, Py);
        julia(mystruct, Px, Py);
        i += increment;
    }
    return NULL;
}


//clang -c src/main.c -o obj/main.o -F/Library/Frameworks
//clang obj/main.o -o fractol -F/Library/Frameworks -framework SDL2

//time = 1.726272 - no threads 