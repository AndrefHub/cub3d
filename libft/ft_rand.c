#include "libft.h"
#define __INTERNAL 0
#define __EXTERNAL 1

static unsigned int _ft_srand(unsigned int _seed, int _flag)
{
	static unsigned int	_next = 1;
	static int	_prev = 0;

	if (!(_flag == __INTERNAL && _prev == __EXTERNAL))
		_next = _seed;
	_prev = _flag;
	return (_next);
}

void	ft_srand(unsigned int seed)
{
	_ft_srand(seed, __EXTERNAL);
}

int	ft_rand(void)
{
	static unsigned long int	next = 1;

	next = _ft_srand(next, __INTERNAL);
	next = next * 1103515245 + 12345;
	return ((int) ((unsigned int)(next/65536) % 32768));
}