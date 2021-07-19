#include "bonus.h"

int	init_philo(t_philo *philo, int argc, char *argv[])
{
	philo->start_time = get_time_ms();
	philo->nbr_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->nbr_meals = ft_atoi(argv[5]);
	else
		philo->nbr_meals = -1;
	philo->last_meal = philo->start_time;
	philo->meal_cnt = 0;
	sem_unlink("sem_forks");
	sem_unlink("sem_end");
	sem_unlink("sem_print");
	sem_unlink("sem_all_forks");
	sem_unlink("sem_eaten_enough");
	sem_unlink("sem_death");
	philo->sem_forks = sem_open("sem_forks", O_CREAT, S_IRWXU,
			philo->nbr_philos);
	philo->sem_all_forks = sem_open("sem_all_forks", O_CREAT, S_IRWXU, 1);
	philo->sem_print = sem_open("sem_print", O_CREAT, S_IRWXU, 1);
	philo->sem_end = sem_open("sem_end", O_CREAT, S_IRWXU, 0);
	philo->sem_eaten_enough = sem_open("sem_eaten_enough", O_CREAT, S_IRWXU, 0);
	philo->sem_death = sem_open("sem_death", O_CREAT, S_IRWXU, 1);
	return (SUCCESS);
}

int	free_semaphores(t_philo *philo, int ret)
{
	sem_unlink("sem_print");
	sem_unlink("sem_forks");
	sem_unlink("sem_end");
	sem_unlink("sem_all_forks");
	sem_unlink("sem_eaten_enough");
	sem_unlink("sem_death");
	sem_close(philo->sem_print);
	sem_close(philo->sem_forks);
	sem_close(philo->sem_end);
	sem_close(philo->sem_all_forks);
	sem_close(philo->sem_eaten_enough);
	sem_close(philo->sem_death);
	return (ret);
}

int	main(int argc, char *argv[])
{
	t_philo		philo;

	if (check_args(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_philo(&philo, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_philo_processes(&philo) != SUCCESS)
		return (free_semaphores(&philo, EXIT_SUCCESS));
	return (free_semaphores(&philo, EXIT_SUCCESS));
}
