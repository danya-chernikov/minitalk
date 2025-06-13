#include "libft.h"

char	*ft_int_to_hex(unsigned long long num, int dcase)
{
	char	*lower;
	char	*upper;
	char	*str;
	int		i;

	lower = "0123456789abcdef\0";
	upper = "0123456789ABCDEF\0";
	str = ft_calloc(32, sizeof (char));
	if (str == NULL)
		return (NULL);
	if (num == 0)
		str[0] = '0';
	i = 0;
	while (num != 0)
	{
		if (dcase == 1)
			str[i] = lower[num % 16];
		else if (dcase == 2)
			str[i] = upper[num % 16];
		num /= 16;
		i++;
	}
	return (ft_reverse_str(str));
}
