#include "../../../include/structures.h"
#include "../../../include/utils.h"
#include "../../../include/trace.h"

t_bool	hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sp;
	t_vec3 oc;	//방향벡터로 나타낸 구의 중심.
	//a, b, c는 각각 t에 관한 2차 방정식의 계수
	double a;
	double half_b;
	double c;
	double discriminant; //판별식
	double sqrtd;
	double root;

	sp = sp_obj->element;
	oc = vminus(ray->orig, sp->center);
	/* a = vdot(ray->dir, ray->dir);
	b = 2.0 * vdot(oc, ray->dir);
	c = vdot(oc, oc) - sp->radius2;
	//discriminant는 판별식
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0) // 판별식이 0보다 작을 때 : 실근이 없다
		return (-1.0);
	else	// 근의 공식 : (-b +or-(b*b - 4ab)) / 2a
		return ((-b -sqrt(discriminant)) / (2.0 * a));	//두근 중 작은 근 */

	a = vlength2(ray->dir);
	half_b = vdot(oc, ray->dir);
	c = vlength2(oc) - sp->radius2;
	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return(FALSE);
	sqrtd = sqrt(discriminant);
	//두 실근(t) 중 tmin과 tmax 사이에 있는 근이 있는지 체크, 작은 근부터 체크
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || root > rec->tmax)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);	//정규화된 법선 벡터
	// rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 t_bool 값으로 저장
	set_face_normal(ray, rec);
	rec->albedo = sp_obj->albedo;
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
	return (hit_result);
}