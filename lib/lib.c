#include "lib.h"

void	*memcpy(void *dest, const void *src, int n)
{
	char		*ndest = dest;
	const char	*nsrc = src;
	while (n > 0)
	{
		*ndest = *nsrc;
		ndest++;
		nsrc++;
		n--;
	}
	return (dest);
}

int	ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}