/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:26:03 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/17 17:10:59 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' \
	|| c == '\f' || c == '\r')
		return (true);
	return (false);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	minus;

	i = 0;
	nbr = 0;
	minus = 1;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		return (-42);
	return (nbr * minus);
}

void	error_message_exit(char *message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}
