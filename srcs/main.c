/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:27:58 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/20 19:11:29 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	player(t_data *data)
{
	int		x;
	int		y;

	x = 250;
	y = 250;
	while (1)
	{
		mlx_pixel_put(data->mlx, data->win, x, y, 0x00FF0000);
		mlx_clear_window(data->mlx, data->win);
	}
	return (1);
}

void	ft_start(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WINDOW_X, WINDOW_Y, "Cub3D");
	player(data);
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
		mlx_loop_hook(data->mlx, player, data);
		mlx_loop(data->mlx);
	}
	else
		ft_error();
}
