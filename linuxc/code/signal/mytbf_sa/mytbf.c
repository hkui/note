#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include "mytbf.h"

typedef struct mytbf_st_ {
    int cps;
    int burst;
    int token;
    int pos;
} mytbf_st;

static mytbf_st *job[MYTBF_MAX];

static int inited = 0;

static struct sigaction alrm_sa_save;

static int get_free_pos(void) {
    int i;
    for (i = 0; i < MYTBF_MAX; i++) {
        if (job[i] == NULL) {
            return i;
        }
    }
    return -1;
}

static void alrm_action(int s, siginfo_t *infop, void *unused) {
    int i;
    //如果不是从kernel来的，不响应，程序里发出的都是从内核来的
    if (infop->si_code != SI_KERNEL) {
        return;
    }
    for (i = 0; i < MYTBF_MAX; i++) {
        if (job[i] != NULL) {
            job[i]->token += job[i]->cps;
            if (job[i]->token > job[i]->burst) {
                job[i]->token = job[i]->burst;
            }

        }
    }
}

static void module_unload(void) {
    struct itimerval itv;
    //恢复时钟
    sigaction(SIGALRM, &alrm_sa_save, NULL);
    //关掉时钟
    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 0;
    itv.it_value.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &itv, NULL) < 0) {
        perror("setitimer err");
        exit(1);
    }


    int i;
    for (i = 0; i < MYTBF_MAX; i++) {
        free(job[i]);
    }
}

static void module_load(void) {
    struct sigaction sa;
    struct itimerval itv;

    sa.sa_sigaction = alrm_action;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGALRM, &sa, &alrm_sa_save);

    itv.it_interval.tv_sec = 1;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 1;
    itv.it_value.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &itv, NULL) < 0) {
        perror("setitimer err");
        exit(1);
    }
    atexit(module_unload);
}

mytbf_t *mytbf_init(int cps, int burst) {
    mytbf_st *me;
    int pos;
    if (!inited) {
        module_load();
        inited = 1;
    }
    pos = get_free_pos();
    if (pos < 0) {
        return NULL;
    }

    me = malloc(sizeof(*me));
    if (me == NULL) {
        return NULL;
    }
    me->token = 0;
    me->cps = cps;
    me->burst = burst;
    me->pos = pos;
    job[pos] = me;
    return me;
}

static int min(int a, int b) {
    return a > b ? b : a;
}

int mytbf_fetchtoken(mytbf_t *ptr, int size) {
    mytbf_st *me = ptr;
    if (size <= 0) {
        return -EINVAL;
    }
    while (me->token <= 0) {
        pause();
    }
    int n;
    n = min(me->token, size);
    me->token -= n;
    return n;

}

int mytbf_returntoken(mytbf_t *ptr, int size) {
    mytbf_st *me = ptr;
    if (size <= 0) {
        return -EINVAL;
    }
    me->token += size;
    if (me->token > me->burst) {
        me->token = me->burst;
    }
    return size;
}

int mytbf_destory(mytbf_t *ptr) {
    mytbf_st *me = ptr;
    job[me->pos] = NULL;

    free(ptr);
    return 0;
}

