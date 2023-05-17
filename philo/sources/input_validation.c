/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:34:48 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/17 17:23:22 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/colors.h"

// check if args are valid numbers

void	print_error_message(char *error_message)
{
	printf(CC_RED CC_BOLD"Error:"CC_OFF" %s\n", error_message);
}

void	prompt_message(void)
{
	printf("./philo "CC_YELLOW"[number_of_philosophers] "
		"[time_to_starve] [time_to_eat] [time_to_sleep] "
		"[number_of_times_each_philosopher_must_eat]\n"CC_OFF""
		"Note: "CC_YELLOW"[number_of_times_each_philosopher_must_eat] "CC_OFF""
		"is an optional arguments; you can also leave it out\n");
	exit(EXIT_FAILURE);
}

void	validate_input(int argc)
{
	if (argc != 5 && argc != 6)
	{
		print_error_message("incorrect number of arguments");
		prompt_message();
		exit(EXIT_FAILURE);
	}
}

void	validate_arguments(t_data *data)
{
	char	*error_message;

	if (data->philosophers_amount < 0)
		error_message = "invalid number_of_philosophers";
	else if (data->time_to_starve < 0)
		error_message = "invalid time_to_starve";
	else if (data->time_to_eat < 0)
		error_message = "invalid time_to_eat";
	else if (data->time_to_sleep < 0)
		error_message = "invalid time_to_sleep";
	else if (data->meals_quota < 0 && data->meals_quota_established == true)
		error_message = "invalid number_of_times_each_philosopher_must_eat";
	else
		return ;
	print_error_message(error_message);
	prompt_message();
}
