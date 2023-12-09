/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keopsfenks <keopsfenks@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:27:58 by segurbuz          #+#    #+#             */
/*   Updated: 2023/12/10 02:23:41 by keopsfenks       ###   ########.fr       */
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
#define ESC 65307


int mapX=8, mapY=8, mapS=64;
int map[]=
{
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

float degToRad(int a) { return a*PI/180.0;}
int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}
//float disTance(ax,ay,bx,by,ang){ return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);}

void	ft_start(t_data *data)
{
	int w;

	w = 0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WINDOW_X, WINDOW_Y, "Cub3D");
	data->var.px = 64; 
	data->var.py = 64; 
	data->var.pa = 90;
	data->var.pa = cos(degToRad(data->var.pa));
	data->var.pa =- sin(degToRad(data->var.pa));
	data->floor = mlx_xpm_file_to_image(data->mlx, "srcs/texture/floor.xpm", &w, &w);
	data->wall = mlx_xpm_file_to_image(data->mlx, "srcs/texture/wall.xpm", &w, &w);
	data->player = mlx_xpm_file_to_image(data->mlx, "srcs/texture/player.xpm", &w, &w);
}

void drawMap2D(t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < mapY)
	{
		x = 0;
		while (x < mapX)
		{
			if (map[y*mapX+x] == 1)
				mlx_put_image_to_window(data->mlx, data->win, data->wall, (x*64), (y*64)); // warn
			else if (map[y*mapX+x] == 0)
				mlx_put_image_to_window(data->mlx, data->win, data->floor, (x*64), (y*64)); // warn
			x++;
		}
		y++;
	}
}

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
		if (map[(((int)(Y+20) / 64) * mapY) + (int)((X+20) / 64)] != 1)
        	mlx_pixel_put(data->mlx, data->win, X + 20, Y + 20, 0xFF0000);
		else
			break;
        X += Xinc;
        Y += Yinc;
    }
}

void drawPlayer2D(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->player, data->var.px, data->var.py);
	DDA(data->var.px - 12, data->var.py - 12, data->var.px + data->var.pdx * 95, data->var.py + data->var.pdy * 95, data);
	DDA(data->var.px - 13, data->var.py - 13, data->var.px + data->var.pdx * 95, data->var.py + data->var.pdy * 95, data);
	DDA(data->var.px - 11, data->var.py - 11, data->var.px + data->var.pdx * 95, data->var.py + data->var.pdy * 95, data);}

void	drawRays3D(t_data *data)
{
//  glColor3f(0,1,1); glBegin(GL_QUADS); glVertex2i(526,  0); glVertex2i(1006,  0); glVertex2i(1006,160); glVertex2i(526,160); glEnd();	
//  glColor3f(0,0,1); glBegin(GL_QUADS); glVertex2i(526,160); glVertex2i(1006,160); glVertex2i(1006,320); glVertex2i(526,320); glEnd();	 	
	DDA(536, 0, 1006, 0, data);
	DDA(536, 160, 1006, 160, data);
	DDA(536, 320, 1006, 320, data);
	DDA(536, 0, 536, 320, data);
 int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
 
 ra=FixAng(data->var.pa+30);                                                              //ray set back 30 degrees
 
 for(r=0;r<60;r++)
 {
  //---Vertical--- 
  dof=0; side=0; disV=100000;
  float Tan=tan(degToRad(ra));
       if(cos(degToRad(ra))> 0.001){ rx=(((int)data->var.px>>6)<<6)+64;      ry=(data->var.px-rx)*Tan+data->var.py; xo= 64; yo=-xo*Tan;}//looking left
  else if(cos(degToRad(ra))<-0.001){ rx=(((int)data->var.px>>6)<<6) -0.0001; ry=(data->var.px-rx)*Tan+data->var.py; xo=-64; yo=-xo*Tan;}//looking right
  else { rx=data->var.px; ry=data->var.py; dof=8;}                                                  //looking up or down. no hit  

  while(dof<8) 
  { 
   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
   if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-data->var.px)-sin(degToRad(ra))*(ry-data->var.py);}//hit         
   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  } 
  vx=rx; vy=ry;

  //---Horizontal---
  dof=0; disH=100000;
  Tan=1.0/Tan; 
       if(sin(degToRad(ra))> 0.001){ ry=(((int)data->var.py>>6)<<6) -0.0001; rx=(data->var.py-ry)*Tan+data->var.px; yo=-64; xo=-yo*Tan;}//looking up 
  else if(sin(degToRad(ra))<-0.001){ ry=(((int)data->var.py>>6)<<6)+64;      rx=(data->var.py-ry)*Tan+data->var.px; yo= 64; xo=-yo*Tan;}//looking down
  else{ rx=data->var.px; ry=data->var.py; dof=8;}                                                   //looking straight left or right
 
  while(dof<8) 
  { 
   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
   if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disH=cos(degToRad(ra))*(rx-data->var.px)-sin(degToRad(ra))*(ry-data->var.py);}//hit         
   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  } 
  
