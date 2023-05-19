/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:38:55 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/19 14:16:41 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	free_all_allocated_memory(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->forks_amount)
	{
		free(data->fork_mutexes[i]);
		i++;
	}
	free(data->fork_mutexes);
	free(data);
	free(philo);
}

static void	destroy_all_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->message_mutex);
	i = 0;
	while (i < data->forks_amount)
	{
		pthread_mutex_destroy(data->fork_mutexes[i]);
		i++;
	}
}

void	free_memory(t_philo **philo, t_data *data)
{
	destroy_all_mutexes(data);
	free_all_allocated_memory(philo, data);
}

void	join_philosopher_threads(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philosophers_amount)
	{
		pthread_join((*philo[i]).thread, NULL);
		i++;
	}
}
