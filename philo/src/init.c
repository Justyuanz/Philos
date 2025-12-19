#include "philosophers.h"

static void forks_init(t_data *d)
{
	int	i;

	i = -1;
	while ( ++i < d->philo_count)
	{
		pthread_mutex_init(&d->forks[i],NULL); //from 0 - (philo_id - 1)
	}
}

static void	philo_init(t_data *d)
{
	int	i;

	i = -1;
	while ( ++i < d->philo_count)
	{
		d->philo[i].philo_id = i + 1;
		d->philo[i].data = d;
		d->philo[i].left_forks = &d->forks[i];
		d->philo[i].right_forks = &d->forks[(i + 1) % d->philo_count];
	}
}

bool	data_init(t_data *d)
{
	d->philo = NULL;
	d->forks = NULL;
	d->print_lock = NULL;
	d->philo = malloc (d->philo_count * sizeof (t_philo));
	if (!d->philo)
		return (cleanup_free(d, "malloc fail\n"));
	d->forks = malloc(d->philo_count * sizeof (pthread_mutex_t));
	if (!d->forks)
		return (cleanup_free(d, "malloc fail\n"));
	d->print_lock = malloc(1 * sizeof (pthread_mutex_t));
	if (!d->print_lock)
		return (cleanup_free(d, "malloc fail\n"));
	forks_init(d);
	philo_init(d);
	pthread_mutex_init(d->print_lock, NULL);
	return (true);
}
