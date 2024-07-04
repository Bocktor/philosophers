/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/03/13 15:44:10 by marvin            #+#    #+#             */
/*   Updated: 2024/03/13 15:44:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_mutix
{
	pthread_mutex_t *forks;
	pthread_mutex_t l_fork_locker;
	pthread_mutex_t r_fork_locker;
	pthread_mutex_t write_locker;
	pthread_mutex_t dead_locker;
	pthread_mutex_t meal_locker;

} t_mutix;

typedef struct s_args
{
	pthread_t philosophers;
	int num_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int diet;
	int until_full;
	int fasting;
	int n_philo;
	int l_fork;
	int r_fork;
	int flatware;
	int dead_flag;
	int start;
	t_mutix locker;
	
} t_args;

t_args	arguments(int argc, char **argv, int n_ph, t_mutix locked);
t_args	flatware(t_args philo, t_mutix locked);
void	philosophers(int argc, char **argv);
void	*life(void *add);
int	eating(t_args *philo);
int	ft_atoi(char *str);
size_t	get_current_time(void);
int	ft_usleep(size_t milliseconds);

#endif
