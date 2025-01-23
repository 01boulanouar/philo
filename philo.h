/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboulan <moboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 04:23:42 by moboulan          #+#    #+#             */
/*   Updated: 2025/01/23 22:02:35 by moboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	time_t			last_meal;
	int				n_meals;
	int				right;
	int				left;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				n_philo;
	int				n_meals;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	print;
	pthread_mutex_t	meal;
}					t_table;

int					ft_strlen(char *str);
int					ft_isspace(char c);
int					ft_isallspace(char *str);
int					ft_isint(char *str);
long				ft_atol(char *str);
int					ft_error(char *error);
void				print_usage(void);
int					check_int(int argc, char **argv);
int					check_range(int argc, char **argv);
void				init_table(int argc, char **argv, t_table *table);

int					philo_dead(t_table *table);
void				init_mutex(t_table *table);
void				destroy_mutex(t_table *table);
void				*routine(void *context);
time_t				get_time(void);
void				print(char *action, t_philo *philo);
void				ft_usleep(time_t time);
#endif