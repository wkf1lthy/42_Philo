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