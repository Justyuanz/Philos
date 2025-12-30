/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 19:57:55 by jinzhang          #+#    #+#             */
/*   Updated: 2025/12/30 17:54:04 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

bool	are_eating(t_philo *philo)
{
	if (simulation_over(philo->data))
    	return (false);
	pthread_mutex_lock(philo->meal_lock);
	philo->previous_meal = get_now_time_converter();
	philo->meal_eaten += 1;
	locked_printf(philo, "is eating");
	pthread_mutex_unlock(philo->meal_lock);
	precise_usleep(philo, philo->data->eat_duration);
	return (true);
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

bool	take_forks(t_philo *philo)
{
	if (simulation_over(philo->data))
    	return (false);
	usleep(1000);
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
	return (true);
}
