#include "philosophers.h"

void	check_if_dead(t_data *d)
{
	long i;

	i = -1;
	while (++i < d->philo_count)
	{
		if (d->philo[i].meal_eaten == 0)
		{
			if (get_now_time_converter() - d->start_simulation >= d->hunger_endurance)
			{
				pthread_mutex_lock(d->end_simulation_lock);
				d->end_simulation = 1;
				locked_printf(&d->philo[i], "died");
				pthread_mutex_unlock(d->end_simulation_lock);
				return;
			}
		}
		else
		{
			if (get_now_time_converter() - d->philo[i].previous_meal >= d->hunger_endurance)
			{
				pthread_mutex_lock(d->end_simulation_lock);
				d->end_simulation = 1;
				locked_printf(&d->philo[i], "died");
				pthread_mutex_unlock(d->end_simulation_lock);
				return ;
			}
		}

	}
}

void main_monitor(t_data *d)
{
	while (1)
	{
		check_if_dead(d);
		if (d->end_simulation)
			break;
	}
}