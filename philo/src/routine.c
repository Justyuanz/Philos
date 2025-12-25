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

// home end   , shift home shift end, ctrl home ctrl end,  option u or down arrow

bool	precise_usleep(long sleep_duration)
{
	long	start_sleep;

	start_sleep = get_now_time_converter();
	while (1)
	{
		if (get_now_time_converter() - start_sleep >= sleep_duration)
			break;
		usleep(100);
	}
	return (true);
}

bool	are_eating(t_philo *philo)
{
	philo->previous_meal = get_now_time_converter();
	philo->meal_eaten += 1;
	locked_printf(philo, "is eating");
	precise_usleep (philo->data->eat_duration);
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

void	take_forks(t_philo *philo)
{
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
