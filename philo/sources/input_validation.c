/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:34:48 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/19 14:45:46 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	input_validation(t_data *data)
{
	char	*error_message;

	if (data->philosophers_amount <= 0)
		error_message = "invalid number_of_philosophers";
	else if (data->time_to_starve < 0)
		error_message = "invalid time_to_starve";
	else if (data->time_to_eat <= 0)
		error_message = "invalid time_to_eat";
	else if (data->time_to_sleep <= 0)
		error_message = "invalid time_to_sleep";
	else if (data->meals_quota_established == true && data->meals_quota <= 0)
		error_message = "invalid number_of_times_each_philosopher_must_eat";
	else
		return ;
	print_input_error_message_and_exit(error_message);
}
