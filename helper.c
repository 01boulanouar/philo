/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:52:52 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/23 03:02:18 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->meal, NULL))
		ft_error("failed to init meal mutex");
	if (pthread_mutex_init(&table->print, NULL))
		ft_error("failed to init print mutex");
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			ft_error("failed to create fork mutex");
		i++;
	}
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->meal);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	print(char *action, t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->meal);
	if (table->end)
	{
		pthread_mutex_unlock(&table->meal);
		return ;
	}
	pthread_mutex_unlock(&table->meal);
	pthread_mutex_lock(&table->print);
	printf("%ld %d %s\n", get_time() - table->start, philo->id + 1, action);
	pthread_mutex_unlock(&table->print);
}

void	ft_usleep(time_t time)
{
	time_t	start;

	start = get_time();
	while (get_time() < start + time)
		usleep(500);
}
