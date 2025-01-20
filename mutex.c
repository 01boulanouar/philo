/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 02:18:12 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/19 19:24:55 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->print, NULL))
		ft_error("failed to init print mutex");
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			ft_error("failed to create philo thread");
		i++;
	}
}

void	destroy_mutex(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->print);
	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}
