# include "../../include/structures.h"
# include "../../include/scene.h"

t_object	*object(t_object_type type, void *element, t_color3 albedo)
{
	t_object	*new;

	new = (t_object *)malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->type = type;
	new->element = element;
	new->next = NULL;
	new->albedo = albedo;
	return (new);
}

t_sphere	*sphere(t_point3 center, double radius)
{
	t_sphere *sp;

	sp = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	return (sp);
}

t_plane	*plane(t_point3 point, t_vec3 normal)
{
	t_plane *pl;

	pl = (t_plane *)malloc(sizeof(t_plane));
	if (!pl)
		return (NULL);
	pl->point = point;
	pl->normal = vunit(normal);
	return (pl);
}

t_cylinder	*cylinder(t_point3 center, t_vec3 normal, double height, double diameter)
{
	t_cylinder *cy;

	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	cy->center = center;
	cy->normal = vunit(normal);
	// cy->normal = normal;
	cy->height = height;
	cy->diameter = diameter;
	return (cy);
}

t_cone	*cone(t_point3 center, t_vec3 normal, double height, double radius)
{
	t_cone *cn;

	cn = (t_cone *)malloc(sizeof(t_cone));
	if (!cn)
		return (NULL);
	cn->center = center;
	cn->normal = vunit(normal);
	cn->height = height;
	cn->radius = radius;
	return (cn);
}

t_disk	*disk(t_point3 center, t_vec3 normal, double radius)
{
	t_disk *disk;

	disk = (t_disk *)malloc(sizeof(t_disk));
	if (!disk)
		return (NULL);
	disk->center = center;
	disk->normal = vunit(normal);
	disk->radius = radius;
	return (disk);
}

t_light		*light_point(t_point3 light_origin, t_color3 light_color, double bright_ratio)
{
	t_light *light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->origin = light_origin;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}
