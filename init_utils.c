#include "philosophers.h"

void    init_colors()
{
    g_dudes[0].color = "33";
    g_dudes[1].color = "31";
    g_dudes[2].color = "34";
    g_dudes[3].color = "35";
    g_dudes[4].color = "36";
    g_dudes[5].color = "32";
    g_dudes[6].color = "30";
}

void        init_resources()
{
    int       i;

    i = 0;
    init_colors();
    while (i < 7)
    {
        g_dudes[i].state = 'R';
        g_dudes[i].time_to_think = rand() % 5;
        g_dudes[i].time_to_eat = rand() % 5;
        g_dudes[i].time_to_rest = rand() % 5;
        g_dudes[i].hunger = 10 + rand() % 50;
        g_dudes[i].rice = 100;
        g_dudes[i].i = i;
        g_dudes[i].st_i = 0;
        g_chopsticks[i] = 0;
        pthread_create(&(g_dudes[i].handler), NULL, set_brain, &g_dudes[i]);
        i = i + 1;
    }
}

void 		print_states_history()
{
    int 	i;

    fprintf(stdout, "\n\nResult : \n\n");
    i = 0;
    while (i < 7)
    {
        g_dudes[i].states[g_dudes[i].st_i] = 0;
        printf("\e[1;%smPhilosopher %d : [%s]\e[m\n", g_dudes[i].color, i, g_dudes[i].states);
        ++i;
    }
}

void        wait_for()
{
    int     i;

    i = 0;
    while (i < 7)
    {
        pthread_join((g_dudes[i].handler), NULL);
        i = i + 1;
    }
}