/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:02:52 by hbouchel          #+#    #+#             */
/*   Updated: 2025/02/10 17:24:14 by hbouchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_input(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_init(t_params *params)
{
	if (params->num <= 0 || params->time_to_die <= 60
		|| params->time_to_eat < 60 || params->time_to_sleep < 60)
		return (1);
	if (params->num > INT_MAX || params->num > 200
		|| params->time_to_die > INT_MAX || params->time_to_eat > INT_MAX
		|| params->time_to_sleep > INT_MAX)
		return (1);
	return (0);
}

int	init_params(t_params *params, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("%s\n", "It should be :");
		printf("%s\n",
			"Number_of_philosophers time_to_die time_to_eat time_to_sleep");
		return (0);
	}
	params->num = ft_atoi(av[1]);
	params->time_to_die = ft_atoi(av[2]);
	params->time_to_eat = ft_atoi(av[3]);
	params->time_to_sleep = ft_atoi(av[4]);
	params->meal_max = -1;
	params->is_dead = 0;
	if (check_input(av))
		params->num = 0;
	if (ac == 6)
	{
		params->meal_max = ft_atoi(av[5]);
		if (ft_atoi(av[5]) < 0)
			return (0);
	}
	if (check_init(params))
		return (0);
	pthread_mutex_init(&params->mutex_is_dead, NULL);
	return (1);
}

void	init_philo(t_philo *phil, t_fork **forks, t_params *params, int current)
{
	phil->param = params;
	phil->pos = current;
	phil->last_meal = 0;
	phil->meal_count = 0;
	phil->r_fork = &((*forks)[current]);
	phil->r_taken = 0;
	phil->l_taken = 0;
	if (current == params->num - 1)
		phil->l_fork = &((*forks)[0]);
	else
		phil->l_fork = &((*forks)[current + 1]);
	phil->l_fork->used = 0;
	pthread_mutex_init(&(phil->l_fork->lock), NULL);
	pthread_mutex_init(&(phil->meal_lock), NULL);
}

int	create_philos(t_philo **philos, t_fork **forks, t_params *params)
{
	int	current;

	*philos = malloc(sizeof(t_philo) * params->num);
	if (!*philos)
		return (0);
	*forks = malloc(sizeof(t_fork) * params->num);
	if (!*forks)
	{
		free(*philos);
		return (0);
	}
	current = 0;
	while (current < params->num)
	{
		init_philo(&(*philos)[current], forks, params, current);
		current++;
	}
	return (1);
}
