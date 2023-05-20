/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:29:42 by dofranci          #+#    #+#             */
/*   Updated: 2023/05/18 22:32:17 by dofranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/time.h>

# define MAXINT 2147483647

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_time
{
	long int	to_birth;
	long int	to_die;
	long int	to_eat;
	long int	to_sleep;
	long int	last_meal;
}	t_time;

typedef struct s_philo
{
	int				order;
	int				nop;
	int				id;
    int				dead;
    int				meals;
	int				max_meals;
	pthread_t		tid;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_time	*time; 
}   t_philo;

typedef struct s_data
{
	t_philo			**philo;
	pthread_mutex_t	*forks;
	pthread_t		tid_monitor;
	int				nop;
}	t_data;

int			ft_atoi(const char *str);
int			validate_args(int argc, char *argv[]);
void		init_data(int argc, char *argv[], t_data *data);
void		init_philos(t_data *data);
long int	timestamp(long int init_time);
void		print_action(long int time, t_philo *philo, char *str);
void eat(t_philo *philo);
void thinking(t_philo *philo);
void take_forks(t_philo *philo);
void ft_sleep(t_philo *philo);

#endif