#include "utils.h"

int	error_message(char *description, int error_code)
{
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	ft_putstr_fd("[!] Philosophers: ", STDERR_FILENO);
	ft_putstr_fd(NONE_COLOR, STDERR_FILENO);
	ft_putendl_fd(description, STDERR_FILENO);
	return (error_code);
}
