#include "utils.h"

/*
** The function get_time_ms() returns the epoch time (since 1 January 1970)
** in microseconds.
*/
long	get_time(void)
{
	struct timeval	s_time;

	if (gettimeofday(&s_time, NULL))
		return (error_message("gettimeofday() error", 0));
	return (s_time.tv_sec * 1000000 + s_time.tv_usec);
}
