#include "philo.h"

void	*philos_eaten_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->common->mutex_print);
	philo->common->died = TRUE;
	printf("Everyone has eaten at least %d times\n", philo[0].nbr_meals);
	pthread_mutex_unlock(&philo->common->mutex_print);
	return (NULL);
}

void	*philos_has_died(t_philo *philo)
{
	philo->common->died = TRUE;
	printf("%ldms #%d %s\n", (get_time() - philo->start_time) / 1000,
		philo->id, "has died");
	pthread_mutex_unlock(&philo->mutex_death);
	return (NULL);
}

void	*check_death_and_fed(void	*philo_v)
{
	t_philo	*philo;
	int		eaten_enough;
	int		i;

	philo = (t_philo *)philo_v;
	while (1)
	{
		eaten_enough = TRUE;
		i = -1;
		while (++i < philo[0].nbr_philos && philo->common->died == FALSE)
		{
			pthread_mutex_lock(&philo->mutex_death);
			if (get_time() - philo[i].last_meal > philo[i].time_to_die)
				return (philos_has_died(philo));
			pthread_mutex_unlock(&philo->mutex_death);
			if (philo[0].nbr_meals >= 0
				&& philo[i].meal_cnt < philo[0].nbr_meals)
				eaten_enough = FALSE;
		}
		if (philo[0].nbr_meals >= 0 && eaten_enough)
			return (philos_eaten_enough(philo));
	}
	return (NULL);
}

void	*philosophers(void	*philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	if (philo->nbr_philos == 1)
	{
		print_message(philo, "has taken a fork");
		while (philo->common->died == FALSE)
			continue ;
	}
	while (philo->common->died == FALSE)
	{
		take_forks(philo);
		pthread_mutex_lock(&philo->mutex_death);
		philo->last_meal = get_time();
		print_message(philo, "is eating");
		pthread_mutex_unlock(&philo->mutex_death);
		ft_usleep(philo->time_to_eat);
		philo->meal_cnt++;
		return_forks(philo);
		print_message(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		print_message(philo, "is thinking");
		ft_usleep(200);
	}
	return (NULL);
}

int	create_philo_threads(t_philo *philo)
{
	int			i;
	pthread_t	tid_death;

	if (pthread_create(&tid_death, NULL, &check_death_and_fed, philo) != 0)
		return (FAILURE);
	pthread_detach(tid_death);
	i = -1;
	while (++i < philo[0].nbr_philos)
	{
		if (pthread_create(&philo[i].tid_philo, NULL, &philosophers,
				&philo[i]) != 0)
			return (FAILURE);
	}
	return (SUCCESS);
}
