#include "bonus.h"

void	*check_death(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	while (1)
	{
		sem_wait(philo->sem_death);
		if (get_time_ms() - philo->last_meal > philo->time_to_die)
		{	
			sem_wait(philo->sem_print);
			printf("%ldms #%d %s\n", get_time_ms() - philo->start_time,
				philo->id, "has died");
			sem_post(philo->sem_end);
			return (NULL);
		}
		sem_post(philo->sem_death);
		if (philo->meal_cnt == philo->nbr_meals)
			sem_post(philo->sem_eaten_enough);
	}
	return (NULL);
}

int	philosophers(t_philo *philo)
{
	pthread_t	tid_death;

	philo->last_meal = get_time_ms();
	pthread_create(&tid_death, NULL, check_death, philo);
	while (1)
	{
		sem_wait(philo->sem_all_forks);
		sem_wait(philo->sem_forks);
		print_message(philo, "has taken a fork");
		sem_wait(philo->sem_forks);
		print_message(philo, "has taken a fork");
		sem_wait(philo->sem_death);
		philo->last_meal = get_time_ms();
		print_message(philo, "is eating");
		sem_post(philo->sem_death);
		sem_post(philo->sem_all_forks);
		ft_usleep(philo->time_to_eat * 1000);
		philo->meal_cnt++;
		sem_post(philo->sem_forks);
		sem_post(philo->sem_forks);
		print_message(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep * 1000);
		print_message(philo, "is thinking");
	}
	return (SUCCESS);
}

void	*check_fed(void *philo_v)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_v;
	i = -1;
	while (++i < philo->nbr_meals)
		sem_wait(philo->sem_eaten_enough);
	if (philo->nbr_meals != -1)
	{
		sem_wait(philo->sem_print);
		printf("Everyone has eaten at least %d times\n", philo->nbr_meals);
		sem_post(philo->sem_end);
	}
	return (NULL);
}

int	check_fed_and_creat_child_processes(t_philo *philo,
	pid_t *pid, pthread_t *ph_fed)
{
	int	i;

	if (philo->nbr_meals != -1
		&& pthread_create(ph_fed, NULL, check_fed, (void *)philo) != 0)
		return (FAILURE);
	i = -1;
	while (++i < philo->nbr_philos)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (ft_free(pid, "Memory allocation error", FAILURE));
		if (!pid[i])
		{
			philo->id = i + 1;
			philosophers(philo);
		}
	}
	return (SUCCESS);
}

int	create_philo_processes(t_philo *philo)
{
	int			i;
	pid_t		*pid;
	pthread_t	ph_fed;

	pid = (pid_t *)malloc(sizeof(pid_t) * philo->nbr_philos);
	if (!pid)
		return (error_message("Memory allocation error", EXIT_FAILURE));
	if (check_fed_and_creat_child_processes(philo, pid, &ph_fed) == FAILURE)
		return (EXIT_FAILURE);
	sem_wait(philo->sem_end);
	i = -1;
	while (++i < philo->nbr_philos)
		kill(pid[i], SIGTERM);
	if (philo->nbr_meals != -1)
	{
		i = philo->nbr_meals;
		philo->nbr_meals = -1;
		while (--i >= 0)
			sem_post(philo->sem_eaten_enough);
		pthread_join(ph_fed, NULL);
	}
	free (pid);
	return (SUCCESS);
}
