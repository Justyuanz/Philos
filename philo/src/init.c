/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 19:57:38 by jinzhang          #+#    #+#             */
/*   Updated: 2025/12/27 19:57:40 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_init(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->philo_count)
	{
		pthread_mutex_init(&d->forks[i], NULL);
		pthread_mutex_init(&d->meal_locks[i], NULL);
		d->philo[i].philo_id = i + 1;
		d->philo[i].data = d;
		d->philo[i].meal_eaten = 0;
		d->philo[i].left_forks = &d->forks[i];
		d->philo[i].right_forks = &d->forks[(i + 1) % d->philo_count];
		d->philo[i].meal_lock = &d->meal_locks[i];
	}
}

bool	data_init(t_data *d)
{
	d->philo = NULL;
	d->forks = NULL;
	d->print_lock = NULL;
	d->end_simulation = 0;
	d->end_simulation_lock = NULL;
	d->philo = malloc(d->philo_count * sizeof(t_philo));
	if (!d->philo)
		return (cleanup_free(d, "malloc fail\n"));
	d->forks = malloc(d->philo_count * sizeof(pthread_mutex_t));
	if (!d->forks)
		return (cleanup_free(d, "malloc fail\n"));
	d->print_lock = malloc(1 * sizeof(pthread_mutex_t));
	if (!d->print_lock)
		return (cleanup_free(d, "malloc fail\n"));
	d->end_simulation_lock = malloc(1 * sizeof(pthread_mutex_t));
	if (!d->end_simulation_lock)
		return (cleanup_free(d, "malloc fail\n"));
	d->meal_locks = malloc(d->philo_count * sizeof(pthread_mutex_t));
	if (!d->meal_locks)
		return (cleanup_free(d, "malloc fail\n"));
	pthread_mutex_init(d->print_lock, NULL);
	pthread_mutex_init(d->end_simulation_lock, NULL);
	philo_init(d);
	return (true);
}
