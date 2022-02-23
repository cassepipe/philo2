#include <pthread.h>
#include <threads.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

#define LOCKED true
#define UNLOCKED false

#define FORK1_STR " has taken a fork (1/2)\n"
#define FORK2_STR " has taken a fork (2/2)\n"
#define DIE_STR " has died\n"
#define EAT_STR " is eating\n"
#define SLEEP_STR " is sleeping\n"
#define THINK_STR " is thinking\n"

#define NOERROR 0
#define ERROR	-1
#define	ALIVE	0
#define	DEAD	1
#define DONE_EATING 2
#define DID_NOT_EAT 3
#define DID_TAKE 4
#define DID_NOT_TAKE 5
#define DONE_THINKING 6
#define DONE_SLEEPING 7

/*typedef enum e_philo_state {*/
/*    ALIVE,*/
/*    DEAD,*/
/*    DONE,*/
/*    ERROR,*/
/*    TAKEN,*/
/*    DONE_EATING,*/
/*}	t_state;*/

typedef pthread_mutex_t t_mutex;
/*typedef phtread_mutex_t t_fork;*/

typedef struct s_fork {
	t_mutex mutex;
	bool	status;
} t_fork;

typedef struct s_env t_env;

typedef struct s_philo {
	t_env	*env;
	t_fork	*own_fork;
	t_fork	*borrowed_fork;
	pthread_t	thread;
	unsigned long 	starting_time;
	unsigned long	last_meal_time;
	int		meals_left;
	int 	id;
	int		is_uneven;
	int		is_first;
	int		is_last;
} t_philo;

typedef struct s_env {
	t_philo *philosophers;
	t_fork	*forks;
	t_mutex quitlock;
	t_mutex	printlock;
	int	nb_philo;
	int quit;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	must_eat_times;
} t_env;

/*#include "main.h"*/

#define USLEEP_SPLIT 10.0

void	usleep_ms(unsigned int time_in_ms)
{
	float	time;
	int				i;

	i = 0;
	time = ((float) time_in_ms) * 1000.0 / USLEEP_SPLIT;
	while (i < USLEEP_SPLIT)
	{
		usleep(time);
		i++;
	}
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	value;
	size_t			i;

	p = (unsigned char*)s;
	value = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		p[i] = value;
		i++;
	}
	return (s);
}

t_env	*new_env()
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (new_env)
	{
		ft_memset(new_env, 0, sizeof(t_env));
	}
	return (new_env);
}

/*Check for return status ?*/

int lock(t_mutex *mutex)
{
  return (pthread_mutex_lock(mutex));
}

int lock_fork(t_fork *fork)
{
  return (pthread_mutex_lock(&fork->mutex));
}

int unlock(t_mutex *mutex)
{
  return (pthread_mutex_unlock(mutex));
}

int unlock_fork(t_fork *fork)
{
  return (pthread_mutex_unlock(&fork->mutex));
}

void	mark_fork_as_locked(t_fork *fork)
{
	fork->status = LOCKED;
}

void	mark_fork_as_unlocked(t_fork *fork)
{
	fork->status = UNLOCKED;
}

