/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:03:01 by hbouchel          #+#    #+#             */
/*   Updated: 2025/02/10 17:11:58 by hbouchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_all(t_philo *philos, t_fork *forks)
{
	int	i;

	i = 0;
	while (i < philos->param->num)
	{
		pthread_mutex_destroy(&(philos->l_fork->lock));
		pthread_mutex_destroy(&(philos->meal_lock));
		i++;
	}
	pthread_mutex_destroy(&(philos->param->mutex_is_dead));
	free(philos);
	free(forks);
}

void	eating(t_philo *phil)
{
	write_state("is eating", phil);
	if (phil->param->is_dead == 1)
		return ;
	ft_usleep(phil->param->time_to_eat, phil);
	pthread_mutex_lock(&(phil->meal_lock));
	phil->last_meal = get_timestamp() - phil->param->start_time;
	pthread_mutex_unlock(&(phil->meal_lock));
	pthread_mutex_lock(&(phil->param->mutex_is_dead));
	phil->meal_count++;
	pthread_mutex_unlock(&(phil->param->mutex_is_dead));
	release_fork_and_sleep(phil);
}

void	*philo_life(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	if (phil->pos % 2 == 0)
		ft_usleep(phil->param->time_to_eat, phil);
	while (!is_dead(phil))
	{
		if (phil->meal_count == phil->param->meal_max
			&& phil->param->meal_max > 0)
			break ;
		take_fork('l', phil);
		if (phil->l_taken)
			take_fork('r', phil);
		if (phil->l_taken && phil->r_taken)
			eating(phil);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_params	params;
	t_philo		*philos;
	t_fork		*forks;

	if (!init_params(&params, ac, av))
		exit_error("Wrong set of params");
	if (!create_philos(&philos, &forks, &params))
		exit_error("An error occured while creating philosophers");
	if (!create_threads(&philos, &params))
		return (stop_thread(&philos[0]), 0);
	if (!wait_threads(&philos, &params))
		return (free_all(philos, forks), 0);
	return (free_all(philos, forks), 0);
}
