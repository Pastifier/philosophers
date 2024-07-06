#include "philo.h"
#include <stdlib.h>

static bool	init_data(int argc, char *argv[], t_data *data);
static bool	init_philos(int philo_count, t_philo **philos);

int	main(int argc, char *argv[])
{
	t_data	context;
	t_philo	*philos;

	if (init_data(argc, argv, &context))
		return (EXIT_FAILURE);
	// if (init_philos(context.philo_count, &context.philos))
	// 	return (EXIT_FAILURE);
	return (0);
}

static bool	init_data(int argc, char *argv[], t_data *data)
{
	t_eint	fetcher;

	if (argc < 5 || argc > 6)
		return (/*do_log()=WRONG_USAGE*/false);
	fetcher = ft_atoi(argv[1]);
	if (fetcher.error || fetcher.value < 1)
		return (/*do_log()=INVALID_NUMBER*/false);
	data->philo_count = fetcher.value;
	data->dead = false;
	if (gettimeofday(&data->start, NULL) == -1)
		return (/*do_log()=GETTIMEOFDAY_FAILED*/false);
}

static bool	init_philos(int philo_count, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * philo_count);
	if (!*philos)
		return (/*do_log()=MALLOC_FAILED*/false);
	i = 0;
	while (i < philo_count)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].left_fork = i;
		(*philos)[i].right_fork = (i + 1) % philo_count;
		(*philos)[i].eat_count = 0;
		(*philos)[i].last_eat = 0;
	}
	return (true);
}