static int	ft_isspace(const char c)
{
	if (c == ' '
	|| c == '\t'
	|| c == '\v'
	|| c == '\n'
	|| c == '\f'
	|| c == '\r')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

int			ft_atoi(const char *nptr)
{
	long	result;
	size_t	i;
	size_t	neg;

	result = 0;
	i = 0;
	neg = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
		neg = ++i;
	while (ft_isdigit(nptr[i]))
	{
		result *= 10;
		result += nptr[i] - '0';
		i++;
	}
	if (neg)
		return (-result);
	else
		return (result);
}

int	get_nb_philo(t_env *env, char **av)
{
	int nb_philo;

	nb_philo = ft_atoi(av[1]);
	if (nb_philo <= 0)
		return (-1);
	else
		env->nb_philo = nb_philo;
	return (0);
}

int	get_time_to_die(t_env *env, char **av)
{
	int time_to_die;

	time_to_die = ft_atoi(av[2]);
	if (time_to_die <= 0)
		return (-1);
	else
		env->time_to_die = time_to_die;
	return (0);
}

int	get_time_to_eat(t_env *env, char **av)
{
	int time_to_eat;

	time_to_eat = ft_atoi(av[3]);
	if (time_to_eat <= 0)
		return (-1);
	else
		env->time_to_eat = time_to_eat;
	return (0);
}

int	get_time_to_sleep(t_env *env, char **av)
{
	int time_to_sleep;

	time_to_sleep = ft_atoi(av[4]);
	if (time_to_sleep <= 0)
		return (-1);
	else
		env->time_to_sleep = time_to_sleep;
	return (0);
}

int	get_must_eat_times(t_env *env, char **av)
{
	int must_eat_times;

	must_eat_times = ft_atoi(av[5]);
	if (must_eat_times <= 0)
		return (-1);
	else
		env->must_eat_times = must_eat_times;
	return (0);
}

int init_forks(t_env *env)
{
	int i;
	int ret;

	i = 0;
	while (i < env->nb_philo)
	{
		ret = pthread_mutex_init(&env->forks[i].mutex, NULL);
		if (ret)
			return (ret);
		env->forks[i].status = UNLOCKED;
		i++;
	}
	return (0);
}

int	init_locks(t_env *env)
{
	int ret;

	ret = init_forks(env);
	if (ret)
		return (ret);
	ret = pthread_mutex_init(&env->quitlock, NULL);
	if (ret)
		return (ret);
	ret = pthread_mutex_init(&env->printlock, NULL);
	if (ret)
		return (ret);
	return (0);
}

int	init_philosophers(t_env *env, t_philo *philos)
{
	int i;
	int j;

	i = 0;
	/*ft_memset(philos, 0, sizeof(t_philo) * env->nb_philo);*/
	while (i < env->nb_philo)
	{
		philos[i].env = env;
		philos[i].id = i + 1;
		philos[i].own_fork = &env->forks[i];
		j = (philos[i].id != env->nb_philo) * (i + 1);
		philos[i].borrowed_fork = &env->forks[j];
		philos[i].starting_time = 0;
		philos[i].last_meal_time = 0;
		if (env->must_eat_times < 1)
			philos[i].meals_left = -1;
		else
			philos[i].meals_left = env->must_eat_times;
		philos[i].is_uneven = (philos[i].id % 2);
		philos[i].is_first = (philos[i].is_uneven && philos[i].id == 1);
		philos[i].is_last = (philos[i].is_uneven && philos[i].id == env->nb_philo);
		printf("Philo[%i] owns fork %i and borrowed %i\n", philos[i].id, philos[i].own_fork, philos[i].borrowed_fork);
		i++;
	}
	return (0);
}

int	init_env(t_env *env, int ac, char **av)
{
	int ret;

	if (ac != 5 && ac != 6)
		return (7);
	if (get_nb_philo(env, av))
		return (1);
	if (get_time_to_die(env, av))
		return (2);
	if (get_time_to_eat(env, av))
		return (3);
	if (get_time_to_sleep(env, av))
		return (4);
	if (ac == 6)
		if (get_must_eat_times(env, av))
			return (5);
	env->philosophers = malloc(env->nb_philo * sizeof(t_philo));
	env->forks = malloc(env->nb_philo * sizeof(t_fork));
	if (env->forks == NULL || env->philosophers == NULL)
		return (8);
	ret = init_locks(env);
	if (ret)
		return (9);
	init_philosophers(env, env->philosophers);
	return (0);
}

void free_env(t_env *env)
{
	free(env->forks);
	free(env->philosophers);
	free(env);
}

int	get_time(unsigned long *time)
{
	struct timeval	tv;
	unsigned long	ret;

	if (gettimeofday(&tv, NULL) != 0)
		return (ERROR);
	ret = 1000 * (unsigned long)(tv.tv_sec);
	ret += (unsigned long)(tv.tv_usec) / 1000;
	*time = ret;
	return (NOERROR);
}

void	assign_forks(t_fork **fork1, t_fork **fork2, t_philo *philo)
{
	*fork1 = philo->own_fork;
	*fork2 = philo->borrowed_fork;
	/*if (philo->id % 2)*/
	/*{*/
	/*    *fork1 = philo->borrowed_fork;*/
	/*    *fork1 = philo->own_fork;*/
	/*}*/
}

/*Can't the lock happen inside the if statement ?*/
int	take_fork(t_fork *fork)
{
	int	ret;

	ret = DID_NOT_TAKE;
	lock(&fork->mutex);
	if (fork->status == UNLOCKED)
	{
		fork->status = LOCKED;
		ret = DID_TAKE;
	}
	unlock(&fork->mutex);
	return (ret);
}

void	put_down_fork(t_fork *fork)
{
	lock(&fork->mutex);
	fork->status = UNLOCKED;
	unlock(&fork->mutex);
}

void	put_down_both_forks(t_philo *philo)
{
	put_down_fork(philo->own_fork);
	put_down_fork(philo->borrowed_fork);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char*)dest;
	s = (unsigned char *)src;
	if (!d && !s)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

unsigned long    to_the_power_of(unsigned long n, unsigned long p)
{
	unsigned long result;

	result = 1;
	while (p--)
		result *= n;
	return (result);
}

char    *ulong_repr(long n, char *buffer, int *len)
{
	unsigned long   i;
	unsigned long   digit;
	unsigned long   a_power_of_ten;
	int	            pos;

	pos = 1;
	i = n;
	while (i /= 10)
		pos++;
	*len += pos;
	a_power_of_ten = to_the_power_of(10, pos - 1);
	i = 0;
	while (--pos >= 0)
	{
		digit = n / a_power_of_ten;
		buffer[i] = "0123456789"[digit];
		n = n - digit * a_power_of_ten;
		a_power_of_ten /= 10;
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

long	gettimeofday_in_ms()
{
	struct timeval tv;
	long	time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = tv.tv_sec * 1000;
	time_in_ms += tv.tv_usec / 1000;
	return (time_in_ms);
}

void	print_philo(const t_philo *philo, const char *action, int act_len)
{
	char			buffer[256];
	int				len;
	unsigned long	timestamp;

	len = 0;
	get_time(&timestamp);
	timestamp = timestamp - philo->starting_time;
	ulong_repr(timestamp, buffer, &len);
	ft_memcpy(buffer + len, "ms Philo ", sizeof("ms Philo ") - 1);
	len += sizeof("ms Philo ") - 1;
	ulong_repr(philo->id, buffer + len, &len);
	ft_memcpy(buffer + len, action, act_len);
	len += act_len;
	write(STDOUT_FILENO, buffer, len);
}

void	print_philo_death(const t_philo *philo, t_env *env)
{
	if (env->quit == 0)
		print_philo(philo, DIE_STR, sizeof(DIE_STR) - 1);
}

void	print_philo_eat(const t_philo *philo, t_env *env)
{
	if (env->quit == 0)
		print_philo(philo, EAT_STR, sizeof(EAT_STR) - 1);
}

void	print_philo_sleep(const t_philo *philo, t_env *env)
{
	if (env->quit == 0)
		print_philo(philo, SLEEP_STR, sizeof(SLEEP_STR) - 1);
}

void	print_philo_think(const t_philo *philo, t_env *env)
{
	if (env->quit == 0)
		print_philo(philo, THINK_STR, sizeof(THINK_STR) - 1);
}

/*Do I really need to check philo's meals left ?*/
int	check_state(t_philo *philo, t_env *env)
{
	unsigned long	time;

	if (env->quit > 0)
		return (DEAD);
	if (philo->meals_left == 0)
		return (DONE_EATING);
	if (get_time(&time) == ERROR)
		return (ERROR);
	time -= philo->last_meal_time;
	if (time > (unsigned long)env->time_to_die)
	{
		print_philo_death(philo, env);
		env->quit++;
		return (DEAD);
	}
	return (ALIVE);
}

/*Need to check for end ?*/
int	eat_action(t_philo *philo, t_env *env)
{
	unsigned long	time;

	if (get_time(&time) == ERROR)
		return (ERROR);
	print_philo_eat(philo, env);
	philo->last_meal_time = time;
	if (env->must_eat_times > 0)
		philo->meals_left--;
	time = env->time_to_eat;
	if (env->time_to_eat > env->time_to_die)
		time = env->time_to_die;
	usleep_ms(time);
	return (DONE_EATING);
}

int	eat_cycle(t_philo *philo, t_env *env, t_fork *fork1, t_fork *fork2)
{
	if (take_fork(fork1) == DID_NOT_TAKE)
	{
		usleep(500);
		return (DID_NOT_EAT);
	}
	if (take_fork(fork2) == DID_NOT_TAKE)
	{
		put_down_fork(fork1);
		usleep(500);
		return (DID_NOT_EAT);
	}
	if (eat_action(philo, env) == ERROR)
	{
		put_down_both_forks(philo);
		return (ERROR);
	}
	put_down_both_forks(philo);
	return (DONE_EATING);
}

int	eat(t_philo *philo, t_env *env)
{
	t_fork	*fork1;
	t_fork	*fork2;
	int		state;

	assign_forks(&fork1, &fork2, philo);
	state = eat_cycle(philo, env, fork1, fork2);
	while (state != DONE_EATING)
	{
		state = eat_cycle(philo, env, fork1, fork2);
	}
	return (DONE_EATING);
}

/*Fuck me I don't understand this !*/
int	sleeph(t_philo *philo, t_env *env)
{
	unsigned long	time;
	/*unsigned long	time_since_start;*/
	/*unsigned long	time_since_last_meal;*/
	/*unsigned long	since_last_meal_plus_sleep;*/

	if (get_time(&time) == ERROR)
		return (ERROR);
	/*time_since_start = time - philo->starting_time;*/
	print_philo_sleep(philo, env);
	/*time_since_last_meal = time - philo->last_meal_time;*/
	/*since_last_meal_plus_sleep = time_since_last_meal + (unsigned long)(env->time_to_sleep);*/
	/*if (since_last_meal_plus_sleep > (unsigned long)(env->time_to_die))*/
	/*    time_since_last_meal = env->time_to_die - time_since_last_meal;*/
	/*else*/
	/*    time_since_last_meal = env->time_to_sleep;*/
	/*usleep(time_since_last_meal * 1000);*/
	usleep(env->time_to_sleep * 1000);
	return (DONE_SLEEPING);
	/*Donc si le temps écoulé depuis le dernier repas ajouté au temps de sommeil est supérieur au temps de la mort, tu fais dormir ton philo la diff entre le temps*/
	/*de mort et le temps écoulé depuis le dernier repas. Mindfuck*/
}


int	think(t_philo *philo, t_env *env)
{
	unsigned long	time;

	if (get_time(&time) == ERROR)
		return (ERROR);
	time -= philo->starting_time;
	print_philo_think(philo, env);
	usleep(1000);
	return (DONE_THINKING);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *) arg;
	env = philo->env;
	if (philo->id % 2)
		usleep(10000);
	get_time(&philo->starting_time);
	get_time(&philo->last_meal_time);
	while (1)
	{
		if (check_state(philo, env) != ALIVE)
			break;
		if (eat(philo, env) != DONE_EATING)
			break;
		if (check_state(philo, env) != ALIVE)
			break;
		if (sleeph(philo, env) != DONE_SLEEPING)
			break;
		if (check_state(philo, env) != ALIVE)
			break;
		if (think(philo, env) != DONE_THINKING)
			break;
	}
	/*printf("Philo %i exiting...\n", philo->id);*/
	return (NULL);
}

int	start_dinner(t_env *env)
{
	int i;
	int ret;

	i = 0;
	while (i < env->nb_philo)
	{
		ret = pthread_create(&env->philosophers[i].thread, NULL, &routine, &env->philosophers[i]);
		if (ret)
			return (10);
		i++;
	}
	return (0);
}

void		wait_end(t_env *env)
{
	int i;

	i = 0;
	while (i < env->nb_philo)
	{
		pthread_join(env->philosophers[i].thread, NULL);
		i++;
	}
}

int 	main(int ac, char **av)
{
	int ret;
	t_env *env;

	env = new_env();
	if (!env)
		return  (1);
	ret = init_env(env, ac, av);
	if (!ret)
		ret = start_dinner(env);
	wait_end(env);
	free_env(env);
	return (ret);
}
