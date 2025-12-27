/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 19:57:28 by jinzhang          #+#    #+#             */
/*   Updated: 2025/12/27 21:12:56 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	*thread_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_forks);
		locked_printf(philo, "has taken a fork");
		precise_usleep(philo, philo->data->hunger_endurance);
		pthread_mutex_unlock(philo->left_forks);
		return (NULL);
	}
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (!simulation_over(philo->data))
	{
		if (philo->data->meal_limit > 0 &&
        philo->meal_eaten >= philo->data->meal_limit)
        	break;
		take_forks(philo);
		are_eating(philo);
		put_down_forks(philo);
		locked_printf(philo, "is sleeping");
		precise_usleep(philo, philo->data->sleep_duration);
		locked_printf(philo, "is thinking");
	}
	return (NULL);
}

bool	create_thread(t_data *d)
{
	int	i;

	i = -1;
	d->start_simulation = get_now_time_converter();
	while (++i < d->philo_count)
	{
		d->philo[i].previous_meal = d->start_simulation;
		if (pthread_create(&d->philo[i].thread_id, NULL, &thread_start,
				&d->philo[i]) != 0)
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
