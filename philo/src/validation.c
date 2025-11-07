/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:19:50 by fabialme          #+#    #+#             */
/*   Updated: 2025/10/30 10:24:05 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_atol(const char *nptr)
{
	long	sum;
	int		sign;

	sum = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		sum = (sum * 10) + (*nptr - '0');
		nptr++;
	}
	return (sum * sign);
}

int	ft_only_valid_chars(const char *nptr)
{
	if (!*nptr)
		return (0);
	if (*nptr == '+')
		nptr++;
	if (!*nptr)
		return (0);
	while (*nptr == ' ')
		nptr++;
	while (*nptr)
	{
		if (!(*nptr >= '0' && *nptr <= '9'))
			return (0);
		nptr++;
	}
	return (1);
}

int	ft_validate(int ac, char **av)
{
	int	i;

	i = 1;
	if ((ac < 5 || ac > 6))
	{
		printf("ERROR: Invalid number of Args\n");
		return (0);
	}
	while (av[i])
	{
		if (!ft_only_valid_chars(av[i]))
		{
			input_error_msg(i, av[i]);
			return (0);
		}
		if (ft_atol(av[i]) > INT_MAX)
		{
			printf("Value too big INT_MAX is the limit\n");
			return (0);
		}
		i++;
	}
	return (1);
}
