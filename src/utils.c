#include "../inc/cub3d.h"
#include <stdlib.h>

void	put_error_and_exit(char *msg, int exitcode)
{
	ft_putendl_fd(msg, 2);
	exit(exitcode);
}