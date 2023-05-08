/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:34:48 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/08 12:44:49 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// check if args are valid numbers
void	validate_input(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error message args\n");
		printf("[number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]\n");
		exit (EXIT_FAILURE);
	}
}
