#ifndef PHILO_H
# define PHILO_H

# include "utils.h"

int		take_forks(t_philo *philo);
int		return_forks(t_philo *philo);
int		create_philo_threads(t_philo *philo);
void	print_message(t_philo *philo, const char *msg);

#endif