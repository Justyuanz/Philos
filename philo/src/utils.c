#include "philosophers.h"


void	get_time_converter(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	printf("time_t      tv_sec:%ld  suseconds_t tv_usec: %ld \n", tv.tv_sec, tv.tv_usec);
}

void locked_printf(t_philo *philo, char *msg)
{

	pthread_mutex_lock(philo->data->print_lock);
	printf("%d %s\n", philo->philo_id, msg);
	pthread_mutex_unlock(philo->data->print_lock);
}

