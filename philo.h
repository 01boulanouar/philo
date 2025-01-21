/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 04:23:42 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/21 00:56:46 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	time_t			last_meal;
	int				n_meals;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				ended;
	int				n_philo;
	int				n_meals;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	print;

}					t_table;

int					ft_strlen(char *str);
int					ft_isspace(char c);
int					ft_isallspace(char *str);
int					ft_isint(char *str);
long				ft_atol(char *str);
void				handle_args(int argc, char **argv, t_table *table);
void				ft_error(char *error);

void				init_mutex(t_table *table);
void				destroy_mutex(t_table *table);
void				*routine(void *context);
time_t				get_time(t_table *table);
void				ft_usleep(time_t time, t_table *table);
void				print(char *action, t_philo *philo);
#endif