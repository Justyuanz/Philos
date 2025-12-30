/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 19:57:47 by jinzhang          #+#    #+#             */
/*   Updated: 2025/12/30 18:00:46 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	all_meals_done(t_data *d)
{
	long	i;
	int		meal;
	bool	all_ate;

	i = -1;
	all_ate = false;
	while (++i < d->philo_count)
	{
		pthread_mutex_lock(d->philo[i].meal_lock);
		meal = d->philo[i].meal_eaten;
		pthread_mutex_unlock(d->philo[i].meal_lock);
		if (meal < d->meal_limit)
			return (all_ate);
	}
	all_ate = true;
	pthread_mutex_lock(d->end_simulation_lock);
	d->end_simulation = 1;
	pthread_mutex_unlock(d->end_simulation_lock);
	return (all_ate);
}

void	death_print(t_data *d, long i)
{
	d->end_simulation = 1;
	pthread_mutex_lock(d->print_lock);
	printf("%ld %ld died\n", get_now_time_converter() - d->start_simulation,
		d->philo[i].philo_id);
	pthread_mutex_unlock(d->print_lock);
}

static void	check_if_dead(t_data *d)
{
	long	i;
	long	previous_meal;
	int		meal;
	long	now;

	i = -1;
	while (++i < d->philo_count)
	{
		pthread_mutex_lock(d->philo[i].meal_lock);
		previous_meal = d->philo[i].previous_meal;
		meal = d->philo[i].meal_eaten;
		pthread_mutex_unlock(d->philo[i].meal_lock);
		if (d->meal_limit > 0 && meal >= d->meal_limit)
			continue ;
		now = get_now_time_converter();
		if (now - previous_meal >= d->hunger_endurance)
		{
			pthread_mutex_lock(d->end_simulation_lock);
			if (!d->end_simulation)
				death_print(d, i);
			pthread_mutex_unlock(d->end_simulation_lock);
			return ;
		}
	}
}

void	main_monitor(t_data *d)
{
	bool	meal_limit_done;

	meal_limit_done = false;
	while (1)
	{
		usleep(1000);
		if (d->meal_limit > 0)
			meal_limit_done = all_meals_done(d);
		if (simulation_over(d))
			break ;
		if (!meal_limit_done)
			check_if_dead(d);
		if (simulation_over(d))
			break ;
	}
}
