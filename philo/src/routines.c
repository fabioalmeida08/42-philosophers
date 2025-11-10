/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:21:44 by fabialme          #+#    #+#             */
/*   Updated: 2025/11/07 16:06:12 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_think(t_philo *philo)
{
	if (!check_sim(philo))
		return ;
	print_msg(philo, MSG_THINK);
}

void	philo_sleep(t_philo *philo)
{
	print_msg(philo, MSG_SLEEP);
	ft_usleep(philo->table->time_to_sleep);
}

void	one_philo_routine(t_philo *philo)
{
	print_msg(philo, MSG_FORK);
	ft_usleep(philo->table->time_to_die);
	print_msg(philo, MSG_DIED);
	pthread_mutex_lock(&philo->table->sim_lock);
	philo->table->end_simulation = true;
	pthread_mutex_unlock(&philo->table->sim_lock);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, MSG_FORK);
	pthread_mutex_lock(philo->r_fork);
	print_msg(philo, MSG_FORK);
	print_msg(philo, MSG_EAT);
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_meal_time = ft_get_time_ms();
	philo->total_meal_counter++;
	pthread_mutex_unlock(&philo->eat_lock);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_meal_time = ft_get_time_ms();
	pthread_mutex_unlock(&philo->eat_lock);
	if (philo->table->total_philos == 1)
	{
		one_philo_routine(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (check_sim(philo))
	{
		philo_eat(philo);
		philo_think(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
