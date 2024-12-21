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

// include/fractol.h

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define WIDTH 1080
# define HEIGHT 1080

typedef struct s_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               t_data;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    ft_error();

#endif
