/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:52:52 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/19 15:26:19 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(t_table *table)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
		- table->start);
}

void	print(char *action, t_philo *philo)
{
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
