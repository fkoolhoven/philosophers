/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:57:28 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/22 16:02:37 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	should_dinner_end(t_data *data)
{
	bool	should_stop;

	pthread_mutex_lock(&data->dinner_end_mutex);
	should_stop = data->dinner_should_end;
	pthread_mutex_unlock(&data->dinner_end_mutex);
	return (should_stop);
}

bool	should_dinner_start(t_data *data)
{
	bool	should_start;

	pthread_mutex_lock(&data->dinner_start_mutex);
	should_start = data->dinner_should_start;
	pthread_mutex_unlock(&data->dinner_start_mutex);
	return (should_start);
}

void	let_dinner_start(t_data *data)
{
	pthread_mutex_lock(&data->dinner_start_mutex);
	data->dinner_should_start = true;
	data->start_time = get_current_time();
	pthread_mutex_unlock(&data->dinner_start_mutex);
}
