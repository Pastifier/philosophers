/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:17:33 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/13 04:50:21 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h> // for EXIT_FAILURE

int	main(int argc, char *argv[])
{
	t_data	data;

	data = (t_data){0};
	if (!init_data(&data, argc, argv))
		return (EXIT_FAILURE);
	if (!start_sim(&data))
		return (EXIT_FAILURE);
	destroy(&data, data.philos);
	return (EXIT_SUCCESS);
}
