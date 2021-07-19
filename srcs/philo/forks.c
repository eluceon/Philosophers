#include "philo.h"

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork.right);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork.left);
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork.left);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork.right);
		print_message(philo, "has taken a fork");
	}
	return (SUCCESS);
}

int	return_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->fork.right);
		pthread_mutex_unlock(philo->fork.left);
	}
	else
	{
		pthread_mutex_unlock(philo->fork.left);
		pthread_mutex_unlock(&philo->fork.right);
	}
	return (SUCCESS);
}
