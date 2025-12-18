#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data d;

	if (input_validation(argc, argv, &d))
		data_init(&d);
}