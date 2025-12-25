#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>


typedef struct s_data t_data;

typedef struct s_philo
{
	long			philo_id;
	long			meal_eaten;
	long			previous_meal;
	t_data			*data;
	pthread_t		thread_id;
	pthread_mutex_t	*left_forks;
	pthread_mutex_t *right_forks;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t *print_lock;
	pthread_mutex_t *end_simulation_lock;
	long			end_simulation;
	long 			start_simulation;
	long			philo_count;
	long			hunger_endurance;
	long			eat_duration;
	long			sleep_duration;
	long			meal_limit;

}	t_data;


//parsing.c
bool	input_validation(int argc, char **argv, t_data *d);

//init.c
bool 	data_init(t_data *d);

//start_threads.c
bool 	create_thread(t_data *d);

//routine.c
void	take_forks(t_philo *philo);
bool	are_eating(t_philo *philo);
void	put_down_forks(t_philo *philo);
bool	precise_usleep(long sleep_duration);
bool    is_dead(t_philo *philo);

// monitor.c
void main_monitor(t_data *d);


//utils.c
void 	locked_printf(t_philo *philo, char *msg);
long	get_now_time_converter(void);

//cleanup.c
bool cleanup_free(t_data *d, char *msg);
bool cleanup_all(t_data *d, char *msg);


#endif