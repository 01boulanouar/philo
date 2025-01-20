/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 04:23:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/21 00:40:11 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	table->start = get_time(table);
	i = 0;
	while (i < table->n_philo)
	{
		philo = &table->philos[i];
		philo->id = i;
		philo->n_meals = 0;
		philo->table = table;
		philo->last_meal = get_time(philo->table);
		if (pthread_create(&philo->thread, NULL, routine, philo))
			ft_error("failed to create philo thread");
		if (pthread_detach(table->philos[i].thread))
			ft_error("failed to detach philo thread");
		i++;
	}
}

int	done_eating(t_table *table)
{
	int	i;
	int	n_philo;

	n_philo = 0;
	i = 0;
	while (i < table->n_philo)
	{
		if (table->philos[i].n_meals >= table->n_meals)
			n_philo++;
		i++;
	}
	return (n_philo == table->n_philo);
}

void	monitor(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->n_philo)
		{
			if (table->n_meals && done_eating(table))
			{
				destroy_mutex(table);
				exit(0);
			}
			if (get_time(table)
				- table->philos[i].last_meal >= table->time_to_die)
			{
				pthread_mutex_lock(&table->print);
				printf("%ld %d died\n", get_time(table), i + 1);
				destroy_mutex(table);
				exit(0);
			}
			usleep(50);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	handle_args(argc, argv, &table);
	init_mutex(&table);
	create_philos(&table);
	monitor(&table);
	return (0);
}
