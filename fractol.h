/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:45:56 by sabadri           #+#    #+#             */
/*   Updated: 2024/12/20 13:09:37 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */





#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define WIDTH 1080
# define HEIGHT 1080

typedef struct s_data {
    void    *mlx;           
    void    *win;           
    void    *img;           
    char    *addr;         
    int     bits_per_pixel; // Number of bits per pixel
    int     line_length;    // Line length of the image
    int     endian;         // Endianness of the image
    double  zoom;           // Current zoom level
    double  move_x;         // Current horizontal offset
    double  move_y;         // Current vertical offset
    double  cr;             // Real part of the constant for Julia set
    double  ci;             // Imaginary part of the constant for Julia set
    char    *type;          // Fractal type (e.g., "julia", "mandelbrot")
}               t_data;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    generate_julia(t_data *data);
void    generate_mandelbrot(t_data *data);
void    ft_putstr_fd(char *s1, int fd);
int     ft_strcmp(char *s1, char *s2);
void    ft_error(const char *msg);
int     key_hook(int keycode, t_data *data);

#endif
















// // include/fractol.h

// #ifndef FRACTOL_H
// # define FRACTOL_H

// # include "mlx.h"
// # include <stdlib.h>
// # include <stdio.h>
// # include <unistd.h>

// # define WIDTH 1080
// # define HEIGHT 1080

// typedef struct s_data {
//     void    *img;
//     char    *addr;
//     int     bits_per_pixel;
//     int     line_length;
//     double  zoom;
//     double  move_x;
//     double  move_y;
//     double  cr;
//     double  ci;
//     int     endian;
// }               t_data;

// void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
// void    ft_error();

// #endif
