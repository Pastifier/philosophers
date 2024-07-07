/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:40:53 by ebinjama          #+#    #+#             */
/*   Updated: 2024/07/07 17:44:41 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	my_gettime(void)
{
	struct timeval	timeofday;

	if (gettimeofday(&timeofday, NULL) == -1)
		return (/*log=GETTIMEOFDAYFAILED*/-1);
	return ((timeofday.tv_sec / 1000) + (timeofday.tv_usec * 1000));
}
