#include "libs/libft/includes/libft.h"
#include <stdio.h>

int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

unsigned int	convert_color(char *value)
{
	return (create_trgb(255, ft_atoi(value), ft_atoi(ft_strchr(value, ',') + 1), ft_atoi(ft_strrchr(value, ',') + 1)));
}

int main(void)
{
	printf("%x\n", convert_color("192,15,0"));
	return (0);
}