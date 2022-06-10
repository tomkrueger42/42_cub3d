#include "cub3d.h"

int	create_trgb(unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	return (*(int *)(unsigned char [4]){t, b, g, r});
}
