#include "bonus.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
	write(fd, "\n", 1);
}

int	error_message(char *description, int error_code)
{
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	ft_putstr_fd("[!] Philosophers: ", STDERR_FILENO);
	ft_putstr_fd(NONE_COLOR, STDERR_FILENO);
	ft_putendl_fd(description, STDERR_FILENO);
	return (error_code);
}

void	print_message(t_philo *philo, const char *msg)
{
	sem_wait(philo->sem_print);
	printf("%ldms #%d %s\n", get_time_ms() - philo->start_time, philo->id, msg);
	sem_post(philo->sem_print);
}
