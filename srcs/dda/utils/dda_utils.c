#include "c3d.h"

double pitagora_theorem(t_point first_point, t_point second_point)
{
	double result;
	double dx;
	double dy;

	dx = first_point.x - second_point.x;
	dy = first_point.y - second_point.y;
	result = sqrt(pow(dx, 2) + pow(dy, 2));
	return (result);
}

//this is useful to fine the intersection between
//1.: line passing through player and perpendicular to his direction
//2:: line passing for the impact_point of a ray against a wall, and parallel to player direction 
//(that is the line where the projection of that point is located)
//m1: is tan(p1_angle)  
//the linear equation of a line is: y = mx + c;
t_point find_two_lines_intersection(t_point p1, double p1_angle, t_point p2, double p2_angle) 
{
    t_point intersection;
    double c1;
    double c2;
    double m1;
    double m2;
	double c;

    point_init(&intersection);
	c = cos(p1_angle);
	if (c <= PI_FIX && c >= -PI_FIX)
		p1_angle += PI_FIX;
	c = cos(p2_angle);
	if (c  <= PI_FIX && c >= -PI_FIX)
		p2_angle += PI_FIX;
    m1 = tan(p1_angle);
    m2 = tan(p2_angle);
    c1 = p1.y - (m1 * p1.x);
    c2 = p2.y - (m2 * p2.x);
    intersection.x = (c2 - c1) / (m1 - m2);
    intersection.y = (m1 * intersection.x) + c1;
    return intersection;
}

int	is_it_a_wall(t_point point_to_verify, char **map_grid)
{
	if (map_grid[(int)point_to_verify.y / TILE_SIZE][(int)point_to_verify.x / TILE_SIZE] == '1')
		return (True);
	return (False);
}

int	is_it_inside_map_perimeter(t_point point, t_dimension map_dimension)
{
	if (point.x >= TILE_SIZE && \
	point.x < (map_dimension.w * TILE_SIZE - TILE_SIZE) && \
	point.y >= TILE_SIZE && \
	point.y < (map_dimension.h * TILE_SIZE) - TILE_SIZE)
		return (True);
	return (False);
}
