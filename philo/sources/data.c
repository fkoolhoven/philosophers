/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:59 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/08 15:46:26 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_data	*create_forks(t_data *data)
{
	int	i;

	data->forks = malloc(data->nbr_of_forks * sizeof(int *));
	if (data->forks == NULL)
		error_message_exit("Malloc fail");
	data->fork_mutexes = malloc(data->nbr_of_forks * sizeof(pthread_mutex_t *));
	if (data->fork_mutexes == NULL)
		error_message_exit("Malloc fail");
	i = 0;
	while (i < data->nbr_of_forks)
	{
		data->forks[i] = malloc(sizeof(int));
		if (data->forks[i] == NULL)
			error_message_exit("Malloc fail");
		data->fork_mutexes[i] = malloc(sizeof(pthread_mutex_t));
		if (data->fork_mutexes[i] == NULL)
			error_message_exit("Malloc fail");
		*data->forks[i] = AVAILABLE;
		pthread_mutex_init(data->fork_mutexes[i], NULL);
		i++;
	}
	return (data);
}

t_data	*store_data_in_struct(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		error_message_exit("Malloc fail");
	data->nbr_of_philosophers = ft_atoi(argv[1]);
	data->nbr_of_forks = data->nbr_of_philosophers;
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	create_forks(data);
	pthread_mutex_init(&data->message_mutex, NULL);
	return (data);
}
