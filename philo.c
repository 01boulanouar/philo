/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 04:23:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/21 02:13:27 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *context)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)context;
	table = philo->table;
	if (philo->id % 2)
		ft_usleep(table->time_to_eat, table);
	while (1)
	{
		pthread_mutex_lock(&table->forks[philo->id]);
		print("has taken a fork", philo);
		pthread_mutex_lock(&table->forks[(philo->id + 1) % table->n_philo]);
		print("has taken a fork", philo);
		print("is eating", philo);
		ft_usleep(table->time_to_eat, table);
		pthread_mutex_unlock(&table->forks[(philo->id + 1) % table->n_philo]);
		pthread_mutex_unlock(&table->forks[philo->id]);
		philo->last_meal = get_time(table);
		philo->n_meals++;
		print("is sleeping", philo);
		ft_usleep(table->time_to_sleep, table);
		print("is thinking", philo);
	}
	return (NULL);
}

void	create_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	table->ended = 0;
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
		if (table->n_meals && done_eating(table))
			return ;
		while (i < table->n_philo)
		{
			if (get_time(table)
				- table->philos[i].last_meal >= table->time_to_die)
			{
				table->ended = 1;
				pthread_mutex_lock(&table->print);
				printf("%ld %d died\n", get_time(table), i + 1);
				return ;
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
	{
		print_usage();
		return (0);
	}
	if (!check_int(argc, argv))
		return (0);
	if (!check_range(argc, argv))
		return (0);
	init_table(argc, argv, &table);
	init_mutex(&table);
	create_philos(&table);
	monitor(&table);
	destroy_mutex(&table);
	return (0);
}
