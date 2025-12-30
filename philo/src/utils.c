/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 19:58:04 by jinzhang          #+#    #+#             */
/*   Updated: 2025/12/30 17:48:33 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_now_time_converter(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void	locked_printf(t_philo *philo, char *msg)
{
	long	now;
	long	timelap;

    pthread_mutex_lock(philo->data->end_simulation_lock);
    if (philo->data->end_simulation)
    {
        pthread_mutex_unlock(philo->data->end_simulation_lock);
        return;
    }
    pthread_mutex_unlock(philo->data->end_simulation_lock);
	pthread_mutex_lock(philo->data->print_lock);
	now = get_now_time_converter();
	timelap = now - philo->data->start_simulation;
	printf("%ld %ld %s\n", timelap, philo->philo_id, msg);
	pthread_mutex_unlock(philo->data->print_lock);
}
