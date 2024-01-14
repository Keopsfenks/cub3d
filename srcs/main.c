#include "./includes/cub3d.h"
#define DR 0.0174532925
#define PI  3.14159265
#define S 115
#define W 119
#define A 97
#define D 100

float px,py,pdx,pdy; // player position

float pa = 1.3;

/*int mapX=10, mapY=10, mapS=100;
int map[]=
{
	1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,0,0,0,0,1,
	1,0,0,0,1,0,0,0,0,1,
	1,0,0,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,
};*/

void draw2Dmap(t_data *data)
{
	int 	x;
	int 	y;

	x = 0;
	y = 0;
	while (data->attr->arr_map[y])
	{
		x = 0;
		while (data->attr->arr_map[y][x])
		{
			if (data->attr->arr_map[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->wall_img, (x*64), (y*64)); // warn
			else if (data->attr->arr_map[y][x] == '0')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->floor_img, (x*64), (y*64)); // warn
			x++;
		}

		y++;
	}
}


void	img_pix_put(t_image *image, int x, int y, int color)
{
	char	*pixel;

	pixel = image->data + (y * image->sizeline + x * (image->bpp / 8));
	*(int *)pixel = color;
}

unsigned int	get_pixel_in_texture(t_texture *texture, int x, int y)
{
	char	*re;

	re = texture->data + (y * texture->sizeline + x * (texture->bpp / 8));
	return (*((unsigned int *)re));
}


// void	calc_texture_pixel_color(t_data *data)
// {
// 	int	color;

// 	color = 0;
// 		img_pix_put(&data->img, data->x, data->y, 0xFFFFF);
// }


void draw3DView(t_data *data, int numRays) {
    float wallHeight = data->windowHeight * 10;

    int windowWidth = data->windowWidth; // upd from data 
    int windowHeight = data->windowHeight; // upd from data

    for (int i = 0; i < numRays; i++) {
        float distanceToWall = data->distances[i];
		// printf("orta cizgi uzunluk -> %f en sağ çizgi uzunluk -> %f en sol --> %f \n", data->distances[29], data->distances[59], data->distances[0]);

        float wallSize = (1 / distanceToWall) * wallHeight;
        float wallThickness = (1 / distanceToWall);

        int wallCenter = windowHeight / 2;

        float wallStart = wallCenter - (wallSize) * 2;
        float wallEnd = wallCenter + (wallSize) * 2;

        int wallThicknessStart = i - (wallThickness);
        int wallThicknessEnd = i + (wallThickness);

        int wallColor = 0x402414;
		if (wallStart < 0)
			wallStart = 0;
		if (wallEnd > wallHeight)
			wallEnd = wallHeight - 1;
		// printf("wallsize -> %f\n", wallSize);
        for (int j = wallStart; j <= wallEnd; j++)
		{
            for (int k = wallThicknessStart * 0.001670 * (windowWidth) ; k <= wallThicknessEnd * 0.001670 * (windowWidth); k++)
			{
				float wall_tes = (((j) - (wallStart)) * 14) / (wallSize);
				wallColor = get_pixel_in_texture(&data->textures[0], (data->wall_X[i]) * 64, wall_tes);
				if (data->wall_direction[i] == 1)
					img_pix_put(&data->image, k, j, wallColor);
				else if (data->wall_direction[i] == 3)
					img_pix_put(&data->image, k, j, wallColor);
				else
				{
					wallColor = get_pixel_in_texture(&data->textures[1], (data->wall_Y[i]) * 64, wall_tes);
					img_pix_put(&data->image, k, j, wallColor);
				}
				// if (data->wall_direction[i] == 0)
				// 	data->wall_direction[i] = data->wall_direction[i-1];
				// if (data->wall_direction[i] == 3)
                // 	mlx_pixel_put(data->mlx, data->mlx_win, k + (windowWidth / 2), j, 0xFFFF00);
				// else if (data->wall_direction[i] == 1)
                // 	mlx_pixel_put(data->mlx, data->mlx_win, k + (windowWidth / 2), j, 0xFF0000);
                // 	mlx_pixel_put(data->mlx, data->mlx_win, k + (windowWidth / 2), j, 0xFFFFFF);
                // 	mlx_pixel_put(data->mlx, data->mlx_win, k + (windowWidth / 2), j, wallColor);
            }
        }
    }
}

