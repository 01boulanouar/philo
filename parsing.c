/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 04:23:21 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/19 02:29:35 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_usage(void)
{
	printf("./philo n_philo time_to_die ");
	printf("time_to_eat time_to_sleep [n_meals]\n");
	exit(1);
}

void	check_int(int argc, char **argv)
{
	if (!ft_isint(argv[1]))
		ft_error("number_of_philosophers must be an int");
	if (!ft_isint(argv[2]))
		ft_error("time_to_die must be an int");
	if (!ft_isint(argv[3]))
		ft_error("time_to_eat must be an int");
	if (!ft_isint(argv[4]))
		ft_error("time_to_sleep must be an int");
	if (argc == 6 && !ft_isint(argv[5]))
		ft_error("number_of_meals must be an int");
}

void	check_range(int argc, char **argv)
{
	if (ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > 200)
		ft_error("number_of_philosophers range is 1 to 200");
	if (ft_atol(argv[2]) < 60)
		ft_error("time_to_die must be 60ms or more");
	if (ft_atol(argv[3]) < 60)
		ft_error("time_to_eat must be 60ms or more");
	if (ft_atol(argv[4]) < 60)
		ft_error("time_to_sleep must be 60ms or more");
	if (argc == 6 && ft_atol(argv[5]) <= 0)
		ft_error("number_of_meals must be 1 or more");
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

void	handle_args(int argc, char **argv, t_table *table)
{
	if (argc != 5 && argc != 6)
		print_usage();
	check_int(argc, argv);
	check_range(argc, argv);
	init_table(argc, argv, table);
}
