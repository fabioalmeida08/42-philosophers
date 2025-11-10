/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 09:28:41 by fabialme          #+#    #+#             */
/*   Updated: 2025/11/04 10:11:28 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	check_limit_meals(t_table *table)
{
	int	i;
	int	satisfied_count;

	if (table->total_meals == -1)
		return (false);
	i = 0;
	satisfied_count = 0;
	while (i < table->total_philos)
	{
		pthread_mutex_lock(&table->philos[i].eat_lock);
		if (table->philos[i].total_meal_counter >= table->total_meals)
			satisfied_count++;
		pthread_mutex_unlock(&table->philos[i].eat_lock);
		i++;
	}
	return (satisfied_count == table->total_philos);
}

static int	check_starvation(t_table *table)
{
	int		i;
	long	time;

	i = 0;
	while (i < table->total_philos)
	{
		pthread_mutex_lock(&table->philos[i].eat_lock);
		time = ft_get_time_ms();
		if ((time - table->philos[i].last_meal_time) >= table->time_to_die)
		{
			pthread_mutex_unlock(&table->philos[i].eat_lock);
			return (table->philos[i].id);
		}
		pthread_mutex_unlock(&table->philos[i].eat_lock);
		i++;
	}
	return (0);
}

bool	check_sim(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->sim_lock);
	pthread_mutex_lock(&philo->eat_lock);
	if (philo->table->end_simulation
		|| (philo->total_meal_counter >= philo->table->total_meals
			&& philo->table->total_meals != -1))
	{
		pthread_mutex_unlock(&philo->eat_lock);
		pthread_mutex_unlock(&philo->table->sim_lock);
		return (false);
	}
	pthread_mutex_unlock(&philo->eat_lock);
	pthread_mutex_unlock(&philo->table->sim_lock);
	return (true);
}

void	*monitor_routine(void *data)
{
	t_table	*table;
	int		died_id;

	table = (t_table *)data;
	while (1)
	{
		died_id = check_starvation(table);
		if (died_id > 0)
		{
			print_msg(&table->philos[died_id - 1], MSG_DIED);
			pthread_mutex_lock(&table->sim_lock);
			table->end_simulation = true;
			pthread_mutex_unlock(&table->sim_lock);
			break ;
		}
		if (check_limit_meals(table))
		{
			pthread_mutex_lock(&table->sim_lock);
			table->end_simulation = true;
			pthread_mutex_unlock(&table->sim_lock);
			break ;
		}
	}
	return (NULL);
}
