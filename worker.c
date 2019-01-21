/******************************************************************************
 * @file   worker.c
 *
 *
 * Copyright (c) 2018-2019.
 * All rights reserved
 *
 * The present software is the confidential and proprietary information of
 * Silead Inc. You shall not disclose the present software and shall use it
 * only in accordance with the terms of the license agreement you entered
 * into with lyman. This software may be subject to export or import
 * laws in certain countries.
 *
 *
 * ------------------- Revision History ------------------------------
 * <author>    <date>   <version>     <desc>
 * Lyman Xue  2019/1/21   0.1.0       Init version
 *
 *****************************************************************************/

#include <pthread.h>
#include "worker.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


static pthread_t m_workerthread;
static pthread_mutex_t m_lock;
static pthread_cond_t m_worker_cond;



static void* _worker_command_loop(void *arg)
{
    uint32_t i = 5;

    LOG_MSG_DEBUG("init \n");

    while (i--) {
        LOG_MSG_DEBUG("i=%d \n", i);
    };

    pthread_cond_signal(&m_worker_cond);

    return R_SUCCESS;
}

int32_t worker_run(void)
{
    int32_t ret = -R_FAILED;

    LOG_MSG_DEBUG("init. \n");

    ret = pthread_create(&m_workerthread, NULL, _worker_command_loop, NULL);
    if (ret != R_SUCCESS)
        LOG_MSG_DEBUG("can't create thread (%d, %s)\n", ret, strerror(ret));

    return ret;
}

int32_t worker_init(void)
{
    LOG_MSG_DEBUG("init. \n");

    pthread_mutex_init(&m_lock, NULL);
    pthread_cond_init(&m_worker_cond, NULL);
    worker_run();
}

int32_t main(void)
{
    worker_init();
    pthread_mutex_lock(&m_lock);
    pthread_cond_wait(&m_worker_cond, &m_lock);
    pthread_mutex_unlock(&m_lock);
    return R_SUCCESS;
}

