/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:41:29 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/10 12:22:11 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	let_time_pass(long long time_to_sleep, t_data *data)
{
	long long	start_time;

	start_time = get_current_time();
	while (get_current_time() - start_time < time_to_sleep
		&& !data->philo_starved)
		usleep(100);
}

long long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	get_simulation_time(t_data *data)
{
	return (get_current_time() - data->start_time);
}
