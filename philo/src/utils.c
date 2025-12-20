#include "philosophers.h"

/*
Obtains the current time, expressed as seconds and microseconds
since 00:00:00 Coordinated Universal Time (UTC), January 1, 1970,
and stores it in the timeval structure
seconds → milliseconds	sec * 1000
seconds → microseconds	sec * 1000000
milliseconds → seconds	ms / 1000
milliseconds → microseconds	ms * 1000
microseconds → milliseconds	us / 1000
microseconds → seconds	us / 1000000
*/

/*
1000      // int
1000L     // long
1000LL    // long long
Without L suffix, the multiplication can happen in int
with L, Now the compiler sees: long * long, result = long, no overflow (if value fits in long)
*/
long	get_time_converter(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL); //-1 for failure
	return(tv.tv_sec * 1000L + tv.tv_usec / 1000L); //overflow?
}

void locked_printf(t_philo *philo, char *msg)
{
	long now;
	long timelap;

	pthread_mutex_lock(philo->data->print_lock);
	now = get_time_converter(); //might return -1
	timelap = now - philo->data->start_simulation;
	printf("%ld %d %s\n", timelap, philo->philo_id, msg);
	pthread_mutex_unlock(philo->data->print_lock);
}

