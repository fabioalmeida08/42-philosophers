/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:50:42 by fabialme          #+#    #+#             */
/*   Updated: 2025/11/07 16:01:37 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_mtx	*set_first_fork(t_philo *philo)
{
	t_mtx	*first_fork;

	if (philo->l_fork > philo->r_fork)
		first_fork = philo->l_fork;
	else
		first_fork = philo->r_fork;
	return (first_fork);
}

t_mtx	*set_second_fork(t_philo *philo)
{
	t_mtx	*second_fork;

	if (philo->l_fork < philo->r_fork)
		second_fork = philo->l_fork;
	else
		second_fork = philo->r_fork;
	return (second_fork);
}
