/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:17:33 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/10 04:23:08 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h> // for EXIT_FAILURE

int	main(int argc, char *argv[])
{
	t_data	data;
	((void)argv, (void)argc);
	/*	
		First step is to initialize the data structure,
		which will hold all the information about the simulation.
	*/
	if (!init_data(&data, argc, argv))
		return (EXIT_FAILURE);

	/*
		Second step is to initialize the forks structure,
		which will hold all the information about each fork.
	*/
	// if (!init_forks(&data))
	// 	return (EXIT_FAILURE);

	/*
		Third step is to initialize the philo structure,
		which will hold all the information about each philosopher.
	*/
	// if (!init_philo(&philos, &data))
	// 	return (EXIT_FAILURE);

	/*
		Last step is to initialize the simulation.
	*/
	// if (!simulation(&data, &philos))
	// 	return (EXIT_FAILURE);
	destroy(&data, data.philos);
	return (EXIT_SUCCESS);
}
