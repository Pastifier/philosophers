/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:54:29 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/10 05:58:22 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

static bool	init_philo_attr(t_philo *const *philos, t_data *context,
				char *argv[], int i);
static bool	init_philos(t_data *context, int argc, char *argv[]);
static bool	init_forks(t_data *context, int argc, char *argv[]);

bool	init_data(t_data *context, int argc, char *argv[])
{
	t_eint	fetcher;

	if (argc < 5 || argc > 6)
		return (write_error(WRONG _USAGE), false);
	fetcher = ft_atoi(argv[1]);
	if (fetcher.error || fetcher.value < 0)
		return (write_error("Invalid number of philosophers!"), false);
	context->philo_count = fetcher.value;
	context->philos = malloc(sizeof(t_philo) * context->philo_count);
	if (!context->philos)
		return (write_error(MALLOC_FAILED "for philosophers!"), false);
	context->done_eating = false;
	context->death_flag = -1;
	context->start_time = my_gettime();
	if (pthread_mutex_init(&context->print_mutex, NULL) != 0
		|| pthread_mutex_init(&context->death_mutex, NULL) != 0
		|| pthread_mutex_init(&context->meal_mutex, NULL) != 0)
	{
		mutex_massacre(context, context->philo_count, STATE_ONLY);
		return (write_error(MUTEX_INIT_FAILED), false);
	}
	return (init_forks(context, argc, argv));
}

bool	init_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->context->philo_count)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]))
		{
			destroy(philos->context, philos);
			return (write_error(THREAD_FAILED), false);
		}
		i++;
	}
	return (true);
}

static bool	init_philo_attr(t_philo *const *philos, t_data *context,
				char *argv[], int i)
{
	t_eint	fetcher;
	bool	status;

	status = true;
	(*philos)[i] = (t_philo){0};
	(*philos)[i].id = i + 1;
	(*philos)[i].context = context;
	fetcher = ft_atoi(argv[2]);
	if (fetcher.error || fetcher.value < 0)
		(write_error("Time to die: "INVALID_VALUE), status = false);
	(*philos)[i].time_to_die = fetcher.value;
	fetcher = ft_atoi(argv[3]);
	if (fetcher.error || fetcher.value < 0)
		(write_error("Time to eat: "INVALID_VALUE), status = false);
	(*philos)[i].time_to_eat = fetcher.value;
	fetcher = ft_atoi(argv[4]);
	if (fetcher.error || fetcher.value < 0)
		(write_error("Time to sleep: "INVALID_VALUE), status = false);
	(*philos)[i].time_to_sleep = fetcher.value;
	(*philos)[i].left_mutex = &context->forks[i].mutex;
	(*philos)[i].right_mutex
		= &context->forks[(i + 1) % context->philo_count].mutex;
	(*philos)[i].last_eat = context->start_time;
	return (status);
}

static bool	init_philos(t_data *context, int argc, char *argv[])
{
	int	i;

	i = 0;
	while (i < context->philo_count)
	{
		if (!init_philo_attr(&context->philos, context, argv, i))
		{
			destroy(context, context->philos);
			return (false);
		}
		if (argc == 6)
		{
			context->philos[i].eat_count = ft_atoi(argv[5]).value;
			if (context->philos[i].eat_count < 0 || ft_atoi(argv[5]).error)
			{
				destroy(context, context->philos);
				return (write_error("Invalid number of meals!"), false);
			}
		}
		else
			context->philos[i].eat_count = -1;
		i++;
	}
	return (true);
}

static bool	init_forks(t_data *context, int argc, char *argv[])
{
	int	i;

	i = 0;
	context->forks = malloc(sizeof(t_fork) * context->philo_count);
	if (!context->forks)
		return (write_error(MALLOC_FAILED "for fork!"), false);
	while (i < context->philo_count)
	{
		if (pthread_mutex_init(&context->forks[i].mutex, NULL) != 0)
		{
			mutex_massacre(context, i + 1, ALL_MUTEXES);
			return (write_error(MUTEX_INIT_FAILED), false);
		}
		context->forks[i].last_user_id = 0;
		context->forks[i].is_taken = false;
		i++;
	}
	return (init_philos(context, argc, argv));
}
