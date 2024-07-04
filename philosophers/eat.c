
#include "philo.h"

t_args	flatware(t_args philo, t_mutix locked)
{
	int l;
	int r;

	l = philo.n_philo;
	r = philo.n_philo + 1;
	if ((r + 1) >= philo.num_of_philo)
		r = 0;
	philo.l_fork = l;
	philo.r_fork = r;
	philo.locker.l_fork_locker = locked.forks[l];
	philo.locker.r_fork_locker = locked.forks[r];
	return(philo);
}

int	eating(t_args *philo)
{
	pthread_mutex_lock(&philo->locker.l_fork_locker);

	pthread_mutex_lock(&philo->locker.write_locker);
	printf("%dms %d has taken a lfork\n", 0, (philo->n_philo + 1));
	pthread_mutex_unlock(&philo->locker.write_locker);

	pthread_mutex_lock(&philo->locker.r_fork_locker);

	pthread_mutex_lock(&philo->locker.write_locker);
	printf("%dms %d has taken a rfork\n", 0, (philo->n_philo + 1));
	pthread_mutex_unlock(&philo->locker.write_locker);
	
	pthread_mutex_lock(&philo->locker.meal_locker);
	philo->until_full++;
	philo->fasting = get_current_time();
	pthread_mutex_unlock(&philo->locker.meal_locker);

	pthread_mutex_lock(&philo->locker.write_locker);
	printf("%dms %d is eating\n", philo->time_to_eat, (philo->n_philo + 1));
	pthread_mutex_unlock(&philo->locker.write_locker);
	
	pthread_mutex_unlock(&philo->locker.r_fork_locker);
	pthread_mutex_unlock(&philo->locker.l_fork_locker);
	
	return (0);
}
