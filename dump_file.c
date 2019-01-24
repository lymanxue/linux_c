/******************************************************************************
 * @file   dump_file.c
 *
 *
 * Copyright (c) 2018-2019.
 * All rights reserved
 *
 * The present software is the confidential and proprietary information of
 * lyman. You shall not disclose the present software and shall use it
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
#include "dump_file.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int32_t dump_file_status(const char *path)
{
	FILE *fp;
	char ch;

	if ((fp = fopen(path, "r")) != NULL) {
		if ((ch = fgetc(fp)) == EOF) {
			fclose(fp);
			return 0;
		}else {
			fclose(fp);
			return -1;
		}
	}

	return -1;
}

static uint64_t dump_util_get_seconds(void)
{
    uint64_t msec = 0;
    time_t timep;

    time(&timep);
    msec = (uint64_t)timep;

    return msec;
}

static int32_t dump_util_seconds_to_date(uint64_t seconds, char *datastr, uint32_t len)
{
    time_t timep = (time_t)seconds;
    struct tm *p;

    if (datastr == NULL || len == 0) {
        printf("param invalid");
        return -1;
    }

    p = localtime(&timep);
    snprintf(datastr, len, "%04d%02d%02d-%02d%02d%02d", (1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);

    return 0;
}

void dump_file_save(void)
{
	char datastr[64] = {0};
	char buf[256] = {0};
	char result[8] = {0};
	uint32_t fd = -1;
	uint32_t len = 0;

	uint64_t second = dump_util_get_seconds();
	dump_util_seconds_to_date(second, datastr, sizeof(datastr));

	fd = open(DUMP_PATH, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0) {
		printf("open dump fd failed. \n");
		return -1;
	}

	memset(buf, 0, sizeof(buf));
	snprintf(result, sizeof(result), "%s", (0 >= 0)?"success":"failed ");

	if (dump_file_status(DUMP_PATH) == 0) {
		printf("dump title... \n");
		len = snprintf(buf, sizeof(buf), "测试项 %s %-17s %s    : %-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s\n", \
			"步骤", "日期", "结果", "dead_pixels", "circle", "diameter", "mean_w", "mean_b", "p_percent", "p_wb_percent", \
			"noise", "blot", "blot_glass", "status", "shading", "shading_unit");
		write(fd, buf, len);
		memset(buf, 0, sizeof(buf));
	}
	len = snprintf(buf, sizeof(buf), "cal    %d %18s %s : %-14d%-14d%-14d%-14d%-14d%-14d%-14d%-14d%-14d%-14d%-14d%-14d%-14d\n", \
		1, datastr, result, 1, 100, 0, 56, 2003, 3, 16, \
		34, 2, 0, 0, 5678, 2);
	write(fd, buf, len);
	//lseek(fd, 0, SEEK_SET);
	close(fd);

	return ;
}
