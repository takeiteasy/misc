/*********************************************************************************************************************/
/*                                                  /===-_---~~~~~~~~~------____                                     */
/*                                                 |===-~___                _,-'                                     */
/*                  -==\\                         `//~\\   ~~~~`---.___.-~~                                          */
/*              ______-==|                         | |  \\           _-~`                                            */
/*        __--~~~  ,-/-==\\                        | |   `\        ,'                                                */
/*     _-~       /'    |  \\                      / /      \      /                                                  */
/*   .'        /       |   \\                   /' /        \   /'                                                   */
/*  /  ____  /         |    \`\.__/-~~ ~ \ _ _/'  /          \/'                                                     */
/* /-'~    ~~~~~---__  |     ~-/~         ( )   /'        _--~`                                                      */
/*                   \_|      /        _)   ;  ),   __--~~                                                           */
/*                     '~~--_/      _-~/-  / \   '-~ \                                                               */
/*                    {\__--_/}    / \\_>- )<__\      \                                                              */
/*                    /'   (_/  _-~  | |__>--<__|      |                                                             */
/*                   |0  0 _/) )-~     | |__>--<__|     |                                                            */
/*                   / /~ ,_/       / /__>---<__/      |                                                             */
/*                  o o _//        /-~_>---<__-~      /                                                              */
/*                  (^(~          /~_>---<__-      _-~                                                               */
/*                 ,/|           /__>--<__/     _-~                                                                  */
/*              ,//('(          |__>--<__|     /                  .----_                                             */
/*             ( ( '))          |__>--<__|    |                 /' _---_~\                                           */
/*          `-)) )) (           |__>--<__|    |               /'  /     ~\`\                                         */
/*         ,/,'//( (             \__>--<__\    \            /'  //        ||                                         */
/*       ,( ( ((, ))              ~-__>--<_~-_  ~--____---~' _/'/        /'                                          */
/*     `~/  )` ) ,/|                 ~-_~>--<_/-__       __-~ _/                                                     */
/*   ._-~//( )/ )) `                    ~~-'_/_/ /~~~~~~~__--~                                                       */
/*    ;'( ')/ ,)(                              ~~~~~~~~~~                                                            */
/*   ' ') '( (/                                                                                                      */
/*     '   '  `                                                                                                      */
/*********************************************************************************************************************/
#ifndef _LINALGB_H_
#define _LINALGB_H_

#include <stdbool.h>

/* --------------------------------------------------
 * Floating point Maths
 * -------------------------------------------------- */
#ifndef max
float max(float x, float y);
#endif
#ifndef min
float min(float x, float y);
#endif
float clamp(float x, float bottom, float top);
float saturate(float x);
bool between(float x, float bottom, float top);
bool between_or(float x, float bottom, float top);

/* lerp name conflicts with OpenAL definition... */
float lerpp(float p1, float p2, float amount);
float smoothstep(float p1, float p2, float amount);
float smootherstep(float p1, float p2, float amount);
float cosine_interp(float p1, float p2, float amount);
float cubic_interp(float p1, float p2, float p3, float p4, float amount);
float nearest_interp(float p1, float p2, float amount);

float binearest_interp(float tl, float tr, float bl, float br, float x_amount, float y_amount);
float bilinear_interp(float tl, float tr, float bl, float br, float x_amount, float y_amount);
float bicosine_interp(float tl, float tr, float bl, float br, float x_amount, float y_amount);
float bismoothstep_interp(float tl, float tr, float bl, float br, float x_amount, float y_amount);
float bismootherstep_interp(float tl, float tr, float bl, float br, float x_amount, float y_amount);

float degrees(float radians);
float radians(float degrees);

/* --------------------------------------------------
 * Vector Maths
 * -------------------------------------------------- */
/* vec2 */
typedef union {
    struct { float x, y; };
    struct { float s, t; };
    float xy[2];
} vec2;

