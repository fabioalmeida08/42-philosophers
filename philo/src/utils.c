/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:23:35 by fabialme          #+#    #+#             */
/*   Updated: 2025/11/04 10:01:45 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	input_error_msg(int arg_nbr, char *av)
{
	if (arg_nbr == 1)
		printf("ERROR: Invalid Number of philosophers: %s\n", av);
	if (arg_nbr == 2)
		printf("ERROR: Invalid time to die: %s\n", av);
	if (arg_nbr == 3)
		printf("ERROR: Invalid time to eat: %s\n", av);
	if (arg_nbr == 4)
		printf("ERROR: Invalid time to sleep: %s\n", av);
	if (arg_nbr == 5)
		printf("ERROR: Invalid number of \
		times each philosopher must eat: %s\n", av);
}

long	ft_get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = ft_get_time_ms();
	while ((ft_get_time_ms() - start) < milliseconds)
		usleep(400);
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*mem;
	unsigned char	*tmp;
	size_t			i;

	if (!nmemb || !size)
		return (malloc(1));
	if (size && nmemb > (size_t) - 1 / size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	i = 0;
	tmp = (unsigned char *)mem;
	while (i < (nmemb * size))
		tmp[i++] = '\0';
	return (mem);
}

void	print_msg(t_philo *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->table->sim_lock);
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->end_simulation)
	{
		time = ft_get_time_ms();
		printf("%ld %d %s\n", time - philo->table->start_time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->table->sim_lock);
	pthread_mutex_unlock(&philo->table->print_lock);
}
