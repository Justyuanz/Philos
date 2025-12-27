/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 19:57:55 by jinzhang          #+#    #+#             */
/*   Updated: 2025/12/27 21:06:34 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Any shared state must be read and written under a mutex.

without alternating:
Philosopher 1
lock(left_fork);   // fork 0
lock(right_fork);  // fork 1

Philosopher 2
lock(left_fork);   // fork 1
lock(right_fork);  // fork 0

t=0: Philo 1 locks fork 0
t=1: Philo 2 locks fork 1
t=2: Philo 1 waits for fork 1
t=3: Philo 2 waits for fork 0
*/

// home end   , shift home shift end, ctrl home ctrl end,
// option u or down arrow

bool	simulation_over(t_data *d)
{
	bool	end;

	pthread_mutex_lock(d->end_simulation_lock);
	end = d->end_simulation;
	pthread_mutex_unlock(d->end_simulation_lock);
	return (end);
}

void	precise_usleep(t_philo *philo, long sleep_duration)
{
	long	start_sleep;

	start_sleep = get_now_time_converter();
	while (!simulation_over(philo->data))
	{
		if (get_now_time_converter() - start_sleep >= sleep_duration)
			break ;
		usleep(100);
	}
}

void	are_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->previous_meal = get_now_time_converter();
	philo->meal_eaten += 1;
	locked_printf(philo, "is eating");
	pthread_mutex_unlock(philo->meal_lock);
	precise_usleep(philo, philo->data->eat_duration);
}

void	put_down_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_forks);
		pthread_mutex_unlock(philo->left_forks);
	}
	else
	{
		pthread_mutex_unlock(philo->left_forks);
		pthread_mutex_unlock(philo->right_forks);
	}
	return ;
}

void	take_forks(t_philo *philo)
{
	usleep(1000);// breaks perfect symmetry at the moment philosophers try to grab forks.
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_forks);
		locked_printf(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_forks);
		locked_printf(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_forks);
		locked_printf(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_forks);
		locked_printf(philo, "has taken a fork");
	}
	return ;
}
