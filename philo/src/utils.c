#include "philosophers.h"

bool	error_msg(char *msg)
{
	printf("%s\n", msg);
	return (false);
}

static bool number_only(const char *str)
{
	int i;

	i = 0;
	if (str[i] == '\0')
		return (false);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			return (false);
	}
	return (true);
}


int	parse_number(const char *str, int *error)
{
	int		i;
	int		start;
	long	result;

	i = 0;
	result = 0;
	if (!number_only(str))
		return (*error = 1);
	start = i;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - '0';
	if (i - start > 10)
		return (*error = 1);
	if ((result > INT_MAX))
		return (*error = 1);
	return (result);
}