/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keopsfenks <keopsfenks@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:27:58 by segurbuz          #+#    #+#             */
/*   Updated: 2023/12/07 01:55:50 by keopsfenks       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"
#define DR 0.0174532925
#define PI  3.1415926535
#define P2  PI/2
#define P3  3*PI/2
#define S 115
#define W 119
#define A 97
#define D 100

float px,py,pdx,pdy,pa; // player position


int abs(int n) { return ((n > 0) ? n : (n * (-1))); } 

void DDA(int X0, int Y0, int X1, int Y1, t_data *data)
{
    int dx = X1 - X0;
    int dy = Y1 - Y0;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++) {
		mlx_pixel_put(data->mlx, data->win, X + 20, Y + 20, 0xFF0000);
        X += Xinc;
        Y += Yinc;
    }
}

int	key_event(int keycode, t_data *data)
{
	if (keycode == W)
	{
		data->p_y += pdy;
		data->p_x += pdx;
	}
	else if (keycode == S)
	{
		data->p_y -= pdy;
		data->p_x -= pdx;	
	}
	else if (keycode == A)
	{
		pa-= 0.1;
		if (pa < 0)
			pa += 2*PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
		data->pl_a -= pa * 5 ;
	}
	else if (keycode == D)
	{
		pa+= 0.1;
		if (pa > 2*PI)
			pa -= 2*PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
		data->pl_a += pa * 5;
	}
	else if (keycode == 65307)
	{
		printf("\n***exit***\n\n");
		exit(0);
	}
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->player, data->p_x, data->p_y);
	DDA(data->p_x - 12 , data->p_y - 12, data->p_x + pdx * 100, data->p_y + pdy * 100, data);
	// gidilen yönün açısını bulup giden çizgiyi yönlendirmemiz lazım.
	return (0);
}

void	ft_start(t_data *data)
{
	int	w;
	
	w = 0;
	if (w == 1)
		return ;
	data->p_x = 64;
	data->p_y = 64;
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
	data->pl_a = 0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WINDOW_X, WINDOW_Y, "Cub3D");
	data->floor = mlx_xpm_file_to_image(data->mlx, "srcs/texture/floor.xpm", &w, &w);	
	data->wall = mlx_xpm_file_to_image(data->mlx, "srcs/texture/wall.xpm", &w, &w);
	data->player = mlx_xpm_file_to_image(data->mlx, "srcs/texture/player.xpm", &w, &w);
	
	mlx_put_image_to_window(data->mlx, data->win, data->player, 16, 16);

}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		data = ft_calloc(sizeof(t_data), 1);
		data->attr = ft_calloc(sizeof(t_attr), 1);
		data->map_arg = av[1];
		ft_parse(data);
		ft_start(data);
		mlx_hook(data->win, 2, 1L << 0, &key_event, data);
		mlx_loop(data->mlx);
	}
	else
		ft_error();
}
