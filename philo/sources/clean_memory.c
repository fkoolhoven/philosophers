/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:38:55 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/29 16:59:00 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	free_all_allocated_memory(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	if (data->fork_mutexes)
	{
		while (i < data->forks_amount)
		{
			if (data->fork_mutexes[i])
				free(data->fork_mutexes[i]);
			i++;
		}
		free(data->fork_mutexes);
	}
	if (data)
		free(data);
	if (philo)
		free(philo);
}

static void	destroy_all_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->dinner_start_mutex);
	pthread_mutex_destroy(&data->message_mutex);
	pthread_mutex_destroy(&data->dinner_end_mutex);
	i = 0;
	while (i < data->forks_amount)
	{
		pthread_mutex_destroy(data->fork_mutexes[i]);
		i++;
	}
}

void	free_memory(t_philo **philo, t_data *data)
{
	if (data->initialization_failed)
		destroy_all_mutexes(data);
	free_all_allocated_memory(philo, data);
}

void	join_philosopher_threads(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->initialized_threads)
	{
		pthread_join((*philo[i]).thread, NULL);
		i++;
	}
}