vec2 vec2_new(float x, float y);
vec2 vec2_zero();
vec2 vec2_one();

vec2 vec2_add(vec2 v1, vec2 v2);
vec2 vec2_sub(vec2 v1, vec2 v2);
vec2 vec2_mul(vec2 v, float fac);
vec2 vec2_mul_vec2(vec2 v1, vec2 v2);
vec2 vec2_div(vec2 v, float fac);
vec2 vec2_div_vec2(vec2 v1, vec2 v2);
vec2 vec2_pow(vec2 v, float exp);
vec2 vec2_neg(vec2 v);
vec2 vec2_abs(vec2 v);
vec2 vec2_floor(vec2 v);
vec2 vec2_fmod(vec2 v, float val);

vec2 vec2_max(vec2 v, float x);
vec2 vec2_min(vec2 v, float x);
vec2 vec2_clamp(vec2 v, float b, float t);

bool vec2_equ(vec2 v1, vec2 v2);

float vec2_dot(vec2 v1, vec2 v2);
float vec2_length_sqrd(vec2 v);
float vec2_length(vec2 v);
float vec2_dist_sqrd(vec2 v1, vec2 v2);
float vec2_dist(vec2 v1, vec2 v2);
float vec2_dist_manhattan(vec2 v1, vec2 v2);
vec2 vec2_normalize(vec2 v);

vec2 vec2_reflect(vec2 v1, vec2 v2);

vec2 vec2_from_string(char* s);
void vec2_print(vec2 v);

void vec2_to_array(vec2 v, float* out);

int vec2_hash(vec2 v);
int vec2_mix_hash(vec2 v);

vec2 vec2_saturate(vec2 v);
vec2 vec2_lerp(vec2 v1, vec2 v2, float amount);
vec2 vec2_smoothstep(vec2 v1, vec2 v2, float amount);
vec2 vec2_smootherstep(vec2 v1, vec2 v2, float amount);

/* vec3 */
typedef union {
    struct { float x, y, z; };
    float xyz[3];
    struct { float r, g, b; };
    float rgb[3];
    struct { float s, t, p; };
} vec3;

vec3 vec3_new(float x, float y, float z);
vec3 vec3_zero();
vec3 vec3_one();
vec3 vec3_up();

vec3 vec3_red();
vec3 vec3_green();
vec3 vec3_blue();
vec3 vec3_white();
vec3 vec3_black();
vec3 vec3_grey();
vec3 vec3_light_grey();
vec3 vec3_dark_grey();

vec3 vec3_add(vec3 v1, vec3 v2);
vec3 vec3_sub(vec3 v1, vec3 v2);
vec3 vec3_mul(vec3 v, float fac);
vec3 vec3_mul_vec3(vec3 v1, vec3 v2);
vec3 vec3_div(vec3 v, float fac);
vec3 vec3_div_vec3(vec3 v1, vec3 v2);
vec3 vec3_pow(vec3 v, float fac);
vec3 vec3_neg(vec3 v);
vec3 vec3_abs(vec3 v);
vec3 vec3_floor(vec3 v);
vec3 vec3_fmod(vec3 v, float val);

bool vec3_equ(vec3 v1, vec3 v2);
bool vec3_neq(vec3 v1, vec3 v2);

float vec3_dot(vec3 v1, vec3 v2);
float vec3_length_sqrd(vec3 v);
float vec3_length(vec3 v);
float vec3_dist_sqrd(vec3 v1, vec3 v2);
float vec3_dist(vec3 v1, vec3 v2);
float vec3_dist_manhattan(vec3 v1, vec3 v2);
vec3 vec3_cross(vec3 v1, vec3 v2);
vec3 vec3_normalize(vec3 v);

vec3 vec3_reflect(vec3 v1, vec3 v2);
vec3 vec3_project(vec3 v1, vec3 v2);

vec3 vec3_from_string(char* s);
void vec3_print(vec3 v);

