/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:38:51 by gcoqueir          #+#    #+#             */
/*   Updated: 2024/02/08 15:49:02 by gcoqueir         ###   ########.fr       */
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

void	free_matrix(double **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
}

static void	free_sphere_plane(t_rt *rt)
{
	int	i;

	if (rt->sphere)
	{
		i = -1;
		while (++i < rt->num_sp)
		{
			free_matrix(rt->sphere[i].inverse_matrix);
			free_matrix(rt->sphere[i].transpose_matrix);
		}
	}
	if (rt->planes)
	{
		i = -1;
		while (++i < rt->num_pl)
		{
			free_matrix(rt->planes[i].inverse_matrix);
			free_matrix(rt->planes[i].transpose_matrix);
		}
	}
}

static void	free_cylinder_camera(t_rt *rt)
{
	int	i;

	if (rt->cylinders)
	{
		i = -1;
		while (++i < rt->num_cy)
		{
			free_matrix(rt->cylinders[i].inverse_matrix);
			free_matrix(rt->cylinders[i].transpose_matrix);
		}
	}
	if (rt->camera.invert_matrix)
		free_matrix(rt->camera.invert_matrix);
	if (rt->camera.trans_matrix)
		free_matrix(rt->camera.trans_matrix);
}

void	free_rt(t_rt *rt)
{
	free_ptrptr(&rt->linesread);
	free_ptrptr(&rt->lineread);
	free_ptrptr(&rt->color);
	free_ptrptr(&rt->coordinates);
	free(rt->material);
	free_sphere_plane(rt);
	free(rt->sphere);
	free(rt->planes);
	free_cylinder_camera(rt);
	free(rt->cylinders);
	if (rt->mlx.mlx)
	{
		mlx_destroy_window(rt->mlx.mlx, rt->mlx.window);
		if (rt->mlx.image)
			mlx_destroy_image(rt->mlx.mlx, rt->mlx.image);
		mlx_destroy_display(rt->mlx.mlx);
		free(rt->mlx.mlx);
	}
	free(rt);
	exit(0);
}
