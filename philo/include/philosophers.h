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
	int				philo_id;
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
	int				philo_count;
	int				hunger_endurance;
	int				eat_duration;
	int				sleep_duration;
	int				meal_limit;

}	t_data;


//parsing.c
bool	input_validation(int argc, char **argv, t_data *d);

//init.c
bool 	data_init(t_data *d);

//start_threads.c
bool 	create_thread(t_data *d);

//routine.c
void	take_forks(t_philo *philo);

//utils.c
void 	locked_printf(t_philo *philo, char *msg);
void	get_time_converter(void);

//cleanup.c
bool cleanup_free(t_data *d, char *msg);
bool cleanup_all(t_data *d, char *msg);


#endif