//   glColor3f(0,0.8,0);
  if(disV<disH){ rx=vx; ry=vy; disH=disV;}                  //horizontal hit first
//   glLineWidth(2); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();//draw 2D ray
  DDA(data->var.px - 12, data->var.py- 12, rx  + data->var.pdx * 95, ry  + data->var.pdy * 95, data);
  int ca=FixAng(data->var.pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
  int lineH = (mapS*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
  int lineOff = 160 - (lineH>>1);                                               //line offset
  
//   glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineOff);glVertex2i(r*8+530,lineOff+lineH);glEnd();//draw vertical wall
	for (int i = 0; i < lineH; i++) {
		mlx_pixel_put(data->mlx, data->win, r*8+530, lineOff + i, 0x00FF00);
		mlx_pixel_put(data->mlx, data->win, r*8+531, lineOff + i, 0x00FF00);
		mlx_pixel_put(data->mlx, data->win, r*8+532, lineOff + i, 0x00FF00);
		mlx_pixel_put(data->mlx, data->win, r*8+533, lineOff + i, 0x00FF00);
		mlx_pixel_put(data->mlx, data->win, r*8+534, lineOff + i, 0x00FF00);
		mlx_pixel_put(data->mlx, data->win, r*8+535, lineOff + i, 0x00FF00);
		mlx_pixel_put(data->mlx, data->win, r*8+536, lineOff + i, 0x00FF00);
		mlx_pixel_put(data->mlx, data->win, r*8+537, lineOff + i, 0x00FF00);
		
	}

  ra=FixAng(ra-1);                                                              //go to next ray
 }
}

void	display(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	drawMap2D(data);
	drawPlayer2D(data);
	drawRays3D(data);
}

int		key_event(int keycode, t_data *data)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == W)
	{
		data->var.px += data->var.pdx*5;
		data->var.py += data->var.pdy*5;
	}
	if (keycode == S)
	{
		data->var.px -= data->var.pdx*5;
		data->var.py -= data->var.pdy*5;
	}
	if (keycode == A)
	{
		data->var.pa += 5;
		data->var.pa = FixAng(data->var.pa);
		data->var.pdx = cos(degToRad(data->var.pa));
		data->var.pdy =- sin(degToRad(data->var.pa));
	}
	if (keycode == D)
	{
		data->var.pa -= 5;
		data->var.pa = FixAng(data->var.pa);
		data->var.pdx = cos(degToRad(data->var.pa));
		data->var.pdy =- sin(degToRad(data->var.pa));
	}
	display(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		data = ft_calloc(sizeof(t_data), 1);
		data->attr = ft_calloc(sizeof(t_attr), 1);
		data->map_arg = av[1];
		//ft_parse(data);
		ft_start(data);
		mlx_hook(data->win, 2, 1L << 0, &key_event, data);
		mlx_loop(data->mlx);
	}
	else
		ft_error();
}
