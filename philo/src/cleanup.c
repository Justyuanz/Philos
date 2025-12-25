#include "philosophers.h"

bool cleanup_free(t_data *d, char *msg)
{
	if (d->philo)
	{
		free(d->philo);
		d->philo = NULL;
	}
	if (d->forks)
	{
		free(d->forks);
		d->forks = NULL;
	}
	if (d->print_lock)
	{
		free (d->print_lock);
		d->print_lock = NULL;
	}
	if (d->end_simulation_lock)
	{
		free (d->end_simulation_lock);
		d->end_simulation_lock = NULL;
	}
	if (msg)
		printf("%s", msg);
	return (false);
}

bool  cleanup_all(t_data *d, char *msg)
{
	int	i;

	i = -1;
	while (++i < d->philo_count)
	{
		pthread_mutex_destroy(&d->forks[i]);
	}
	pthread_mutex_destroy(d->print_lock);
	pthread_mutex_destroy(d->end_simulation_lock);
	cleanup_free(d, msg);

	return (false);
}