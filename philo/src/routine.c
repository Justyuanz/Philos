#include "philosophers.h"

/*
	philo 1 locked fork 0
	philo 2 lo
*/

bool	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->left_forks) != 0)
			return (false);
		locked_printf(philo, "has taken the left fork");
		if (pthread_mutex_lock(philo->right_forks) != 0)
			return (false);
		locked_printf(philo, "has taken the right fork");
		locked_printf(philo, "is eating");
		if (pthread_mutex_unlock(philo->right_forks) != 0)
			return (false);
		if (pthread_mutex_unlock(philo->left_forks) != 0)
			return (false);
	}
	else
	{
		if (pthread_mutex_lock(philo->right_forks) != 0)
			return (false); //cleanup
		locked_printf(philo, "has taken the right fork");
		if (pthread_mutex_lock(philo->left_forks) != 0)
			return (false); //cleanup
		locked_printf(philo, "has taken the left fork");
		locked_printf(philo, "is eating");
		if (pthread_mutex_unlock(philo->left_forks) != 0)
			return (false); //clean up
		if (pthread_mutex_unlock(philo->right_forks) != 0)
			return (false); //clean up
	}
	return (true);
}
