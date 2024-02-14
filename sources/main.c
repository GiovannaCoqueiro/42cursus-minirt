/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:48:51 by ada-cruz          #+#    #+#             */
/*   Updated: 2024/02/08 16:20:09 by gcoqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	degree_to_rad(double degree)
{
	return (degree * (M_PI / 180));
}

void	check_arguments(int argc, char **argv)
{
	int	len;

	len = 0;
	if (argc != 2)
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
	while (read(fd, &c, 1))
		rd++;
	close(fd);
	buffer = (char *)ft_calloc(rd + 1, sizeof(char));
	fd = open(file, O_RDONLY);
	read(fd, buffer, rd);
	close(fd);
	rt->linesread = ft_split(buffer, '\n');
	free(buffer);
}

int	main(int argc, char **argv)
{
	t_rt	*rt;
	int		i;

	i = 0;
	check_arguments(argc, argv);
	rt = init_rt();
	read_file(rt, argv[1]);
	parser(rt);
	set_transformations(rt);
	aux_view_transformation(rt);
	set_pixel_size(rt);
	render(rt);
	minirt(rt);
}
