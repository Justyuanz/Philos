#include "philosophers.h"

/*

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
void	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_forks);
		locked_printf(philo, "has taken the left fork 🍴");
		pthread_mutex_lock(philo->right_forks);
		locked_printf(philo, "has taken the right fork 🍴");
		locked_printf(philo, "is eating 🍝");
		pthread_mutex_unlock(philo->right_forks);
		pthread_mutex_unlock(philo->left_forks);
	}
	else
	{
		pthread_mutex_lock(philo->right_forks);
		locked_printf(philo, "has taken the right fork 🍴");
		pthread_mutex_lock(philo->left_forks);
		locked_printf(philo, "has taken the left fork 🍴");
		locked_printf(philo, "is eating 🍝");
		pthread_mutex_unlock(philo->left_forks);
		pthread_mutex_unlock(philo->right_forks);
	}
}
