/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:48:51 by ada-cruz          #+#    #+#             */
/*   Updated: 2023/12/26 17:11:26 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
void	free_ptrptr(char ***ptrptr)
{
	int	i;

	i = 0;
	while (*ptrptr && (*ptrptr)[i])
	{
		free((*ptrptr)[i]);
		i++;
	}
	free(*ptrptr);
	*ptrptr = NULL;
}

void	free_rt(t_rt *rt)
{
	free_ptrptr(&rt->linesread);
	free_ptrptr(&rt->lineread);
	free_ptrptr(&rt->color);
	free_ptrptr(&rt->coordinates);
	// free(rt->lights);
	// free_sphere_plane_matrices(rt);
	// free(rt->spheres);
	// free(rt->planes);
	// free_cylinder_matrices(rt);
	// free(rt->cylinders);
	if (rt->render.mlx)
	{
		mlx_close_window(rt->render.mlx);
		if (rt->render.image)
			mlx_delete_image(rt->render.mlx, rt->render.image);
		mlx_terminate(rt->render.mlx);
	}
	free(rt);
	exit(0);
}

void	print_error(char *error, t_rt *rt)
{
	printf("Error\n%s\n", error);
	if (rt)
		free_rt(rt);
	exit(1);
}

static t_rt	*init_rt(void)
{
	t_rt	*rt;

	rt = (t_rt *)ft_calloc(1, sizeof(t_rt));
	return (rt);
}

void draw(t_rt *rt)
{
	int x;
	int y;
	x = 100;
	while (x < 300)
	{
		y = 100;
		while (y < 300)
		{
			if ((x - 200) * (x - 200) + (y - 200) * (y - 200) <= 10000)
				mlx_put_pixel(rt->render.image,x, y, 255 << 24 | 0 << 16 | 0 << 8 | 255);
			y++;
		}
		x++;
	}
}

void render(t_rt *rt)
{
	rt->render.mlx = mlx_init(WIDTH, HEIGHT, "O inicio de tudo", true);
	if (!rt->render.mlx)
		print_error("Problem initializing mlx pointer", rt);
	rt->render.image = mlx_new_image(rt->render.mlx, WIDTH, HEIGHT);
	if (!rt->render.image)
	{
		mlx_close_window(rt->render.mlx);
		print_error("Problem initializing image pointer", rt);
	}
	draw(rt);
}

void check_arguments(int argc, char **argv)
{
	int len;

	len = 0;
	if(argc != 2)
	{	
		printf("Error\n");
		printf("Number of arguments is wrong!");
		exit (1);
	}
	len = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 3], ".rt", 4) != 0)
	{
		printf("Error\n");
		printf("invalid file type!");
		exit (1);
	}
}

static void	close_window(void *parameter)
{
	t_rt	*rt;

	rt = (t_rt *)parameter;
	if (mlx_is_key_down(rt->render.mlx, MLX_KEY_ESCAPE))
		free_rt(rt);
}

void	read_file(t_rt *rt, char *file)
{
	int		fd;
	int		rd;
	char	c;
	char	*buffer;
	
	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_error("Can't open the file!", rt);
	rd = read(fd, &c, 1);
	if (rd == -1)
		print_error("Can't read the file!", rt);
	while(read(fd, &c, 1))
		rd++;
	close(fd);
	buffer = (char *)ft_calloc(rd + 1, sizeof(char));
	fd = open(file, O_RDONLY);
	read(fd, buffer, rd);
	close(fd);
	rt->linesread = ft_split(buffer, '\n');
	free(buffer);
}

int	validate_double(char *number)
{
	int	i;

	i = 0;
	if (!number || !number[i])
		return (0);
	if (number[i] == '+' || number[i] == '-')
		i++;
	if (!number[i])
		return (0);
	while (ft_isdigit(number[i]))
		i++;
	if (!number[i])
		return (1);
	if (number[i] == '.')
		i++;
	if (!number[i])
		return (0);
	while (ft_isdigit(number[i]))
		i++;
	if (!number[i])
		return (1);
	return (0);
}

int	validate_int(char *number)
{
	int	i;

	i = 0;
	if (!number || !number[i] || ft_strlen(number) > 3)
		return (0);
	while (ft_isdigit(number[i]))
		i++;
	if (!number[i])
		return (0);
	return (1);
}

int validate_color(char **color)
{
	int i;
	int n;
	
	i = 0;
	n = 0;
	while (color && color[i] && validate_int(color[i]) == 0)
	{
		if (ft_atoi(color[i]) < 0 || ft_atoi(color[i]) > 255)
			break ;
		i++;
	}
	if (i != 3)
		return 0;
	return 1;
}

void	set_color(t_color *dest, char **src)
{
	(*dest).red = ft_atoi(src[0]);
	(*dest).green = ft_atoi(src[1]);
	(*dest).blue = ft_atoi(src[2]);
}

int validate_coordinates(char **coordinates)
{
	int i;
	i = 0;
	while (coordinates && coordinates[i] && validate_double(coordinates[i]))
		i++;
	if (i != 3)
		return (0);
	return (1);
}

void	set_coordinates(t_coordinates *dest, char **src, double w)
{
	(*dest).x = ft_atod(src[0]);
	(*dest).y = ft_atod(src[1]);
	(*dest).z = ft_atod(src[2]);
	(*dest).w = w;
}

int	are_equals(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	return (0);
}

double	calculate_vector_magnitude(t_coordinates v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2) + pow(v.w, 2)));
}

int	validate_normalized_vector(t_coordinates coordinates)
{
	return (are_equals(calculate_vector_magnitude(coordinates), 1));
}

int	validate_angle(char *angle)
{
	return (angle && validate_double(angle) && ft_atod(angle) >= 0 \
		&& ft_atod(angle) <= 180);
}

void	validate_amb_light(t_rt *rt)
{
	if (rt->amb_light.amb_light)
		print_error("error in amb_light validation", rt);
	if (!rt->lineread[1] || !rt->lineread[2] || rt->lineread[3])
		print_error("error in amb_light validation", rt);
	if (!validate_double(rt->lineread[1]))
		print_error("error in amb_light validation", rt);
	rt->amb_light.ratio = ft_atod(rt->lineread[1]);
	if (rt->amb_light.ratio > 1 || rt->amb_light.ratio < 0)
		print_error("error in amb_light validation", rt);
	rt->color = ft_split(rt->lineread[2], ',');
	if (validate_color(rt->color) == 0)
		print_error("error in amb_light validation", rt);
	set_color(&rt->amb_light.color, rt->color);
	free_ptrptr(&rt->color);
	rt->amb_light.amb_light = 1;
}

void validate_camera(t_rt *rt)
{
	if (rt->camera.camera)
		print_error("error in camera validation", rt);
	if (!rt->lineread[1] || !rt->lineread[2] || !rt->lineread[3] || rt->lineread[4])
		print_error("error in camera validation", rt);
	rt->coordinates = ft_split(rt->lineread[1], ',');
	if (validate_coordinates(rt->coordinates) == 0)
		print_error("error in camera validation", rt);
	set_coordinates(&rt->camera.point, rt->coordinates, POINT);
	free_ptrptr(&rt->coordinates);
	rt->coordinates = ft_split(rt->lineread[2], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("error in camera validation", rt);
	set_coordinates(&rt->camera.vector, rt->coordinates, VECTOR);
	if (!validate_normalized_vector(rt->camera.vector))
		print_error("the vector is not normalized", rt);
	free_ptrptr(&rt->coordinates);
	if (!validate_angle(rt->lineread[3]))
		print_error("error to validade the angle", rt);
	rt->camera.fov = ft_atod(rt->lineread[3]);
	rt->camera.camera = 1;	
}

void validate_light(t_rt *rt)
{
	if (rt->light.light)
		print_error("error in light validation", rt);
	if (!rt->lineread[1] || !rt->lineread[2] || !rt->lineread[3] || rt->lineread[4])
		print_error("error in light validation", rt);
	rt->coordinates = ft_split(rt->lineread[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("error in light's coordinates validation", rt);
	set_coordinates(&rt->light.point, rt->coordinates, POINT);
	free_ptrptr(&rt->coordinates);
	if (!validate_double(rt->lineread[2]))
		print_error("error in brightness ratio", rt);
	rt->light.brightness = ft_atod(rt->lineread[2]);
	if (rt->light.brightness > 1 || rt->light.brightness < 0)
		print_error("error in brightness range", rt);
	rt->color = ft_split(rt->lineread[3], ',');
	if (!validate_color(rt->color))
		print_error("error in light's color", rt);
	set_color(&rt->light.color, rt->color);
	free_ptrptr(&rt->color);
	rt->light.light = 1;
}

void validate_sphere(t_rt *rt, int sp)
{
	if (!rt->lineread[1] || !rt->lineread[2] || !rt->lineread[3] || rt->lineread[4])
		print_error("Error in sphere validation", rt);
	rt->coordinates = ft_split(rt->lineread[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("Error in sphere coordinates", rt);
	set_coordinates(&rt->spheres[sp].point, rt->coordinates, POINT);
	free_ptrptr(&rt->coordinates);
	if (!validate_double(rt->lineread[2]))
		print_error("Error in sphere diameter", rt);
	rt->spheres[sp].diameter = ft_atod(rt->lineread[2]);
	if (rt->spheres[sp].diameter <= EPSILON)
		print_error("The diameter is too little", rt);
	rt->color = ft_split(rt->lineread[3], ',');
	if (!validate_color(rt->color))
		print_error("Error in sphere color", rt);
	set_color(&rt->spheres[sp].color, rt->color);
	free_ptrptr(&rt->color);			
}

void validate_plane(t_rt *rt, int pl)
{
	if (!rt->lineread[1] || !rt->lineread[2] || !rt->lineread[3] || rt->lineread[4])
		print_error("Error in plane validation", rt);
	rt->coordinates = ft_split(rt->lineread[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("error in plane coordinates", rt);
	set_coordinates(&rt->planes[pl].point, rt->coordinates, POINT);
	free_ptrptr(&rt->coordinates);
	rt->coordinates = ft_split(rt->lineread[2], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("error in plane coordinates", rt);
	set_coordinates(&rt->planes[pl].vector, rt->coordinates, VECTOR);
	if (!validate_normalized_vector(rt->planes[pl].vector))
		print_error("the plane vector is not normalized", rt);
	free_ptrptr(&rt->coordinates);
	rt->color = ft_split(rt->lineread[3], ',');
	if (!validate_color(rt->color))
		print_error("error in plane color validation", rt);
	set_color(&rt->planes[pl].color, rt->color);
	free_ptrptr(&rt->color);
}

void validate_cylinder(t_rt *rt, int cy)
{
	if (!rt->lineread[1] || !rt->lineread[2] || !rt->lineread[3] \
		|| !rt->lineread[4] || !rt->lineread[5] ||  rt->lineread[6])
		print_error("error in cylinder validation", rt);
	rt->coordinates = ft_split(rt->lineread[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("error in cylinder coordinates", rt);
	set_coordinates(&rt->cylinders[cy].point, rt->coordinates, POINT);
	free_ptrptr(&rt->coordinates);
	rt->coordinates = ft_split(rt->lineread[2], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("error in cylinder coordinates", rt);
	set_coordinates(&rt->cylinders[cy].vector, rt->coordinates, VECTOR);
	if (!validate_normalized_vector(rt->cylinders[cy].vector))
		print_error("the cylinders vector is not normalized", rt);
	free_ptrptr(&rt->coordinates);
	if (!validate_double(rt->lineread[3]))
		print_error("error in cylinder diameter", rt);
	rt->cylinders[cy].diameter = ft_atod(rt->lineread[3]);
	if (rt->cylinders[cy].diameter <= EPSILON)
		print_error("Error in cylinder diamter", rt);
	if (!validate_double(rt->lineread[4]))
		print_error("error in cylinder height", rt);
	rt->cylinders[cy].heigh = ft_atod(rt->lineread[4]);
	if (rt->cylinders[cy].heigh <= EPSILON)
		print_error("Error in cylinder height", rt);
	//o felipe colocou algo sobre min e max do cylinder, ainda nao sei o qu eé isso então vou botar depois.
	rt->color = ft_split(rt->lineread[5], ',');
	if (!validate_color(rt->color))
		print_error("Error in cylinder color", rt);
	set_color(&rt->cylinders[cy].color, rt->color);
	free_ptrptr(&rt->color);
}

t_coordinates create_point(double x, double y, double z)
{
	t_coordinates tuple_point;
	
	tuple_point.x = x;
	tuple_point.y = y;
	tuple_point.z = z;
	tuple_point.w = 1;
	
	return (tuple_point);
}

t_coordinates create_vector(double x, double y, double z)
{
	t_coordinates tuple_vector;
	tuple_vector.x = x;
	tuple_vector.y = y;
	tuple_vector.z = z;
	tuple_vector.w = 0;

	return (tuple_vector);
}

int are_equals_tuple(t_coordinates a, t_coordinates b)
{
	if (are_equals(a.x, b.x) && are_equals(a.y, b.y) \
		&& are_equals(a.z, b.z) && are_equals(a.w, b.w))
		return (1);
	else
		return (0);
}

void validate_elements(t_rt *rt)
{
	if (!ft_strncmp(rt->lineread[0], "A", 2))
		validate_amb_light(rt);
	else if (!ft_strncmp(rt->lineread[0], "C", 2))
		validate_camera(rt);
	else if (!ft_strncmp(rt->lineread[0], "L", 2))
		validate_light(rt);
	else if (!ft_strncmp(rt->lineread[0], "sp", 3))
		rt->num_sp++;
	else if (!ft_strncmp(rt->lineread[0], "pl", 3))
		rt->num_pl++;
	else if (!ft_strncmp(rt->lineread[0], "cy", 3))
		rt->num_cy++;
	else
		print_error("there is a wrong element or object in the file", rt);
}

void add_objects(t_rt *rt)
{
	int i;

	i = 0;
	while(rt->linesread[i])
	{
		rt->lineread = ft_split(rt->linesread[i], ' ');
		static int	sp = 0;
		static int	pl = 0;
		static int	cy = 0;
		if (!ft_strncmp(rt->lineread[0], "sp", 3))
		{
			validate_sphere(rt, sp);
			sp++;
		}
		else if (!ft_strncmp(rt->lineread[0], "pl", 3))
		{
			validate_plane(rt, pl);
			pl++;
		}
		else if (!ft_strncmp(rt->lineread[0], "cy", 3))
		{
			validate_cylinder(rt, cy);
			cy++;
		}
		i++;
	}
}

void parser(t_rt *rt)
{
	int i;

	i = 0;
	while(rt->linesread[i])
	{
		rt->lineread = ft_split(rt->linesread[i], ' '); 
		validate_elements(rt);
		free_ptrptr(&rt->lineread);
		i++;
	}
	if (!rt->amb_light.amb_light || !rt->camera.camera || !rt->light.light)
		print_error("there is no amb_light, camera or light", rt);
	if (rt->num_sp)
		rt->spheres = (t_sphere *)ft_calloc(rt->num_sp + 1, sizeof(t_sphere));
	if (rt->num_pl)
		rt->planes = (t_plane *)ft_calloc(rt->num_pl + 1, sizeof(t_plane));
	if (rt->num_cy)
		rt-> cylinders = (t_cylinder *)ft_calloc(rt->num_cy + 1, sizeof(t_cylinder));
	add_objects(rt);
	free_ptrptr(&rt->linesread);
}

int main(int argc, char **argv)
{
	t_rt	*rt;
	int i;
	i = 0;
	
	rt = init_rt();
	check_arguments(argc, argv);
	read_file(rt, argv[1]);
	parser(rt);
	render(rt);
	mlx_image_to_window(rt->render.mlx, rt->render.image, 0, 0);
	mlx_loop_hook(rt->render.mlx, &close_window, rt);
	mlx_loop(rt->render.mlx);
}
