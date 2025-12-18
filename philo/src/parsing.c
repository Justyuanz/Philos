#include "philosophers.h"

/*
◦ number_of_philosophers: The number of philosophers and also the number
of forks.
◦ time_to_die (in milliseconds): If a philosopher has not started eating within
time_to_die milliseconds since the start of their last meal or the start of the
simulation, they die.
◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
◦ number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.
*/

bool fork_init(t_data *d)
{
	int	i;

	i = -1;
	while ( ++i < d->philo_count)
	{
		
	}
	return (true);
}
}

bool	philo_init(t_data *d)
{
	int	i;

	i = -1;
	while ( ++i < d->philo_count)
	{
		d->philo[i].philo_id = i + 1;
		fprintf(stderr, "philo id: %d\n", d->philo[i].philo_id);
	}
	return (true);
}


bool	data_init(t_data *d)
{
	d->philo = malloc (d->philo_count * sizeof (t_philo));
	if (!d->philo)
		return (error_msg("malloc fail"));
	d-//fork?
	philo_init(d);
	return (true);
}

bool	input_validation(int argc, char **argv, t_data *d)
{
	int		error_flag;

	error_flag = 0;
	if (!(argc == 5 || argc == 6))
	return(error_msg("usage: ./philo n_philos t_die t_eat t_sleep [must_eat]"));
	d->philo_count = parse_number(argv[1], &error_flag);
	d->hunger_endurance = parse_number(argv[2], &error_flag);
	d->eat_duration = parse_number(argv[3], &error_flag);
	d->sleep_duration = parse_number(argv[4], &error_flag);
	if (argv[5])
		d->meal_limit = parse_number(argv[5], &error_flag);
	else
		d->meal_limit = -1;
	if (error_flag)
		return (error_msg("invalid input, only digits allowed"));
	return (true);
}

