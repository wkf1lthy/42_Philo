/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:11:30 by hbouchel          #+#    #+#             */
/*   Updated: 2025/02/10 17:11:37 by hbouchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define INT_MAX 2147483647

typedef struct s_params
{
	int				num;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				meal_max;
	long			start_time;
	int				is_dead;
	pthread_mutex_t	mutex_is_dead;
	pthread_t		death_thread;
}					t_params;

typedef struct s_fork
{
	int				used;
	pthread_mutex_t	lock;
}					t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	int				pos;
	long			last_meal;
	int				meal_count;

	pthread_mutex_t	meal_lock;

	t_fork			*l_fork;
	int				l_taken;
	t_fork			*r_fork;
	int				r_taken;

	t_params		*param;
}					t_philo;

// UTILS.C
void				exit_error(char *msg);
long long			ft_atoi(const char *str);
void				write_state(char *str, t_philo *phil);
int					ft_usleep(size_t milliseconds, t_philo *phil);
long				get_timestamp(void);

// INIT.C
int					check_input(char **av);
int					init_params(t_params *params, int ac, char **av);
int					create_philos(t_philo **philos, t_fork **forks,
						t_params *params);

// THREADS.C
int					create_threads(t_philo **philos, t_params *params);
int					wait_threads(t_philo **philos, t_params *params);

// DEATH.C
int					is_dead(t_philo *phil);
int					check_death(t_philo *phil, long current_time);
void				*check_philos_death(void *arg);
int					stop_thread(t_philo *phil);
int					all_philo_have_eat(t_philo **philos);

// FORK.C
void				take_fork(char fork_name, t_philo *phil);
void				release_fork_and_sleep(t_philo *phil);
void				release_fork(char fork_name, t_philo *phil);

// MAIN.C
void				*philo_life(void *arg);
void				free_all(t_philo *philos, t_fork *forks);
void				eating(t_philo *phil);

#endif
