#include "libft.h"

char	*ft_reverse_str(char *str)
{
	size_t	i;
	size_t	slen;
	char	tmp;

	i = 0;
	slen = ft_strlen(str);
	while (i < slen >> 1)
	{
		tmp = str[i];
		str[i] = str[slen - i - 1];
		str[slen - i - 1] = tmp;
		i++;
	}
	return (str);
}
