#include "philosophers.h"

static bool	error_msg_parsing(char *msg)
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

static int	parse_number(const char *str, int *error)
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

bool	input_validation(int argc, char **argv, t_data *d)
{
	int		error_flag;

	error_flag = 0;
	if (!(argc == 5 || argc == 6))
	return(error_msg_parsing("usage: ./philo n_philos t_die t_eat t_sleep [must_eat]"));
	d->philo_count = parse_number(argv[1], &error_flag);
	d->hunger_endurance = parse_number(argv[2], &error_flag);
	d->eat_duration = parse_number(argv[3], &error_flag);
	d->sleep_duration = parse_number(argv[4], &error_flag);
	if (argv[5])
		d->meal_limit = parse_number(argv[5], &error_flag);
	else
		d->meal_limit = -1;
	if (error_flag)
		return (error_msg_parsing("invalid input, only digits allowed"));
	return (true);
}

