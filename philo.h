#ifndef	PHILO_H
# define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 

typedef struct timeval	t_timeval;

typedef struct s_data
{
	int	number;
	int	meals;
	int	t_to_sleep;
	int	t_to_die;
	int	meals_eaten;
	long long	st_time;
	pthread_mutex_t	datamutex;
	pthread_mutex_t	mealsmutex;
	pthread_mutex_t	deathmutex;
	pthread_mutex_t	printmutex;
}       t_data;

typedef struct s_philo
{
    int philo_id;
    pthread_mutex_t	st_eatingmutex;
    pthread_mutex_t	mutex_lfork;
    pthread_mutex_t	*mutex_rfork;
    t_data  *data;
	long long int	started_eating;
}       t_philo;

void clear_data(t_data *data);
void    ft_clear_philo(t_philo **philo, int forknb, int eatnb, int philonb);
int ft_parse_and_check(char **av, int *args);
int	ft_atoi(char *str);
long int	ft_atol(char *str);
void    *ft_philo_routine(t_philo *philo);
void    ft_sleep_func(t_philo **philo, long long msec);
long long   ft_gettime(void);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void    ft_philo_print(t_philo **philo, char *str);
void    ft_philo_sleep(t_philo **philo, int nb);
int	ft_meals_eaten(t_philo **philo);
int	ft_check_eating_time(t_philo **philo, int i, int id);

#endif