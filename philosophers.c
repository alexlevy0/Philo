#include "philosophers.h"

int   	 	        g_chopsticks[7];
t_philosopher           g_dudes[7];
pthread_mutex_t	    g_choose = PTHREAD_MUTEX_INITIALIZER;

void 	        philosopher_eating(t_philosopher *p)
{
    p->state = 'E';
    p->states[p->st_i] = p->state;
    p->st_i++;
    g_chopsticks[p->i] = 1;
    g_chopsticks[(p->i + 1) % 7] = 1;
    pthread_mutex_unlock(&g_choose);
    fprintf(stdout, "\e[1;%smPhilosopher %d : Je mange maintenant\e[m\n", p->color, p->i);
    sleep(p->time_to_eat);
    p->rice -= p->hunger;
    if (p->rice < 0)
        p->rice = 0;
    fprintf(stdout, "\e[1;%smPhilosopher %d : J'ai fini de manger %d grains de riz (restant : %d riz)!\e[m\n", p->color,  p->i, p->hunger, p->rice);
    pthread_mutex_lock(&g_choose);
    g_chopsticks[p->i] = 0;
    g_chopsticks[(p->i + 1) % 7] = 0;
    pthread_mutex_unlock(&g_choose);
}

void 	        philosopher_thinking(t_philosopher *p)
{
    p->state = 'T';
    p->states[p->st_i] = p->state;
    p->st_i++;
    g_chopsticks[p->i] = 1;
    pthread_mutex_unlock(&g_choose);
    fprintf(stdout, "\e[1;%smPhilosopher %d : Je pense maintenant !\e[m\n", p->color,  p->i);
    sleep(p->time_to_think);
    fprintf(stdout, "\e[1;%smPhilosopher %d : J'ai fini de manger !\e[m\n", p->color,  p->i);
    while (p->state != 'E')
    {
        pthread_mutex_lock(&g_choose);
        if (g_chopsticks[(p->i + 1) % 7] == 0)
            philosopher_eating(p);
        else
            pthread_mutex_unlock(&g_choose);
    }
}

void 	philosopher_relax(t_philosopher *p)
{
    pthread_mutex_unlock(&g_choose);
    if (p->state == 'R')
        return ;
    p->state = 'R';
    p->states[p->st_i] = p->state;
    p->st_i++;
    fprintf(stdout, "\e[1;%smPhilosopher %d : Je me relax maintenant\e[m\n", p->color,  p->i);
    sleep(p->time_to_rest);
    fprintf(stdout, "\e[1;%smPhilosopher %d : J'ai fini de me relaxer\e[m\n", p->color,  p->i);
}

void                *set_brain(void *arg)
{
    t_philosopher 	*p;
    int 		    left;
    int 		    right;

    p = (t_philosopher*)arg;
    fprintf(stdout, "\e[1;%smPhilosopher %d : A table !\e[m\n",p->color, p->i);
    while (p->rice > 0)
    {
        pthread_mutex_lock(&g_choose);
        left  = g_chopsticks[p->i];
        right  = g_chopsticks[(p->i + 1) % 7];
        if (left == 0 && right == 0 && p->state != 'E')
            philosopher_eating(p);
        else if (left == 0 && p->state != 'T' && p->state != 'E')
            philosopher_thinking(p);
        else
            philosopher_relax(p);
    }
    fprintf(stdout, "\e[1;%smPhilosopher %d : Quitte la table\e[m\n", p->color, p->i);
    return (NULL);
}

int         main()
{
    srand(time(NULL));
    init_resources();
    wait_for();
    print_states_history();
    return (0);
}
