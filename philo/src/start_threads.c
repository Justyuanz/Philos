#include "philosophers.h"

/*
Think of pthread_create as: Start running this function in parallel,
and give it one piece of data to work with.”
*/
/*
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
	 while (!philo->data->end_simulation)
	 {
		take_forks(philo);
		are_eating(philo);
		put_down_forks(philo);
		locked_printf(philo, "is sleeping");
		precise_usleep (philo->data->sleep_duration);
		locked_printf(philo, "is thinking");
	}
	return (NULL);
}

bool create_thread(t_data *d)
{
	int	i;
	i = -1;
	d->start_simulation = get_now_time_converter();
	while (++i < d->philo_count)
	{
		if (pthread_create(&d->philo[i].thread_id, NULL, &thread_start, &d->philo[i]) != 0)
			return (false);
	}
	main_monitor(d);
	i = -1;
	while (++i < d->philo_count)
	{
		if (pthread_join(d->philo[i].thread_id, NULL) != 0)
			return (false);
	}
	return (true);
}