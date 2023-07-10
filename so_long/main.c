#include <mlx.h>
#include <stdlib.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_data;

typedef struct s_vars{
	void	*mlx;
	void	*win;
}t_vars;

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

#include <stdio.h>
int main()
{
	t_vars	*vars;
	t_data	image;

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 1000, 500, "Hellow World!");
	image.img = mlx_new_image(vars->mlx, 500, 500);
	image.addr = mlx_get_data_addr(image.img,
			&image.bits_per_pixel, &image.line_length,
			&image.endian);
	printf("%d %d %d\n", image.bits_per_pixel,image.line_length , image.endian);
	my_mlx_pixel_put(&image, 50, 50, 0x00FFFFFF);
	mlx_put_image_to_window(vars->mlx, vars->win, image.img, 150, 50);
	mlx_key_hook(vars->win, key_hook, &vars);
	mlx_loop(vars->mlx);
	return (0);
}
