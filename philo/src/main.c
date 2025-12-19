#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data d;

	if (!input_validation(argc, argv, &d))
		return (EXIT_FAILURE);
	if (!data_init(&d))
		return (cleanup_all(&d, "data init error"));
	if (!create_thread(&d))
		return (cleanup_all(&d, "thread error\n"));
	get_time_converter();
	usleep(50000000);
	get_time_converter();
	cleanup_all(&d, NULL);
}