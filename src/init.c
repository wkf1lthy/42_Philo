#include "../philo.h"

void	clear_data(t_data *data)
{
	pthread_mutex_destroy(&data->datamutex);
	pthread_mutex_destroy(&data->deathmutex);
	pthread_mutex_destroy(&data->printmutex);
	pthread_mutex_destroy(&data->mealsmutex);
}

void	ft_clear_philo(t_philo **philo, int forknb, int eatnb, int philonb)
{
	int	i;

	i = 0;
	if (forknb == -1)
		forknb = (*philo)->data->number;
	ft_join_threads(philo, philonb);
	i = 0;
	while (i < eatnb)
	{
		pthread_mutex_destroy(&(*philo)[i].st_eatingmutex);
		i++;
	}
	free(*philo);

	while (i < forknb)
	{
		pthread_mutex_destroy(&(*philo)[i].mutex_lfork);
		i++;
	}
	/*free(*philo);//peut etre supprimer ce 2e free.*/
}

int	ft_parse_and_check(char **av, int *args)
{
	int	i;

	i = 0;
	while (av[i + 1])
	{
		args[i] = ft_atoi(av[i + 1]);
		if (args[i] == -1 || args[i] != ft_atol(av[i + 1]))
			return (-1);
		i++;
	}
	if (args[0] == 0)
		return (-1);
	if (av[5] == NULL)
		args[4] = -1;
	return (0);//reflechir s'il ne doit pas retourner 0.
}
