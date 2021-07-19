#ifndef BONUS_H
# define BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>
# include <unistd.h>
# include <pthread.h>

# define RED_COLOR		"\033[1;31m"
# define NONE_COLOR 	"\033[0;0m"
# define GREEN_COLOR	"\033[0;32m"

# define SUCCESS	0
# define FAILURE	1

enum	e_separators
{
	FALSE,
	TRUE
};

typedef struct s_philo {
	long			start_time;
	long			last_meal;
	int				meal_cnt;
	int				id;
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_meals;
	sem_t			*sem_all_forks;
	sem_t			*sem_eaten_enough;
	sem_t			*sem_forks;
	sem_t			*sem_death;
	sem_t			*sem_print;
	sem_t			*sem_end;
}				t_philo;

int		ft_atoi(const char *str);
long	get_time_ms(void);
int		check_args(int argc, char *argv[]);
void	print_message(t_philo *philo, const char *msg);
int		error_message(char *description, int error_code);
int		ft_free(void *ptr, char *msg, int ret);
int		ft_usleep(long usec);
int		create_philo_processes(t_philo *philo);

#endif