#include "philo.h"
#include <stdlib.h>
#include <string.h>

static bool	init_data(int argc, char *argv[], t_data *context);
//static bool	init_philos(int philo_count, t_philo **philos, t_data *context,
//				char *argv[]);

int	main(int argc, char *argv[])
{
	t_data	context;
	//t_philo	*philos;

	context = (t_data){0};
	if (init_data(argc, argv, &context))
		return (EXIT_FAILURE);
	context.start_time = my_gettime();
	if (context.start_time == -1)
		return (write_error(GETTIMEOFDAY_FAILED), EXIT_FAILURE);
	//if (init_philos(context.philo_count, &philos, &context, argv))
	//	return (EXIT_FAILURE);
	// if (start_sim(&context, philos))
	//	return (EXIT_FAILURE);
	return (0);
}

static bool	init_data(int argc, char *argv[], t_data *data)
{
	t_eint	fetcher;
	int		i;

	if (argc < 5 || argc > 6)
		return (write_error(WRONG _USAGE), false);
	fetcher = ft_atoi(argv[1]);
	if (fetcher.error || fetcher.value < 1)
		return (write_error(INVALID_NUMBER), false);
	data->philo_count = fetcher.value;
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (write_error(MUTEX_INIT_FAILED), false);
	data->forks = malloc(sizeof(t_fork) * data->philo_count);
	if (!data->forks)
		return (write_error(MALLOC_FAILED), false);
	memset(data->forks, 0, sizeof(t_fork) * data->philo_count);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i].mutex, NULL))
			return (write_error(MUTEX_INIT_FAILED), false);
		i++;
	}
	data->curr_timestamp = 0;
	return (true);
}
