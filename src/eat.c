#include "philo.h"

int ft_meals_eaten(t_philo **philo)
{
    pthread_mutex_lock(&(*philo)->data->mealsmutex);
    if((*philo)->data->meals_eaten == (*philo)->data->number)
    {
        pthread_mute_unlock(&(*philo)->data->mealsmutex);
        return(1);
    }
    pthread_mutex_unlock(&(*philo)->data->mealsmutex);
    return(0);
}

int	ft_check_eating_time(t_philo **philo, int i, int id)
{
	if(i == 0)
	{
		pthread_mutex_lock(&(*philo)->st_eatingmutex);
		(*philo)->started_eating = (ft_gettime() - (*philo)->data->t_to_die);
		pthread_mutex_unlock(&(*philo)->st_eatingmutex);
	}
	if(i == 1)
	{
		pthread_mutex_lock(&(*philo)[id].st_eatingmutex);
		if((ft_gettime() - (*philo)->data->st_time)
			- (*philo)[id].started_eating >= (*philo)->data->t_to_die)
		{
			pthread_mutex_unlock(&(*philo)[id].st_eatingmutex);
			return(1);
		}
		pthread_mutex_lock(&(*philo)[id].st_eatingmutex);
	}
	return(0);
}

void	ft_incr_meals_eaten(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->data->mealsmutex);
	(*philo)->data->meals_eaten++;
	pthread_mutex_unlock(&(*philo)->data->mealsmutex);
}

int	ft_take_first_fork(t_philo **philo)
{
	int	f;

	f = 0;
	if(!ft_check_death(philo) && !ft_check_meals_eaten(philo))
	{
		pthread_mutex_lock(&(*philo)->mutex_lfork);
		f += 1;
		if((*philo)->data->number != 1)
		{
			pthread_mutex_lock((*philo)->mutex_rfork);
			f += 1;
		}
		ft_philo_print(philo, "%lld %d has taken a fork\n");
	}
	return(f);
}