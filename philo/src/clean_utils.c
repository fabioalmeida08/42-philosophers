/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 09:55:13 by fabialme          #+#    #+#             */
/*   Updated: 2025/10/31 10:27:48 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clean_forks(t_mtx *forks, int i)
{
	while (--i)
		pthread_mutex_destroy(&forks[i]);
	free(forks);
}

void	clean_philos(t_philo *philos, int i)
{
	while (i--)
		pthread_mutex_destroy(&philos[i].eat_lock);
	free(philos);
}

void	clean_table(t_table *table)
{
	if (table->philos)
		clean_philos(table->philos, table->total_philos);
	if (table->forks)
		clean_forks(table->forks, table->total_philos);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->sim_lock);
	free(table);
}
