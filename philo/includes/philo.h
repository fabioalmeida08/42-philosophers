/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:05:00 by fabialme          #+#    #+#             */
/*   Updated: 2025/11/07 16:03:17 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define VALIDATE_ERROR_MSG "\
Usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>\
[number_of_times_each_philosopher_must_eat]\n\
\n\
Arguments:\n\
  number_of_philosophers               The number of philosophers (and forks).\n\
  time_to_die (ms)                     Time until a philosopher dies if they don't start eating.\n\
  time_to_eat (ms)                     Time it takes for a philosopher to eat (needs two forks).\n\
  time_to_sleep (ms)                   Time a philosopher spends sleeping.\n\
  number_of_times_each_philosopher_must_eat (optional)\n\
                                       If specified,\
simulation stops when all have eaten this many times.\n"

# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_FORK "has taken a fork"
# define MSG_DIED "died"

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	pthread_t	thread_id;
	t_mtx		*l_fork;
	t_mtx		*r_fork;
	t_mtx		eat_lock;
	long		last_meal_time;
	int			total_meal_counter;
	t_table		*table;
	bool		satisfied;
}	t_philo;

struct s_table
{
	int			total_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		start_time;
	int			total_meals;
	bool		end_simulation;
	t_mtx		sim_lock;
	t_mtx		print_lock;
	t_mtx		*forks;
	pthread_t	monitor_thread;
	t_philo		*philos;
};

void	input_error_msg(int arg_nbr, char *av);
long	ft_get_time_ms(void);
void	*ft_calloc(size_t nmemb, size_t size);
void	print_msg(t_philo *philo, char *msg);
int		ft_validate(int ac, char **av);
t_table	*setup_table(int ac, char **av);
long	ft_atol(const char *nptr);
void	clean_forks(t_mtx *forks, int i);
void	clean_philos(t_philo *philos, int i);
void	clean_table(t_table *table);
void	*philo_routine(void *data);
bool	start_simulation(t_table *table);
bool	stop_simulation(t_table *table);
int		ft_usleep(size_t milliseconds);

void	debug_print_table(t_table *table);
void	debug_print_philos(t_table *table);

bool	check_meals(t_philo *philo);
bool	check_sim(t_philo *philo);
void	*monitor_routine(void *data);
bool	join_simulation(t_table *table);
t_mtx	*set_first_fork(t_philo *philo);
t_mtx	*set_second_fork(t_philo *philo);

#endif // !PHILO_H
