/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:42:23 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/08 15:19:57 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_objects(t_rt *rt)
{
	int			i;
	static int	sp;
	static int	pl;
	static int	cy;

	sp = 0;
	pl = 0;
	cy = 0;
	i = -1;
	while (rt->linesread[++i])
	{
		rt->lineread = ft_split(rt->linesread[i], ' ');
		if (!ft_strncmp(rt->lineread[0], "sp", 3))
			validate_sphere(rt, sp++);
		else if (!ft_strncmp(rt->lineread[0], "pl", 3))
			validate_plane(rt, pl++);
		else if (!ft_strncmp(rt->lineread[0], "cy", 3))
			validate_cylinder(rt, cy++);
		free_ptrptr(&rt->lineread);
	}
}

void	parser(t_rt *rt)
{
	int	i;

	i = 0;
	while (rt->linesread[i])
	{
		rt->lineread = ft_split(rt->linesread[i], ' ');
		validate_elements(rt);
		free_ptrptr(&rt->lineread);
		i++;
	}
	if (!rt->amb_light.amb_light || !rt->camera.camera || !rt->light.light)
		print_error("there is no amb_light, camera or light", rt);
	if (rt->num_sp)
		rt->sphere = (t_sphere *)ft_calloc(rt->num_sp + 1, sizeof(t_sphere));
	if (rt->num_pl)
		rt->planes = (t_plane *)ft_calloc(rt->num_pl + 1, sizeof(t_plane));
	if (rt->num_cy)
		rt->cylinders = (t_cylinder *)ft_calloc(rt->num_cy + 1,
				sizeof(t_cylinder));
	add_objects(rt);
	free_ptrptr(&rt->linesread);
}
