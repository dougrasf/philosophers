/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:29:42 by dofranci          #+#    #+#             */
/*   Updated: 2023/05/25 20:21:35 by dofranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include	<pthread.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<sys/time.h>

# define MAXINT 2147483647

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_time
{
	long int	birth;
	long int	die;
	long int	eat;
	long int	sleep;
	long int	last_meal;
}	t_time;

typedef struct s_philo
{
	int				nop;
	int				id;
	int				dead;
	int				meals;
	int				max_meals;
	pthread_t		tid;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_time			*time;
}	t_philo;

typedef struct s_data
{
	t_philo			**philo;
	pthread_mutex_t	*forks;
	pthread_t		tid_monitor;
	int				nop;
}	t_data;

int			ft_atoi(const char *str);
int			validate_args(int argc, char *argv[]);
int			one_philo(char *argv[]);
void		init_data(int argc, char *argv[], t_data *data);
void		init_philos(t_data *data);
void		print_action(long int time, t_philo *philo, char *str);
void		eat(t_philo *philo);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		ft_sleep(t_philo *philo);
long int	timestamp(long int init_time);

#endif
