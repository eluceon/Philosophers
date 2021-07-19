#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/time.h>

# define RED_COLOR		"\033[1;31m"
# define NONE_COLOR 	"\033[0;0m"
# define GREEN_COLOR	"\033[0;32m"

# define SUCCESS	0
# define FAILURE	1

# define FALSE	0
# define TRUE	1

typedef struct s_fork
{
	pthread_mutex_t	right;
	pthread_mutex_t	*left;
}	t_fork;

typedef struct s_common {
	int				died;
	pthread_mutex_t	mutex_print;
}	t_common;

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
	pthread_mutex_t	mutex_death;
	pthread_t		tid_philo;
	pthread_t		tid_death;
	t_fork			fork;
	t_common		*common;
}				t_philo;

int		ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		error_message(char *description, int error_code);
long	get_time(void);
int		ft_usleep(long usec);
int		check_args(int argc, char *argv[]);
int		clear_philo(t_philo	*philo, int ret_value);

#endif