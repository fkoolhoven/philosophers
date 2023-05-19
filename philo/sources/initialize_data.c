/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:59 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/19 14:03:44 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	initialize_forks(t_data *data)
{
	int	i;

	data->fork_mutexes = malloc(data->forks_amount * sizeof(pthread_mutex_t *));
	if (data->fork_mutexes == NULL)
		error_message_exit("malloc fail");
	i = 0;
	while (i < data->forks_amount)
	{
		data->fork_mutexes[i] = malloc(sizeof(pthread_mutex_t));
		if (data->fork_mutexes[i] == NULL)
			error_message_exit("malloc fail");
		pthread_mutex_init(data->fork_mutexes[i], NULL);
		i++;
	}
}

void	initialize_mutexes(t_data *data)
{
	initialize_forks(data);
	pthread_mutex_init(&data->message_mutex, NULL);
}

t_data	*store_arguments_in_data_struct(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		error_message_exit("malloc fail");
	data->dinner_should_stop = false;
	data->philosophers_amount = ft_atol(argv[1]);
	data->forks_amount = data->philosophers_amount;
	data->time_to_starve = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		data->meals_quota = ft_atol(argv[5]);
		data->meals_quota_established = true;
	}
	else
	{
		data->meals_quota = -42;
		data->meals_quota_established = false;
	}
	return (data);
}
