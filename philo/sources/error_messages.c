/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:42:51 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/06/13 14:36:30 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/colors.h"

void	print_error_message(char *message)
{
	printf(CC_RED CC_BOLD"Error: "CC_OFF"%s\n", message);
}

void	*print_error_message_and_return_null(char *message)
{
	print_error_message(message);
	return (NULL);
}

static void	print_input_instructions(void)
{
	printf("./philo "CC_YELLOW"[number_of_philosophers] "
		"[time_to_starve] [time_to_eat] [time_to_sleep] "
		"[number_of_times_each_philosopher_must_eat]\n"CC_OFF""
		"Note: "CC_YELLOW"[number_of_times_each_philosopher_must_eat] "CC_OFF""
		"is an optional arguments; you can also leave it out\n");
}

void	print_input_error_message(char *error_message)
{
	printf(CC_RED CC_BOLD"Error:"CC_OFF" %s\n", error_message);
	print_input_instructions();
}
