#include	"utils.h"

int	ft_usleep(long usec)
{
	struct timeval	s_time;
	long			start_time;

	if (gettimeofday(&s_time, NULL))
		return (error_message("gettimeofday() error", -1));
	start_time = s_time.tv_sec * 1000000 + s_time.tv_usec;
	while (1)
	{
		usleep(50);
		if (gettimeofday(&s_time, NULL))
			return (error_message("gettimeofday() error", -1));
		if (s_time.tv_sec * 1000000 + s_time.tv_usec - start_time >= usec)
			break ;
	}
	return (SUCCESS);
}
