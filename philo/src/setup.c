/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 14:51:05 by fabialme          #+#    #+#             */
/*   Updated: 2025/11/04 09:43:16 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_mtx	*init_forks(int n_forks)
{
	t_mtx	*forks;
	int		i;

	forks = ft_calloc(n_forks, sizeof(t_mtx));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < n_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			clean_forks(forks, i);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static t_philo	*init_philos(t_table *table)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = ft_calloc(table->total_philos, sizeof(t_philo));
	if (!philos)
		return (NULL);
	while (i < table->total_philos)
	{
		philos[i].id = i + 1;
		philos[i].total_meal_counter = 0;
		philos[i].table = table;
		philos[i].satisfied = false;
		philos[i].last_meal_time = ft_get_time_ms();
		philos[i].l_fork = &table->forks[i];
		philos[i].r_fork = &table->forks[(i + 1) % table->total_philos];
		if (pthread_mutex_init(&philos[i].eat_lock, NULL) != 0)
		{
			clean_philos(philos, i);
			return (NULL);
		}
		i++;
	}
	return (philos);
}

static t_table	*init_table(int ac, char **av)
{
	t_table	*table;

	table = ft_calloc(1, sizeof(t_table));
	table->total_philos = (int) atol(av[1]);
	table->time_to_die = atol(av[2]);
	table->time_to_eat = atol(av[3]);
	table->time_to_sleep = atol(av[4]);
	table->total_meals = -1;
	table->end_simulation = false;
	if (ac == 6)
		table->total_meals = atol(av[5]);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0
		|| pthread_mutex_init(&table->sim_lock, NULL) != 0)
	{
		free(table);
		return (NULL);
	}
	return (table);
}

t_table	*setup_table(int ac, char **av)
{
	t_table	*table;

	if (!ft_validate(ac, av))
	{
		printf("%s", VALIDATE_ERROR_MSG);
		return (NULL);
	}
	table = init_table(ac, av);
	if (!table)
		return (NULL);
	table->forks = init_forks(table->total_philos);
	table->philos = init_philos(table);
	if (!table->forks || !table->philos)
	{
		clean_table(table);
		return (NULL);
	}
	return (table);
}
