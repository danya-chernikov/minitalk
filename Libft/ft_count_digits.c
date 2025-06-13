#include "libft.h"

int	ft_count_digits(long long n)
{
	int	num;

	num = 0;
	if (n < 0)
		n = -n;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		num++;
	}
	return (num);
}
