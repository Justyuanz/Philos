#include "philosophers.h"

/*
Think of pthread_create as:
“Start running this function in parallel,
and give it one piece of data to work with.”

pthread_create(
    where_to_store_thread_id,
    thread_options_or_NULL,
    function_the_thread_will_run,
    data_given_to_that_function
);

The job order is random because threads run concurrently
and the OS scheduler decides when each one runs.
*/

static void *thread_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	locked_printf(philo, "is starting job");
	take_forks(philo);
	//is_thinking(philo);
	//sleep
	return (NULL);
}

bool create_thread(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->philo_count)
	{
		if (pthread_create(&d->philo[i].thread_id, NULL, &thread_start, &d->philo[i]) != 0)
			return (false);
	}
	i = -1;
	while (++i < d->philo_count)
	{
		if (pthread_join(d->philo[i].thread_id, NULL) != 0)
			return (false);
	}
	return (true);
}