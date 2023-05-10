/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:59 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/10 13:47:43 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_data	*initialize_forks(t_data *data)
{
	int	i;

	data->fork_mutexes = malloc(data->forks_amount * sizeof(pthread_mutex_t *));
	if (data->fork_mutexes == NULL)
		error_message_exit("Malloc fail");
	i = 0;
	while (i < data->forks_amount)
	{
		data->fork_mutexes[i] = malloc(sizeof(pthread_mutex_t));
		if (data->fork_mutexes[i] == NULL)
			error_message_exit("Malloc fail");
		pthread_mutex_init(data->fork_mutexes[i], NULL);
		i++;
	}
	return (data);
}

t_data	*initialize_data_struct(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		error_message_exit("Malloc fail");
	data->philosophers_amount = ft_atoi(argv[1]);
	data->forks_amount = data->philosophers_amount;
	data->time_to_starve = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_quota = ft_atoi(argv[5]);
	else
		data->meals_quota = -1;
	initialize_forks(data);
	pthread_mutex_init(&data->message_mutex, NULL);
	data->start_time = get_current_time();
	data->philo_starved = 0;
	return (data);
}
