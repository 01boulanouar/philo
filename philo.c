/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 04:23:28 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/21 05:10:49 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *context)
{
	t_philo	*philo;

	philo = (t_philo *)context;
	if (philo->id % 2)
		ft_usleep(philo->table->time_to_eat);
	while (1)
	{
		pthread_mutex_lock(&philo->table->forks[philo->right]);
		print("has taken a fork", philo);
		pthread_mutex_lock(&philo->table->forks[philo->left]);
		print("has taken a fork", philo);
		print("is eating", philo);
		pthread_mutex_lock(&philo->table->meal);
		philo->last_meal = get_time();
		philo->n_meals++;
		pthread_mutex_unlock(&philo->table->meal);
		ft_usleep(philo->table->time_to_eat);
		pthread_mutex_unlock(&philo->table->forks[philo->left]);
		pthread_mutex_unlock(&philo->table->forks[philo->right]);
		print("is sleeping", philo);
		ft_usleep(philo->table->time_to_sleep);
		print("is thinking", philo);
	}
	return (NULL);
}

void	create_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	table->start = get_time();
	i = 0;
	while (i < table->n_philo)
	{
		philo = &table->philos[i];
		philo->id = i;
		philo->right = i;
		philo->left = (i + 1) % table->n_philo;
		philo->n_meals = 0;
		philo->table = table;
		philo->last_meal = get_time();
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
	int	n_meals;

	n_philo = 0;
	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_lock(&table->meal);
		n_meals = table->philos[i].n_meals;
		pthread_mutex_unlock(&table->meal);
		if (n_meals >= table->n_meals)
			n_philo++;
		i++;
	}
	return (n_philo == table->n_philo);
}

void	monitor(t_table *table)
{
	int		i;
	time_t	last_meal;

	while (1)
	{
		if (table->n_meals && done_eating(table))
			return ;
		i = 0;
		while (i < table->n_philo)
		{
			pthread_mutex_lock(&table->meal);
			last_meal = table->philos[i].last_meal;
			pthread_mutex_unlock(&table->meal);
			if (get_time() >= last_meal + table->time_to_die)
			{
				pthread_mutex_lock(&table->print);
				printf("%ld %d died\n", get_time() - table->start, i + 1);
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
