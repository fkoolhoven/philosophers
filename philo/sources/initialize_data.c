/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:59 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/25 19:47:10 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	destroy_fork_mutexes_in_case_of_error(t_data *data, int i)
{
	i--;
	while (i >= 0)
	{
		pthread_mutex_destroy(data->fork_mutexes[i]);
		i--;
	}
}

static void	*initialize_forks(t_data *data)
{
	int	i;

	data->fork_mutexes = malloc(data->forks_amount * sizeof(pthread_mutex_t *));
	if (data->fork_mutexes == NULL)
		return (print_error_message_and_return_null("malloc fail"));
	i = 0;
	while (i < data->forks_amount)
	{
		data->fork_mutexes[i] = malloc(sizeof(pthread_mutex_t));
		if (data->fork_mutexes[i] == NULL)
		{
			destroy_fork_mutexes_in_case_of_error(data, i);
			return (print_error_message_and_return_null("malloc fail"));
		}
		if (pthread_mutex_init(data->fork_mutexes[i], NULL) != 0)
		{
			destroy_fork_mutexes_in_case_of_error(data, i);
			return (print_error_message_and_return_null("mutex init fail"));
		}
		i++;
	}
	return (data);
}

void	*initialize_mutexes_in_data_struct(t_data *data)
{
	if (!initialize_forks(data))
		return (NULL);
	if (pthread_mutex_init(&data->dinner_start_mutex, NULL) != 0)
		return (print_error_message_and_return_null("mutex init fail"));
	if (pthread_mutex_init(&data->message_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->dinner_start_mutex);
		return (print_error_message_and_return_null("mutex init fail"));
	}
	if (pthread_mutex_init(&data->dinner_end_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->dinner_start_mutex);
		pthread_mutex_destroy(&data->message_mutex);
		return (print_error_message_and_return_null("mutex init fail"));
	}
	return (data);
}

t_data	*store_arguments_in_data_struct(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (print_error_message_and_return_null("malloc fail"));
	data->dinner_should_start = false;
	data->dinner_should_end = false;
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
