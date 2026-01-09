/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 19:57:28 by jinzhang          #+#    #+#             */
/*   Updated: 2026/01/07 15:07:50 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_forks);
	locked_printf(philo, "has taken a fork");
	precise_usleep(philo, philo->data->hunger_endurance);
	pthread_mutex_unlock(philo->left_forks);
	return (NULL);
}

static void	*thread_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
		return (lonely_philo(philo));
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (!simulation_over(philo->data))
	{
		if (philo->data->meal_limit > 0
			&& philo->meal_eaten >= philo->data->meal_limit)
			break ;
		if (!take_forks(philo))
			return (NULL);
		if (!are_eating(philo))
		{
			put_down_forks(philo);
			return (NULL);
		}
		put_down_forks(philo);
		locked_printf(philo, "is sleeping");
		precise_usleep(philo, philo->data->sleep_duration);
		locked_printf(philo, "is thinking");
	}
	return (NULL);
}

bool	join_threads(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->philo_count)
	{
		if (pthread_join(d->philo[i].thread_id, NULL) != 0)
			return (false);
	}
	return (true);
}

bool	create_thread(t_data *d)
{
	int	i;
	int	created;

	i = -1;
	created = 0;
	d->start_simulation = get_now_time_converter();
	while (++i < d->philo_count)
	{
		d->philo[i].previous_meal = d->start_simulation;
		if (pthread_create(&d->philo[i].thread_id, NULL, &thread_start,
				&d->philo[i]) != 0)
			break ;
		created++;
	}
	if (created < d->philo_count)
	{
		pthread_mutex_lock(d->end_simulation_lock);
		d->end_simulation = 1;
		pthread_mutex_unlock(d->end_simulation_lock);
		while (--created >= 0)
			pthread_join(d->philo[created].thread_id, NULL);
		return (false);
	}
	return (true);
}
