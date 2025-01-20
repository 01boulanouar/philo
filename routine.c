/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:00:17 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/19 19:32:23 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->id]);
	print("has taken a fork", philo);
	pthread_mutex_lock(&philo->table->forks[(philo->id + 1)
		% philo->table->n_philo]);
	print("has taken a fork", philo);
	print("is eating", philo);
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(&philo->table->forks[(philo->id + 1)
		% philo->table->n_philo]);
	pthread_mutex_unlock(&philo->table->forks[philo->id]);
	philo->last_meal = get_time(philo->table);
	philo->n_meals++;
}

void	philo_sleep(t_philo *philo)
{
	print("is sleeping", philo);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

void	philo_think(t_philo *philo)
{
	print("is thinking", philo);
}

void	*routine(void *context)
{
	t_philo	*philo;

	philo = (t_philo *)context;
	if (philo->id % 2)
		ft_usleep(philo->table->time_to_eat, philo->table);
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