void vec3_to_array(vec3 v, float* out);

int vec3_hash(vec3 v);

vec3 vec3_saturate(vec3 v);
vec3 vec3_lerp(vec3 v1, vec3 v2, float amount);
vec3 vec3_smoothstep(vec3 v1, vec3 v2, float amount);
vec3 vec3_smootherstep(vec3 v1, vec3 v2, float amount);

/* vec4 */
typedef union {
    struct { float x, y, z, w; };
    float xyzw[4];
    struct { float r, g, b, a; };
    float rgba[4];
    struct { float s, t, p, q; };
} vec4;

vec4 vec4_new(float x, float y, float z, float w);
vec4 vec4_zero();
vec4 vec4_one();

vec4 vec4_red();
vec4 vec4_green();
vec4 vec4_blue();
vec4 vec4_white();
vec4 vec4_black();
vec4 vec4_grey();
vec4 vec4_light_grey();
vec4 vec4_dark_grey();

vec4 vec4_add(vec4 v1, vec4 v2);
vec4 vec4_sub(vec4 v1, vec4 v2);
vec4 vec4_mul(vec4 v, float fac);
vec4 vec4_mul_vec4(vec4 v1, vec4 v2);
vec4 vec4_div(vec4 v, float fac);
vec4 vec4_pow(vec4 v, float fac);
vec4 vec4_neg(vec4 v);
vec4 vec4_abs(vec4 v);
vec4 vec4_floor(vec4 v);
vec4 vec4_fmod(vec4 v, float val);
vec4 vec4_sqrt(vec4 v);

vec4 vec4_max(vec4 v1, vec4 v2);
vec4 vec4_min(vec4 v1, vec4 v2);
bool vec4_equ(vec4 v1, vec4 v2);

float vec4_dot(vec4 v1, vec4 v2);
float vec4_length_sqrd(vec4 v);
float vec4_length(vec4 v);
float vec4_dist_sqrd(vec4 v1, vec4 v2);
float vec4_dist(vec4 v1, vec4 v2);
float vec4_dist_manhattan(vec4 v1, vec4 v2);
vec4 vec4_normalize(vec4 v);

vec4 vec4_reflect(vec4 v1, vec4 v2);

vec4 vec4_from_string(char* s);
void vec4_print(vec4 v);

void vec4_to_array(vec4 v, float* out);

vec4 vec3_to_homogeneous(vec3 v);
vec3 vec4_from_homogeneous(vec4 v);

int vec4_hash(vec4 v);

vec4 vec4_saturate(vec4 v);
vec4 vec4_lerp(vec4 v1, vec4 v2, float amount);
vec4 vec4_smoothstep(vec4 v1, vec4 v2, float amount);
vec4 vec4_smootherstep(vec4 v1, vec4 v2, float amount);
vec4 vec4_nearest_interp(vec4 v1, vec4 v2, float amount);

vec4 vec4_binearest_interp(vec4 top_left, vec4 top_right, vec4 bottom_left, vec4 bottom_right, float x_amount, float y_amount);
vec4 vec4_bilinear_interp(vec4 top_left, vec4 top_right, vec4 bottom_left, vec4 bottom_right, float x_amount, float y_amount);

/* quaterion */
typedef vec4 quat;

quat quat_id();
quat quat_new(float x, float y, float z, float w);
quat quat_from_euler(vec3 r);
quat quat_angle_axis(float angle, vec3 axis);
quat quat_rotation_x(float angle);
quat quat_rotation_y(float angle);
quat quat_rotation_z(float angle);

float quat_at(quat q, int i);
float quat_real(quat q);
vec3 quat_imaginaries(quat q);

void quat_to_angle_axis(quat q, vec3* axis, float* angle);
vec3 quat_to_euler(quat q);

quat quat_neg(quat q);
float quat_dot(quat q1, quat q2);
quat quat_scale(quat q, float f);
quat quat_mul_quat(quat q1, quat q2);
vec3 quat_mul_vec3(quat q, vec3 v);

