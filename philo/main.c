/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:17:33 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/10 05:47:10 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h> // for EXIT_FAILURE

int	main(int argc, char *argv[])
{
	t_data	data;
	/*	
		First step is to initialize the data structure,
		which will hold all the information about the simulation.
	
	
		Second step is to initialize the forks structure,
		which will hold all the information about each fork.
	

	
		Third step is to initialize the philo structure,
		which will hold all the information about each philosopher.
	*/
	data = (t_data){0};
	if (!init_data(&data, argc, argv))
		return (EXIT_FAILURE);

	/*
		Last step is to initialize the simulation.
	*/
	if (!start_sim(&data))
		return (EXIT_FAILURE);
	destroy(&data, data.philos);
	return (EXIT_SUCCESS);
}
