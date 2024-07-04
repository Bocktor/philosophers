/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/03/13 15:44:07 by marvin            #+#    #+#             */
/*   Updated: 2024/03/13 15:44:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


t_args	arguments(int argc, char **argv, int n_ph, t_mutix locked)
{
	t_args philo;
	int i;

	i = 0;
	philo.n_philo = n_ph;
	philo.until_full = 0;
	philo.num_of_philo = ft_atoi(argv[1]);
	philo.num_of_philo = ft_atoi(argv[1]);
	philo.time_to_die = ft_atoi(argv[2]);
	philo.time_to_eat = ft_atoi(argv[3]);
	philo.time_to_sleep = ft_atoi(argv[4]);
	philo.start = get_current_time();
	if (argc == 6)
		philo.diet = atoi(argv[5]);
	else
		philo.diet = 799;
	philo.locker = locked;
	philo = flatware(philo, locked);

	return (philo);
}

int	philosopher_dead(t_args *philo, size_t time_to_die)
{
	pthread_mutex_lock(&philo->locker.meal_locker);
	if (get_current_time() - philo->fasting >= time_to_die && philo->eating == 0)
	{
		pthread_mutex_lock(&philo->locker.meal_locker);
		return (1);	
	}
	pthread_mutex_unlock(&philo->locker.meal_locker);
	return (0);
}

void	*service(void *add)
{
	t_args **philos;
	t_args *philo;
	int i;

	philo = (t_args **)(add);
	philo = philos;
	while(1)
	{
		int time;

		i = 0;
		while (i < philos[0]->num_of_philo)
		{
			if (philosopher_dead(&philos[i], philos[i]->time_to_die) == 1)
			{
				pthread_mutex_lock(&philo->locker.write_locker);
				time = get_current_time() - philos[i]->start;
				printf("%zu %d died\n", time, philos[i]->n_philo);
				pthread_mutex_unlock(&philo->locker.write_locker);
				pthread_mutex_lock(&philo->locker.dead_locker);
				philos[i]->dead_flag = 1;
				pthread_mutex_unlock(&philo->locker.dead_locker);
				return (1);
			}
		i++;
	}
	}
	return (NULL);
}

void	*life(void *add)
{
	t_args *philo;
	int i;
	int life;

	philo = (t_args *)(add);
	if ((philo->n_philo) % 2 == 0)
		usleep(10);
	while (is_dead_or_full(philo))
	{
		if (philo->num_of_philo != 1)
			eating(philo);
		pthread_mutex_lock(&philo->locker.write_locker);
		printf("%dms %d is sleeping\n", philo->time_to_sleep, (philo->n_philo
				+ 1));
		usleep(philo->time_to_sleep);
		pthread_mutex_unlock(&philo->locker.write_locker);
		pthread_mutex_lock(&philo->locker.write_locker);
		printf("%dms %d is thinking\n", 0, (philo->n_philo + 1));
		pthread_mutex_unlock(&philo->locker.write_locker);

	}
	return (NULL);
}

void	init_mutix(t_mutix *locker, int forks)
{
	int i;

	i = 0;
	locker->forks = NULL;
	locker->forks = (pthread_mutex_t *)malloc(forks * sizeof(pthread_mutex_t));
	if (!locker->forks)
		return ;
	pthread_mutex_init(&locker->meal_locker, NULL);
	pthread_mutex_init(&locker->write_locker, NULL);
	pthread_mutex_init(&locker->dead_locker, NULL);
	while (i < forks)
	{
		pthread_mutex_init(&locker->forks[i], NULL);
		i++;
	}
}

void	destroy_mutix(t_mutix *locker, int forks)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&locker->meal_locker);
	pthread_mutex_destroy(&locker->write_locker);
	pthread_mutex_init(&locker->dead_locker, NULL);
	while (i < forks)
	{
		pthread_mutex_destroy(&locker->forks[i]);
		i++;
	}
	free(locker->forks);
}

void	ft_philosophers(int argc, char **argv)
{
	int i;
	int x = ft_atoi(argv[1]);
	t_args philos[x];
	pthread_t waiter;
	t_mutix locked;
	i = 0;

	init_mutix(&locked, x);
	while (i < x)
	{
		philos[i] = arguments(argc, argv, i, locked);
		i++;
	}
	pthread_create(&waiter, NULL, service, (void *)&philos);
	i = 0;
	while (i < x)
	{
		pthread_create(&philos[i].philosophers, NULL, life, (void *)&philos[i]);
		i++;
	}
	i = 0;
	pthread_join(waiter, NULL);
	while (i < x)
	{
		pthread_join(philos[i].philosophers, NULL);
		i++;
	}
	destroy_mutix(&locked, x);
}

int	main(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc > 6 || argc < 5)
	{
		printf("Error\n");
		return (0);
	}
	ft_philosophers(argc, argv);
	return (0);
}

/*
	printf("%d %d has taken a fork\n", );
	printf("%d %d is eating\n", );
	printf("%d %d is sleeping\n", );
	printf("%d %d is thinking\n", );
	printf("%d %d died\n", );

	pthread_mutex_init(&mutex, NULL);

	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_destroy(&mutex);
*/
