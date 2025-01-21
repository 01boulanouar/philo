/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 04:23:21 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/21 02:18:00 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *error)
{
	printf("%s\n", error);
	return (0);
}

void	print_usage(void)
{
	printf("./philo n_philo time_to_die ");
	printf("time_to_eat time_to_sleep [n_meals]\n");
	return ;
}

int	check_int(int argc, char **argv)
{
	if (!ft_isint(argv[1]))
		return (ft_error("number_of_philosophers must be an int"));
	if (!ft_isint(argv[2]))
		return (ft_error("time_to_die must be an int"));
	if (!ft_isint(argv[3]))
		return (ft_error("time_to_eat must be an int"));
	if (!ft_isint(argv[4]))
		return (ft_error("time_to_sleep must be an int"));
	if (argc == 6 && !ft_isint(argv[5]))
		return (ft_error("number_of_meals must be an int"));
	return (1);
}

int	check_range(int argc, char **argv)
{
	if (ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > 200)
		return (ft_error("number_of_philosophers range is 1 to 200"));
	if (ft_atol(argv[2]) < 60)
		return (ft_error("time_to_die must be 60ms or more"));
	if (ft_atol(argv[3]) < 60)
		return (ft_error("time_to_eat must be 60ms or more"));
	if (ft_atol(argv[4]) < 60)
		return (ft_error("time_to_sleep must be 60ms or more"));
	if (argc == 6 && ft_atol(argv[5]) <= 0)
		return (ft_error("number_of_meals must be 1 or more"));
	return (1);
}

void	init_table(int argc, char **argv, t_table *table)
{
	table->n_philo = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->n_meals = ft_atol(argv[5]);
	else
		table->n_meals = 0;
}
