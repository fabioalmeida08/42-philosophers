/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:38:12 by fabialme          #+#    #+#             */
/*   Updated: 2025/11/04 10:01:54 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	join_simulation(t_table *table)
{
	int	i;

	i = 0;
	if (!table)
		return (false);
	while (i < table->total_philos)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(table->monitor_thread, NULL);
	return (true);
}

bool	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	if (!table)
		return (false);
	table->start_time = ft_get_time_ms();
	while (i < table->total_philos)
	{
		if (pthread_create(&table->philos[i].thread_id,
				NULL, philo_routine, (void *)&table->philos[i]) != 0)
			return (false);
		i++;
	}
	if (pthread_create(&table->monitor_thread,
			NULL, monitor_routine, (void *)table) != 0)
		return (false);
	return (true);
}
