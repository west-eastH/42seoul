#include "../../../include/structures.h"
#include "../../../include/utils.h"
#include "../../../include/trace.h"

t_bool	hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sp;
	t_vec3 oc;	
	double a;
	double half_b;
	double c;
	double discriminant; //판별식
	double sqrtd;
	double root;

	sp = sp_obj->element;
	oc = vminus(ray->orig, sp->center);
	a = vlength2(ray->dir);
	half_b = vdot(oc, ray->dir);
	c = vlength2(oc) - sp->radius2;
	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return(FALSE);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || root > rec->tmax)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
	set_face_normal(ray, rec);
	rec->albedo = sp_obj->albedo;
	return (TRUE);
}

t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	t_vec3 oc;	//방향벡터로 나타낸 구의 중심.
	//a, b, c는 각각 t에 관한 2차 방정식의 계수
	double a;
	double half_b;
	double c;
	double discriminant; //판별식
	double sqrtd;
	double root;
	double h;

	cy = cy_obj->element;
	oc = vminus(ray->orig, cy->center);
	a = vlength2(vcross(cy->normal, ray->dir));
	half_b = vdot(vcross(cy->normal, ray->dir), vcross(cy->normal, oc));
	c = vlength2(vcross(cy->normal, oc)) - ((cy->diameter / 2) * (cy->diameter / 2));
	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return(FALSE);
	sqrtd = sqrt(discriminant);
	//두 실근(t) 중 tmin과 tmax 사이에 있는 근이 있는지 체크, 작은 근부터 체크
	root = (-half_b - sqrtd) / a;
	h = vdot(vminus(ray_at(ray, root), cy->center), cy->normal);
	if (root < rec->tmin || rec->tmax < root || (h > cy->height / 2) || -h > cy->height / 2)
	{
		root = (-half_b + sqrtd) / a;
		h = vdot(vminus(ray_at(ray, root), cy->center), cy->normal);
		if (root < rec->tmin || root > rec->tmax || (h > cy->height / 2) || -h > cy->height / 2)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vunit(vminus(rec->p, vplus(cy->center, vmult(cy->normal, h))));
	// rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 t_bool 값으로 저장
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (TRUE);
}

t_bool	hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
	t_plane	*pl;
	double	t;

	pl = pl_obj->element;
	t = vdot(vminus(pl->point, ray->orig), pl->normal) / vdot(pl->normal, ray->dir);
	if (t < rec->tmin || rec->tmax < t)
			return (FALSE);
	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->normal = pl->normal;
	set_face_normal(ray, rec);
	rec->albedo = pl_obj->albedo;
	return (TRUE);
}

t_bool	hit_cone(t_object *cn_obj, t_ray *ray, t_hit_record *rec)
{
	t_cone	*cn;
	t_vec3 oc;	//방향벡터로 나타낸 구의 중심.
	//a, b, c는 각각 t에 관한 2차 방정식의 계수
	double a;
	double half_b;
	double c;
	double sqrtd;
	double h;
	double r;
	double root;
	double discriminant; //판별식

	cn = cn_obj->element;
	h = cn->height * cn->height;
	r = cn->radius * cn->radius;
	oc = vminus(ray->orig, cn->center);
	a = (h * vlength2(vcross(cn->normal, ray->dir))) - (r * pow(vdot(cn->normal, ray->dir), 2));
	half_b = (h * vdot(vcross(cn->normal, ray->dir), vcross(cn->normal, oc))) - (r * vdot(cn->normal, ray->dir) * vdot(oc, cn->normal));
	c = (h * vlength2(vcross(cn->normal, oc))) - (r * pow(vdot(oc, cn->normal), 2));
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return(FALSE);
	sqrtd = sqrt(discriminant);
	//두 실근(t) 중 tmin과 tmax 사이에 있는 근이 있는지 체크, 작은 근부터 체크
	root = (-half_b - sqrtd) / a;
	h = vdot(vminus(ray_at(ray, root), cn->center), cn->normal);
	if (root < rec->tmin || rec->tmax < root || (h > cn->height) || h < 0)
	{
		root = (-half_b + sqrtd) / a;
		h = vdot(vminus(ray_at(ray, root), cn->center), cn->normal);
		if (root < rec->tmin || root > rec->tmax || (h > cn->height) || h < 0)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vunit(vminus(rec->p, vplus(cn->center, vmult(cn->normal, (vdot(vminus(rec->p, cn->center), cn->normal) + (((cn->radius * cn->radius) * vdot(vminus(rec->p, cn->center), cn->normal)) / (cn->height * cn->height)))))));
	// rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 t_bool 값으로 저장
	set_face_normal(ray, rec);
	rec->albedo = cn_obj->albedo;
	return (TRUE);
}

t_bool	hit_disk(t_object *dk_obj, t_ray *ray, t_hit_record *rec)
{
	t_disk	*dk;
	double	t;

	dk = dk_obj->element;
	t = vdot(vminus(dk->center, ray->orig), dk->normal) / vdot(dk->normal, ray->dir);
	if (t < rec->tmin || rec->tmax < t)
			return (FALSE);
	if (vlength(vminus(ray_at(ray, t), dk->center)) > dk->radius)
		return (FALSE);
	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->normal = dk->normal;
	set_face_normal(ray, rec);
	rec->albedo = dk_obj->albedo;
	return (TRUE);
}

t_bool	hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool			hit_anything;
	t_hit_record	temp_rec;

	temp_rec = *rec;	// temp_rec의 tmin, tmax초기화를 위해
	hit_anything = FALSE;
	while (world)
	{
		if (hit_obj(world, ray, &temp_rec))
		{
			hit_anything = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		world = world->next;
	}
	return (hit_anything);
}

//hit_obj는 오브젝트 타입에 맞는 hit함수로 연결해주는 관문
t_bool	hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_result;

	hit_result = FALSE;
	if (world->type == SP)
		hit_result = hit_sphere(world, ray, rec);
	else if (world->type == PL)
		hit_result = hit_plane(world, ray, rec);
	else if (world->type == CY)
		hit_result = hit_cylinder(world, ray, rec);
	else if (world->type == CN)
		hit_result = hit_cone(world, ray, rec);
	else if (world->type == DK)
		hit_result = hit_disk(world, ray, rec);
	return (hit_result);
}