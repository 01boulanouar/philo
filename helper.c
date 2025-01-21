/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:52:52 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/21 01:08:22 by moboulan         ###   ########.fr       */
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

time_t	get_time(t_table *table)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - table->start);
}

void	print(char *action, t_philo *philo)
{
	if (philo->table->ended)
		return ;
	pthread_mutex_lock(&philo->table->print);
	printf("%ld %d %s\n", get_time(philo->table), philo->id + 1, action);
	pthread_mutex_unlock(&philo->table->print);
}

void	ft_usleep(time_t time, t_table *table)
{
	time_t	start;

	start = get_time(table);
	while (get_time(table) < start + time)
		usleep(500);
}
