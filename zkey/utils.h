/*
 * zkey - Generate, re-encipher, and validate secure keys
 *
 * This header file defines the interface to the CCA host library.
 *
 * Copyright IBM Corp. 2019
 *
 * s390-tools is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#ifndef UTILS_H
#define UTILS_H

#include "lib/zt_common.h"

int sysfs_is_card_online(int card);

int sysfs_is_apqn_online(int card, int domain);

int sysfs_get_card_level(int card);

int sysfs_get_serialnr(int card, char serialnr[9], bool verbose);

#define MK_STATE_EMPTY		0
#define MK_STATE_PARTIAL	1
#define MK_STATE_FULL		2
#define MK_STATE_VALID		3
#define MK_STATE_INVALID	4
#define MK_STATE_UNKNOWN	-1

struct mk_info_reg {
	int	mk_state;
	u64	mkvp;
};

struct mk_info {
	struct mk_info_reg	new_mk;
	struct mk_info_reg	cur_mk;
	struct mk_info_reg	old_mk;
};

int sysfs_get_mkvps(int card, int domain, struct mk_info *mk_info,
		    bool verbose);

typedef int(*apqn_handler_t) (int card, int domain, void *handler_data);

int handle_apqns(const char *apqns, apqn_handler_t handler, void *handler_data,
		 bool verbose);

int print_mk_info(const char *apqns, bool verbose);

int cross_check_apqns(const char *apqns, u64 mkvp, int min_level,
		      bool print_mks, bool verbose);

bool prompt_for_yes(bool verbose);

#endif