int jd = 0;

int abs(int n) { return ((n > 0) ? n : (n * (-1))); } 

void DDA(int X0, int Y0, int X1, int Y1, t_data *data)
{
    int dx = X1 - X0;
    int dy = Y1 - Y0;
	int num = -1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
	int yon = 0;

//  +20 for player pos
    float X = X0 + 20; // starting position of the line X
    float Y = Y0 + 20; // starting position of the line Y
    while (1) {
		if (data->attr->arr_map[(int)(Y) / 64][(int)(X) / 64] != '1')
			;
			//mlx_pixel_put(data->mlx, data->mlx_win, X, Y, 0xFF0000);
		else // wall
		{
			// printf("wall %d\n", map[(((int)(Y) / 64) * mapY) + (int)((X-5) / 64)]);
			if (data->attr->arr_map[(int)(Y) / 64][(int)(X-1) / 64] == '0' && data->attr->arr_map[(int)(Y+1) / 64][(int)(X) / 64] == '1')
				yon = 2;
			else if (data->attr->arr_map[(int)(Y) / 64][(int)(X+1) / 64] == '0' && data->attr->arr_map[(int)(Y-1) / 64][(int)(X) / 64] == '1')
				yon = 4;
			else if (data->attr->arr_map[(int)(Y+1) / 64][(int)(X) / 64] == '0' && data->attr->arr_map[(int)(Y) / 64][(int)(X-1) / 64] == '1')
				yon = 1;
			else if (data->attr->arr_map[(int)(Y-1) / 64][(int)(X) / 64] == '0' && data->attr->arr_map[(int)(Y) / 64][(int)(X+1) / 64] == '1')
				yon = 3;
			// printf("\n\n\n player x -> %f player y -> %f\n", data->p_x + 8 , data->p_y + 8);
			// printf(" *** x-> %f y-> %f\n", X + 20, Y + 20);
			// printf("\n çizginin uzunluğu ---->>> %f \n", sqrt(pow(data->p_x + 8 - X + 20, 2) + pow(data->p_y + 8 - Y + 20, 2)) );
			// printf("pdx-> %f pdy-> %f\n", pdx, pdy);
			// mlx_pixel_put(data->mlx, data->mlx_win, X, Y, 0xFFFFFF);
			// printf("x in karesi + y nin karesinin karekoku -> %d \n",(int)sqrt(pow(data->p_x, 2) + pow((int)Y, 2)));
			break;
		}
        X += Xinc;
        Y += Yinc;
    }
	data->distances[jd] = (sqrt(pow(data->p_x + 8 - X, 2) + pow(data->p_y + 8 - Y, 2)) * cos(data->currentAngle - pa));
	data->wall_direction[jd] = yon;
	float cellX = (X / 64);
	float cellY = (Y / 64);
	data->wall_X[jd] = cellX;
	data->wall_Y[jd] = cellY;
	jd++;
}

void put_background(t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y <= data->windowHeight / 2)
	{
		x = 0;
		while (x <= data->windowWidth)
		{
			img_pix_put(&data->image, x, y, data->skyc);
			x++;
		}
		y++;
	}
	while (y <= data->windowHeight)
	{
		x = 0;
		while (x <= data->windowWidth)
		{
			img_pix_put(&data->image, x, y, data->floorc);
			x++;
		}
		y++;
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
	else if (keycode == 53)
	{
		printf("\n***exit***\n\n");
		exit(0);
	}
	mlx_clear_window(data->mlx, data->mlx_win);
	//draw2Dmap(data);
	//mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, data->p_x, data->p_y);
	jd = 0;
	for (float i = -30; i <= 30; i+= 0.1) {
		data->currentAngle = pa + (i * DR); // pov
		float endX = data->p_x - 12 + cos(data->currentAngle) * 1024;
		float endY = data->p_y - 12 + sin(data->currentAngle) * 1024;
		DDA(data->p_x - 12 , data->p_y - 12, (int)endX, (int)endY, data);
	}
	// drawCeiling(data);
	// drawFloor(data);
	put_background(data);
	draw3DView(data, 600);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image.window, 0, 0);
	return (0);
}