quat quat_inverse(quat q);
quat quat_unit_inverse(quat q);
float quat_length(quat q);
quat quat_normalize(quat q);

quat quat_exp(vec3 w);
vec3 quat_log(quat q);

quat quat_slerp(quat q1, quat q2, float amount);

quat quat_constrain(quat q, vec3 axis);
quat quat_constrain_y(quat q);

float quat_distance(quat q0, quat q1);
quat quat_interpolate(quat* qs, float* ws, int count);

typedef struct {
    quat real;
    quat dual;
} quat_dual;

quat_dual quat_dual_id();
quat_dual quat_dual_new(quat real, quat dual);
quat_dual quat_dual_transform(quat q, vec3 t);
quat_dual quat_dual_mul(quat_dual q0, quat_dual q1);
vec3 quat_dual_mul_vec3(quat_dual q, vec3 v);
vec3 quat_dual_mul_vec3_rot(quat_dual q, vec3 v);

/* --------------------------------------------------
 * Matrix Maths
 * -------------------------------------------------- */
/* mat2 */
typedef union {
    struct {
#ifdef LINALGB_ROW_MAJOR
        float xx; float xy;
        float yx; float yy;
#else
        float xx; float yx;
        float xy; float yy;
#endif
    };
    float m[4];
    float m2[2][2];
} mat2;

mat2 mat2_id();
mat2 mat2_zero();
mat2 mat2_new(float xx, float xy, float yx, float yy);
mat2 mat2_mul_mat2(mat2 m1, mat2 mat2);
vec2 mat2_mul_vec2(mat2 m, vec2 v);

mat2 mat2_transpose(mat2 m);
float mat2_det(mat2 m);
mat2 mat2_inverse(mat2 m);

void mat2_to_array(mat2 m, float* out);
void mat2_print(mat2 m);
mat2 mat2_rotation(float a);

/* mat3 */
typedef union {
    struct {
#ifdef LINALGB_ROW_MAJOR
        float xx; float xy; float xz;
        float yx; float yy; float yz;
        float zx; float zy; float zz;
#else
        float xx; float yx; float zx;
        float xy; float yy; float zy;
        float xz; float yz; float zz;
#endif
    };
    float m[9];
    float m2[3][3];
} mat3;

mat3 mat3_id();
mat3 mat3_zero();
mat3 mat3_new(float xx, float xy, float xz,
        float yx, float yy, float yz,
        float zx, float zy, float zz);
mat3 mat3_mul_mat3(mat3 m1, mat3 mat2);
vec3 mat3_mul_vec3(mat3 m, vec3 v);

mat3 mat3_transpose(mat3 m);
float mat3_det(mat3 m);
mat3 mat3_inverse(mat3 m);

void mat3_to_array(mat3 m, float* out);
void mat3_print(mat3 m);

mat3 mat3_scale(vec3 s);
mat3 mat3_rotation_x(float a);
mat3 mat3_rotation_y(float a);
mat3 mat3_rotation_z(float a);
mat3 mat3_rotation_angle_axis(float angle, vec3 axis);

/* mat4 */
typedef union {
    struct {
#ifdef LINALGB_ROW_MAJOR
        float xx; float xy; float xz; float xw;
        float yx; float yy; float yz; float yw;
        float zx; float zy; float zz; float zw;
        float wx; float wy; float wz; float ww;
#else
        float xx; float yx; float zx; float wx;
        float xy; float yy; float zy; float wy;
        float xz; float yz; float zz; float wz;
        float xw; float yw; float zw; float ww;
#endif
    };
    float m[16];
    float m2[4][4];
} mat4;

mat4 mat4_id();
mat4 mat4_zero();
mat4 mat4_new(float xx, float xy, float xz, float xw,
        float yx, float yy, float yz, float yw,
        float zx, float zy, float zz, float zw,
        float wx, float wy, float wz, float ww);
