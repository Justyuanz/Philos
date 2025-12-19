#include "philosophers.h"

void locked_printf(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->data->print_lock);
	printf("%d %s\n", philo->philo_id, msg);
	pthread_mutex_unlock(philo->data->print_lock);
}

