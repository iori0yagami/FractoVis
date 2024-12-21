/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:45:31 by sabadri           #+#    #+#             */
/*   Updated: 2024/12/20 13:09:46 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int ft_strncmp(char *s1, char *s2, int n)
{
    int i = 0;

    while (i < n && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
        i++;
    if (i == n)
        return 0;
    else
        return (unsigned char)s1[i] - (unsigned char)s2[i];
}


void    ft_putstr_fd(char *s1, int fd)
{
    int i;
    i = 0;
    while (s1[i])
    {
        write(fd,&s1[i],1);
        i++;
    }
}

void ft_error()
{
    write(1,"Enter a valid set name \n", 25);
}

// void generate_mandelbrot(t_data *data)
// {
//     int x, y;
//     double real, imag;
//     double real_temp;
//     int max_iter = 1000;
//     double zoom = 1.0;
//     double move_x = 0.0;
//     double move_y = 0.0;
//     int color;

//     for (y = 0; y < HEIGHT; y++)
//     {
//         for (x = 0; x < WIDTH; x++)
//         {
//             real = (x - WIDTH / 2) / (0.5 * zoom * WIDTH) + move_x;
//             imag = (y - HEIGHT / 2) / (0.5 * zoom * HEIGHT) + move_y;
//             int i = 0;
//             double real_sq = real * real;
//             double imag_sq = imag * imag;
//             while (real_sq + imag_sq <= 4 && i < max_iter)
//             {
//                 real_temp = real_sq - imag_sq + 0.66;
//                 imag = 2 * real * imag + 0.33;
//                 real = real_temp;
//                 real_sq = real * real;
//                 imag_sq = imag * imag;
//                 i++;
//             }
//             color = (i == max_iter) ? 0x000000 : (i * 255 / max_iter) << 16;
//             my_mlx_pixel_put(data, x, y, color);
//         }
//     }
// }
