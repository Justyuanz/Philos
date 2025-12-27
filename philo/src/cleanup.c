/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 19:56:53 by jinzhang          #+#    #+#             */
/*   Updated: 2025/12/27 20:14:50 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_ptr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

bool	cleanup_free(t_data *d, char *msg)
{
	if (d->philo)
		free_ptr(d->philo);
	if (d->forks)
		free_ptr(d->forks);
	if (d->print_lock)
		free_ptr(d->print_lock);
	if (d->end_simulation_lock)
		free_ptr(d->end_simulation_lock);
	if (d->meal_locks)
		free_ptr(d->meal_locks);
	if (msg)
		printf("%s", msg);
	return (false);
}

bool	cleanup_all(t_data *d, char *msg)
{
	int	i;

	i = -1;
	while (++i < d->philo_count)
	{
		pthread_mutex_destroy(&d->forks[i]);
		pthread_mutex_destroy(&d->meal_locks[i]);
	}
	pthread_mutex_destroy(d->print_lock);
	pthread_mutex_destroy(d->end_simulation_lock);
	cleanup_free(d, msg);
	return (false);
}
