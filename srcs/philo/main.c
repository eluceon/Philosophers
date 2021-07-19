#include "philo.h"

void	ft_init_mutex(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].nbr_philos)
	{
		pthread_mutex_init(&philo[i].fork.right, NULL);
		pthread_mutex_init(&philo[i].mutex_death, NULL);
		if (i != 0)
			philo[i].fork.left = &philo[i - 1].fork.right;
	}
	philo[0].fork.left = &philo[philo[0].nbr_philos - 1].fork.right;
}

int	init_philo(t_philo *philo, int argc, char *argv[], t_common *common)
{
	int	i;

	philo[0].start_time = get_time();
	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		philo[i].start_time = philo[0].start_time;
		philo[i].nbr_philos = ft_atoi(argv[1]);
		philo[i].time_to_die = ft_atoi(argv[2]) * 1000;
		philo[i].time_to_eat = ft_atoi(argv[3]) * 1000;
		philo[i].time_to_sleep = ft_atoi(argv[4]) * 1000;
		if (argc == 6)
			philo[i].nbr_meals = ft_atoi(argv[5]);
		else
			philo[i].nbr_meals = -1;
		philo[i].last_meal = philo[i].start_time;
		philo[i].meal_cnt = 0;
		philo[i].id = 1 + i;
		philo[i].common = common;
	}
	ft_init_mutex(philo);
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_philo		*philo;
	t_common	common;
	int			i;

	if (check_args(argc, argv) != SUCCESS)
		return (EXIT_FAILURE);
	philo = (t_philo *)(malloc)(ft_atoi(argv[1]) * sizeof(t_philo));
	if (!philo)
		return (ENOMEM);
	pthread_mutex_init(&common.mutex_print, NULL);
	common.died = FALSE;
	if (init_philo(philo, argc, argv, &common) != SUCCESS)
		return (EXIT_FAILURE);
	if (create_philo_threads(philo) != SUCCESS)
		return (clear_philo(philo, EXIT_FAILURE));
	i = -1;
	while (++i < philo[0].nbr_philos)
	{
		if (pthread_join(philo[i].tid_philo, NULL) != 0)
			return (EXIT_FAILURE);
	}
	return (clear_philo(philo, EXIT_SUCCESS));
}