float mat4_at(mat4 m, int i, int j);
mat4 mat4_set(mat4 m, int x, int y, float v);
mat4 mat4_transpose(mat4 m);

mat4 mat4_mul_mat4(mat4 m1, mat4 mat2);

vec4 mat4_mul_vec4(mat4 m, vec4 v);
vec3 mat4_mul_vec3(mat4 m, vec3 v);

float mat4_det(mat4 m);
mat4 mat4_inverse(mat4 m);

mat4 mat3_to_mat4(mat3 m);
mat3 mat4_to_mat3(mat4 m);
quat mat4_to_quat(mat4 m);
quat_dual mat4_to_quat_dual(mat4 m);

void mat4_to_array(mat4 m, float* out);
void mat4_to_array_trans(mat4 m, float* out);

void mat4_print(mat4 m);

mat4 mat4_translation(vec3 v);
mat4 mat4_scale(vec3 v);

mat4 mat4_rotation_x(float a);
mat4 mat4_rotation_y(float a);
mat4 mat4_rotation_z(float a);
mat4 mat4_rotation_axis_angle(vec3 axis, float angle);

mat4 mat4_rotation_euler(float x, float y, float z);
mat4 mat4_rotation_quat(quat q);
mat4 mat4_rotation_quat_dual(quat_dual q);

mat4 mat4_view_look_at(vec3 position, vec3 target, vec3 up);
mat4 mat4_perspective(float fov, float near_clip, float far_clip, float ratio);
mat4 mat4_orthographic(float left, float right, float bottom, float top, float near, float far);

mat4 mat4_world(vec3 position, vec3 scale, quat rotation);

mat4 mat4_lerp(mat4 m1, mat4 mat2, float amount);
mat4 mat4_smoothstep(mat4 m1, mat4 mat2, float amount);

/* --------------------------------------------------
 * Geometry
 * -------------------------------------------------- */
/* Plane */
typedef struct {
    vec3 direction;
    vec3 position;
} plane;

plane plane_new(vec3 position, vec3 direction);
plane plane_transform(plane p, mat4 world, mat3 world_normal);
plane plane_transform_space(plane p, mat3 space, mat3 space_normal);
float plane_distance(plane p, vec3 point);

bool point_inside_plane(vec3 point, plane p);
bool point_outside_plane(vec3 point, plane p);
bool point_intersects_plane(vec3 point, plane p);

bool point_swept_inside_plane(vec3 point, vec3 v, plane p);
bool point_swept_outside_plane(vec3 point, vec3 v, plane p);
bool point_swept_intersects_plane(vec3 point, vec3 v, plane p);

vec3 plane_closest(plane p, vec3 v);
vec3 plane_project(plane p, vec3 v);

/* Box */
typedef struct {
    plane top;
    plane bottom;
    plane left;
    plane right;
    plane front;
    plane back;
} box;

box box_new(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max);
box box_sphere(vec3 center, float radius);
box box_merge(box b1, box b2);
box box_transform(box b1, mat4 world, mat3 world_normal);
box box_invert(box b);
box box_invert_depth(box b);
box box_invert_width(box b);
box box_invert_height(box b);

bool point_inside_box(vec3 point, box b);
bool point_outside_box(vec3 point, box b);
bool point_intersects_box(vec3 point, box b);

/* Frustum */
typedef struct {
    vec3 ntr, ntl, nbr, nbl;
    vec3 ftr, ftl, fbr, fbl;
} frustum;

frustum frustum_new(vec3 ntr, vec3 ntl, vec3 nbr, vec3 nbl, vec3 ftr, vec3 ftl, vec3 fbr, vec3 fbl);
frustum frustum_new_clipbox();
frustum frustum_new_camera(mat4 view, mat4 proj);
frustum frustum_slice(frustum f, float start, float end);
frustum frustum_transform(frustum f, mat4 m);
frustum frustum_translate(frustum f, vec3 v);

