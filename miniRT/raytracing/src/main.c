#include <stdio.h>
#include "../include/structures.h"
#include "../include/utils.h"
#include "../include/print.h"
#include "../include/scene.h"
#include "../include/trace.h"
# include "mlx.h"

t_scene	*scene_init()
{
	t_scene		*scene;
	t_object	*world;
	t_object	*lights;
	double		ka;
	t_point3	cy_center;
	t_vec3		cy_normal;
	double		cy_height;
	double		cy_diameter;
	t_point3	cn_center;
	t_vec3		cn_normal;
	double		cn_height;
	double		cn_radius;

	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
		return NULL;
	scene->canvas = canvas(1920, 1080);
	scene->camera = camera(&scene->canvas, point3(0, 0, 0));
	world = NULL;

	cy_center = point3(2, 0, -5);
	cy_normal = vunit(vec3(0, 1, 1));
	cy_height = 2;
	cy_diameter = 2;
	// oadd(&world, object(CY, cylinder(cy_center, cy_normal, cy_height, cy_diameter), color3(0, 0.5, 0)));
	// oadd(&world, object(DK, disk(vplus(cy_center, vmult(cy_normal, cy_height / 2)), vmult(cy_normal, -1), cy_diameter / 2), color3(1, 0.5, 0)));
	// oadd(&world, object(DK, disk(vplus(cy_center, vmult(cy_normal, -(cy_height / 2))), cy_normal, cy_diameter / 2), color3(1, 0.5, 0)));


	cn_center = point3(0, 1, -5);
	cn_normal = vunit(vec3(0, -1, 0));
	cn_height = 2;
	cn_radius = 1;
	oadd(&world, object(CN, cone(cn_center, cn_normal, cn_height, cn_radius), color3(0, 0.5, 0)));
	oadd(&world, object(DK, disk(vplus(cn_center, vmult(cn_normal, cn_height)), cn_normal, cn_radius), color3(0, 0.3, 0)));
	//oadd(&world, object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0))); //world에 구1 추가
	//oadd(&world, object(SP, sphere(point3(0, -1000, 0), 995), color3(1, 1, 1))); 
	//oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0))); //world에 구3 추가
	//oadd(&world, object(PL, plane(point3(0, 10, 0), vec3(0,-1,0)), color3(0, 0.5, 0)));
	//oadd(&world, object(PL, plane(point3(0, -10, 0), vec3(0,1,0)), color3(1, 0, 0)));
	scene->world = world;
	
	lights = object(LIGHT_POINT, light_point(point3(0, 0, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0)); //더미 albedo
	scene->light = lights;
	ka = 0.1;
	scene->ambient = vmult(color3(1, 1, 1), ka);
	return (scene);
}

int main(int argc, char *argv[])
{
	int i;
	int j;
	double u;
	double v;
	t_param	par;
	t_color3 pixel_color;
	t_scene	*scene;
	

	if (argc < 1 || argc > 3)
		return (0);
	init(&par, argv[1]);
	if (par.fd < 0)
		return (0);
	//Scene setting;
	scene = scene_init();
	//렌더링
	//p3는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀 수, 마지막은 사용할 색상값
	printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);
	j = scene->canvas.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < scene->canvas.width)
		{
			u = (double)i / (scene->canvas.width - 1);
			v = (double)j / (scene->canvas.height - 1);
			//ray from camera origin to pixel
			scene->ray = ray_primary(&scene->camera, u, v);
			pixel_color = ray_color(scene);
			write_color(pixel_color);
			++i;
		}
		--j;
	}
	return 0;
}