void ft_init(t_data *data)
{
	int w = 0;

	data->distances = malloc(sizeof(float) * 600);
	data->wall_direction = malloc(sizeof(int) * 600);
	data->windowWidth = 1280;
	data->windowHeight = 1024;
	data->wall_X = calloc(sizeof(float), 600);
	data->wall_Y = calloc(sizeof(float), 600);
	data->attr = ft_calloc(sizeof(t_attr), 1);
	pdx = 0;
	pdy = 0;
	data->pl_a = 0;
	data->mlx = mlx_init();
	data->currentAngle = 0.0;
	data->mlx_win = mlx_new_window(data->mlx, data->windowWidth, data->windowHeight, "faruktinaz raycasting");

}

void	create_rgb(char *line, enum e_map type, t_data *data)
{
	int 	color[3];
	int 	i;
	int 	j;
	int 	result;

	i = -1;
	result = 0;
	j = 0;
	while (line[++i])
	{
		while (line[i] && ft_isdigit(line[i]))
		{
			result = (result * 10) + (line[i] - '0');
			i++;
		}
		color[j] = result;
		result = 0;
		j++;
	}
	if (type == CEILING)
		data->skyc = (color[0] << 16 | color[1] << 8 | color[2]);
	else if (type == FLOOR)
		data->floorc = (color[0] << 16 | color[1] << 8 | color[2]);

}

void	draw_utils(t_data *data)
{
	int w;

	w = 0;
	data->image.window = mlx_new_image(data->mlx, data->windowWidth, data->windowHeight);
	data->image.data = mlx_get_data_addr(data->image.window, &data->image.bpp, &data->image.sizeline, &data->image.endian);

	data->img = mlx_xpm_file_to_image(data->mlx, "srcs/texture/player.xpm", &w, &w);
	data->textures[0].image = mlx_xpm_file_to_image(data->mlx, "srcs/texture/enemy.xpm", &w, &w);
	data->textures[0].data = mlx_get_data_addr(data->textures[0].image, &data->textures[0].bpp, &data->textures[0].sizeline, &data->textures[0].endian);
	data->textures[1].image = mlx_xpm_file_to_image(data->mlx, "srcs/texture/enem2y.xpm", &w, &w);
	data->textures[1].data = mlx_get_data_addr(data->textures[1].image, &data->textures[1].bpp, &data->textures[1].sizeline, &data->textures[1].endian);

	data->wall_img = mlx_xpm_file_to_image(data->mlx, "srcs/texture/wall.xpm", &w, &w);
	data->floor_img = mlx_xpm_file_to_image(data->mlx, "srcs/texture/floor.xpm", &w, &w);
	data->enemy_img = mlx_xpm_file_to_image(data->mlx, "srcs/texture/enemy.xpm", &w, &w);
	data->c_img = mlx_xpm_file_to_image(data->mlx, "srcs/texture/c.xpm", &w, &w);

	while (data->attr->color)
	{
		create_rgb(data->attr->color->line, data->attr->color->type, data);
		data->attr->color = data->attr->color->next;
	}
}


int main(int ac, char **av)
{

	t_data *data = malloc(sizeof(t_data));
	ft_init(data);
	data->map_arg = av[1];
	ft_parse(data);
	draw_utils(data);
	draw2Dmap(data);
	// while (y++ < 100)
	// {
	// 	x = 0;
	// 	while (x++ < 100)
	// 		mlx_pixel_put(data->mlx, data->mlx_win, x, y, 0xFFFFFF);
	// }
	mlx_hook(data->mlx_win, 2, 1L << 0, &key_event, data);
	mlx_loop(data->mlx);
}



// ** For Linux **
// gcc main.c mlx/libmlx.a -L./mlx -lmlx -L/usr/lib -I/usr/include -lXext -lX11 -lm -lz
// ** For macOS **
// gcc test.c -framework AppKit -framework OpenGL -L./mlx -lmlx -o 2dcub