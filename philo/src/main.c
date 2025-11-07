/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:03:39 by fabialme          #+#    #+#             */
/*   Updated: 2025/11/03 09:25:20 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	table = setup_table(ac, av);
	if (!table)
		return (EXIT_FAILURE);
	if (!start_simulation(table))
	{
		clean_table(table);
		return (EXIT_FAILURE);
	}
	join_simulation(table);
	clean_table(table);
	return (0);
}
