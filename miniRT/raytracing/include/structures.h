#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;
typedef struct s_ray t_ray;
typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;
typedef struct s_object t_object;
typedef struct s_sphere t_sphere;
typedef struct s_light	t_light;
typedef struct s_hit_record t_hit_record;
typedef struct s_scene t_scene;
typedef struct s_plane t_plane;
typedef struct s_cylinder t_cylinder;
typedef struct s_disk t_disk;
typedef struct s_cone t_cone;


typedef int	t_bool;
typedef int	t_object_type;
#define FALSE 0
#define TRUE 1
#define SP 0
#define PL 1
#define CY 2
#define DK 3
#define CN 4
#define LIGHT_POINT 1
#define EPSILON 1e-6 //0.000001
#define LUMEN 3 //이 값을 조절하여 장면의 밝기를 조절할 수 있다.

struct s_vec3
{
    double x;
    double y;
    double z;
};
struct s_ray
{
	t_point3 orig;
	t_vec3 dir;
};

struct s_camera
{
	t_point3	orig;	// 카메라 원점(위치)
	double		viewport_h;	// 뷰포인트 세로길이
	double		viewport_w;	// 뷰포인트 가로길이
	t_vec3		horizontal;	// 수평길이 벡터
	t_vec3		vertical;	// 수직길이 벡터
	double		focal_len;	// focal length
	t_point3	left_bottom;	//위쪽 아래 코너점
};

struct s_canvas
{
	int	width;	//canvas width
	int	height;	//canvas height
	double	aspect_ratio;	//종황비
};

struct s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
};

struct s_hit_record
{
	t_point3	p;				//교점의 좌표
	t_vec3		normal;			//교점에서의 법선
	double		tmin;
	double		tmax;
	double		t;				//광선의 원점과 교점사이의 거리
	t_bool		front_face;
	t_color3	albedo;
};

struct s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
	t_color3		albedo; //반사율
};

struct s_light
{
	t_point3	origin;
	t_color3	light_color;
	double		bright_ratio;
};

struct s_scene
{
	t_canvas	canvas;
	t_camera	camera;
	t_object	*world;
	t_object	*light;
	t_color3	ambient; //주변광
	t_ray		ray;
	t_hit_record	rec;
};

struct s_plane
{
	t_point3	point;
	t_vec3		normal;
};

struct s_cylinder
{
	t_point3	center;
	t_vec3		normal;
	double		height;
	double		diameter;
};

struct s_disk
{
	t_point3	center;
	t_vec3		normal;
	double		radius;
};

struct s_cone
{
	t_point3	center;
	t_vec3		normal;
	double		radius;
	double		height;
};
#endif