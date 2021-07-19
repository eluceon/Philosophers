#include "utils.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	check_big_numbers(int argc, char *argv[])
{
	if (ft_atoi(argv[1]) > 300 || ft_strlen(argv[1]) > 4)
		return (error_message("Many philosophers, max 300", EXIT_FAILURE));
	if (ft_atoi(argv[2]) > 10000 || ft_strlen(argv[2]) > 5
		|| ft_atoi(argv[3]) > 10000 || ft_strlen(argv[3]) > 5
		|| ft_atoi(argv[4]) > 10000 || ft_strlen(argv[4]) > 5)
		return (error_message("Max time 10000ms", EXIT_FAILURE));
	if (argc == 6 && (ft_atoi(argv[5]) > 10000 || ft_strlen(argv[5]) > 5))
		return (error_message("Max number each philosopher must eat 10000",
				EXIT_FAILURE));
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0 || (argc == 6 && ft_atoi(argv[5]) <= 0))
		return (error_message("Argument must be > 0", EXIT_FAILURE));
	return (SUCCESS);
}

int	check_args(int argc, char *argv[])
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (error_message("Wrong arguments", EXIT_FAILURE));
	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (error_message("Wrong arguments.", EXIT_FAILURE));
		}
	}
	return (check_big_numbers(argc, argv));
}

void	print_message(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->common->mutex_print);
	if (philo->common->died == FALSE)
		printf("%ldms #%d %s\n", (get_time() - philo->start_time) / 1000,
			philo->id, msg);
	pthread_mutex_unlock(&philo->common->mutex_print);
}

int	clear_philo(t_philo	*philo, int ret_value)
{
	int	i;

	i = -1;
	while (++i < philo->nbr_philos)
	{
		pthread_mutex_destroy(&philo[i].fork.right);
		pthread_mutex_destroy(&philo[i].mutex_death);
	}
	pthread_mutex_destroy(&philo->common->mutex_print);
	free(philo);
	return (ret_value);
}
