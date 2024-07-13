/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:40:53 by ebinjama          #+#    #+#             */
/*   Updated: 2024/07/13 04:57:03 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

size_t	my_gettime(void)
{
	struct timeval	timeofday;

	if (gettimeofday(&timeofday, NULL) == -1)
		return (/*log=GETTIMEOFDAYFAILED*/-1);
	return ((timeofday.tv_sec * 1000) + (timeofday.tv_usec / 1000));
}

void	write_error(const char *msg)
{
	size_t	len;

	len = 0;
	while (msg[len])
		len++;
	write(2, msg, len);
	write(2, "\n", 1);
}
