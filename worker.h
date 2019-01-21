
#ifndef __WORKER_H__
#define __WORKER_H__

/* LOG */
#define LOG_MSG_DEBUG(fmt, ...) printf("[%s] " fmt, __func__, ##__VA_ARGS__)

/* Return Num */
typedef enum {
    R_SUCCESS = 0,
    R_FAILED,
}ret_num_t;

/* function declartion */


#endif