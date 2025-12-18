#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>



typedef struct s_data t_data;

typedef struct s_philo
{
	int		philo_id;
	t_data	*data;
}	t_philo;

typedef struct s_data
{
	int	philo_count;
	int	hunger_endurance;
	int	eat_duration;
	int	sleep_duration;
	int	meal_limit;
	t_philo	*philo;
}	t_data;


//parsing.c
bool	input_validation(int argc, char **argv, t_data *d);
bool 	data_init(t_data *d);

//utils.c
int		parse_number(const char *str, int *error);
int		ft_isspace(char c);
bool	error_msg(char *msg);

#endif