vec3 frustum_center(frustum f);
vec3 frustum_maximums(frustum f);
vec3 frustum_minimums(frustum f);

box frustum_box(frustum f);

bool frustum_outside_box(frustum f, box b);

/* Sphere */
typedef struct {
    vec3 center;
    float radius;
} sphere;

sphere sphere_unit();
sphere sphere_point();
sphere sphere_new(vec3 center, float radius);
sphere sphere_merge(sphere s1, sphere s2);
sphere sphere_merge_many(sphere* s, int count);
sphere sphere_transform(sphere s, mat4 world);
sphere sphere_translate(sphere s, vec3 x);
sphere sphere_scale(sphere s, float x);
sphere sphere_transform_space(sphere s, mat3 space);

sphere sphere_of_box(box bb);
sphere sphere_of_frustum(frustum f);

bool sphere_inside_box(sphere s, box b);
bool sphere_outside_box(sphere s, box b);
bool sphere_intersects_box(sphere s, box b);

bool sphere_inside_frustum(sphere s, frustum f);
bool sphere_outside_frustum(sphere s, frustum f);
bool sphere_intersects_frustum(sphere s, frustum f);

bool sphere_outside_sphere(sphere s1, sphere s2);
bool sphere_inside_sphere(sphere s1, sphere s2);
bool sphere_intersects_sphere(sphere s1, sphere s2);

bool point_inside_sphere(sphere s, vec3 point);
bool point_outside_sphere(sphere s, vec3 point);
bool point_intersects_sphere(sphere s, vec3 point);

bool line_inside_sphere(sphere s, vec3 start, vec3 end);
bool line_outside_sphere(sphere s, vec3 start, vec3 end);
bool line_intersects_sphere(sphere s, vec3 start, vec3 end);

bool sphere_inside_plane(sphere s, plane p);
bool sphere_outside_plane(sphere s, plane p);
bool sphere_intersects_plane(sphere s, plane p);

bool point_swept_inside_sphere(sphere s, vec3 v, vec3 point);
bool point_swept_outside_sphere(sphere s, vec3 v, vec3 point);
bool point_swept_intersects_sphere(sphere s, vec3 v, vec3 point);

bool sphere_swept_inside_plane(sphere s, vec3 v, plane p);
bool sphere_swept_outside_plane(sphere s, vec3 v, plane p);
bool sphere_swept_intersects_plane(sphere s, vec3 v, plane p);

bool sphere_swept_outside_sphere(sphere s1, vec3 v, sphere s2);
bool sphere_swept_inside_sphere(sphere s1, vec3 v, sphere s2);
bool sphere_swept_intersects_sphere(sphere s1, vec3 v, sphere s2);

bool point_inside_triangle(vec3 p, vec3 v0, vec3 v1, vec3 v2);
bool sphere_intersects_face(sphere s, vec3 v0, vec3 v1, vec3 v2, vec3 norm);

/* Ellipsoid */
typedef struct {
    vec3 center;
    vec3 radiuses;
} ellipsoid;

ellipsoid ellipsoid_new(vec3 center, vec3 radiuses);
ellipsoid ellipsoid_transform(ellipsoid e, mat4 m);
ellipsoid ellipsoid_of_sphere(sphere s);

mat3 ellipsoid_space(ellipsoid e);
mat3 ellipsoid_inv_space(ellipsoid e);

/* Capsule */
typedef struct {
    vec3 start;
    vec3 end;
    float radius;
} capsule;

capsule capsule_new(vec3 start, vec3 end, float radius);
capsule capsule_transform(capsule c, mat4 m);

bool capsule_inside_plane(capsule c, plane p);
bool capsule_outside_plane(capsule c, plane p);
bool capsule_intersects_plane(capsule c, plane p);

#endif // ! _LINALGB_H_
