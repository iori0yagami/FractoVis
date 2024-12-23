/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:57:31 by sabadri           #+#    #+#             */
/*   Updated: 2024/12/20 15:16:07 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include <mlx.h>
#include "fractol.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void generate_julia(t_data *data)
{
    int x, y;
    double real, imag;
    double real_temp;
    int max_iter = 100;
    int color;
    int iteration;

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            real = (x - (double)WIDTH / 2) / (0.5 * data->zoom * (double)WIDTH) + data->move_x;
            imag = (y - (double)HEIGHT / 2) / (0.5 * data->zoom * (double)HEIGHT) + data->move_y;

            iteration = 0;
            while (real * real + imag * imag <= 4.0 && iteration < max_iter)
            {
                real_temp = real * real - imag * imag + data->cr;
                imag = 2 * real * imag + data->ci;
                real = real_temp;
                iteration++;
            }

            if (iteration == max_iter)
                color = 0xFFFFFF;
            else
            {
                int red = (iteration * 5 + 120) % 256;
                int green = (iteration * 7 + 550) % 256;
                int blue = (iteration * 3 + 290) % 256;
                color = 0x0000FF | (red << 16) | (green << 8) | blue;
            }
            my_mlx_pixel_put(data, x, y, color);
        }
    }
}

void generate_mandelbrot(t_data *data)
{
    int x, y;
    double real, imag;
    double real_temp;
    int max_iter = 100;
    int color;
    int iteration;

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            real = (x - (double)WIDTH / 2) / (0.5 * data->zoom * (double)WIDTH) + data->move_x;
            imag = (y - (double)HEIGHT / 2) / (0.5 * data->zoom * (double)HEIGHT) + data->move_y;

            iteration = 0;
            double r = 0.0, i = 0.0;

            while (r * r + i * i <= 4.0 && iteration < max_iter)
            {
                double temp = r * r - i * i + real;
                i = 2 * r * i + imag;
                r = temp;
                iteration++;
            }
            if (iteration == max_iter)
                color = 0x00;
            else
            {
                int red = (iteration * 6 + 120) % 256;
                int green = (iteration * 9 + 550) % 256;
                int blue = (iteration * 4 + 290) % 256;
                color = 0x00000000 | (red << 16) | (green << 8) | blue;
            }
            my_mlx_pixel_put(data, x, y, color);
        }
    }
}

int key_hook(int keycode, t_data *data)
{
    if (keycode == 126)
    {
        data->move_y -= 0.1 / data->zoom;
    }
    else if (keycode == 125)
    {
        data->move_y += 0.1 / data->zoom;
    }
    else if (keycode == 123)
    {
        data->move_x -= 0.1 / data->zoom;
    }
    else if (keycode == 124)
    {
        data->move_x += 0.1 / data->zoom;
    }
    else if (keycode == 53)
    {
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
    if (ft_strcmp(data->type, "julia") == 0)
        generate_julia(data);
    else
        generate_mandelbrot(data);

    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return (0);
}

int mouse_hook(int button, int x, int y, t_data *data)
{
    double mr, mi;
    double prev_mr, prev_mi;
    
    prev_mr = (x - (double)WIDTH / 2) / (0.5 * data->zoom * (double)WIDTH + data->move_x);
    prev_mi = (y - (double)HEIGHT / 2) / (0.5 * data->zoom * (double)HEIGHT + data->move_y);
    
    if (button == 4)
        data->zoom /= 1.1;
    else if (button == 5)
        data->zoom *= 1.1;
    
    mr = (x - (double)WIDTH / 2) / (0.5 * data->zoom * (double)WIDTH + data->move_x);
    mi = (y - (double)HEIGHT / 2) / (0.5 * data->zoom * (double)HEIGHT + data->move_y);
    
    data->move_x += prev_mr - mr;
    data->move_y += prev_mi - mi;
    
    if (ft_strcmp(data->type, "julia") == 0)
        generate_julia(data);
    else
        generate_mandelbrot(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return 0;
}


int main(int ac, char **av)
{
    void *mlx;
    void *mlx_win;
    t_data fractol;

    if (ac == 2 && !strcmp(av[1], "Mandelbrot") || (ac == 4 && !strcmp(av[1], "julia")))
    {
        mlx = mlx_init();
        if (!mlx)
        {
            ft_error("MLX initialization failed");
            return (1);
        }

        mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Fractal");

        fractol.img = mlx_new_image(mlx, WIDTH, HEIGHT);
        fractol.addr = mlx_get_data_addr(fractol.img, &fractol.bits_per_pixel, &fractol.line_length, &fractol.endian);
        fractol.mlx = mlx;
        fractol.win = mlx_win;
        fractol.zoom = 1.0;
        fractol.move_x = 0.0;
        fractol.move_y = 0.0;

        if (!strcmp(av[1], "julia"))
        {
            fractol.type = "julia";
            fractol.cr = .42;
            fractol.ci = .42;
            generate_julia(&fractol);
        }
        else
        {
            fractol.type = "mandelbrot";
            generate_mandelbrot(&fractol);
        }
        mlx_key_hook(mlx_win, key_hook, &fractol);
        mlx_mouse_hook(mlx_win, mouse_hook, &fractol);
        mlx_put_image_to_window(mlx, mlx_win, fractol.img, 0, 0);
        mlx_loop(mlx);
    }
    else
    {
        ft_error("Usage: ./fractol Mandelbrot or Julia");
        return (1);
    }
    return (0);
}
