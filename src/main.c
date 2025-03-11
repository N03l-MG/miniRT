/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:08:17 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/11 17:56:55 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int ac, char **av)
{
	int		fd;
	t_data	data;

	if (ac > 2)
	{
		printf("Too many arguments, expected 1.");
		return (1);
	}
	if (ac < 2)
	{
		printf("Too few arguments, expected 1.");
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	parse_elements(&data, fd);
	close(fd);
	return 0;
}
