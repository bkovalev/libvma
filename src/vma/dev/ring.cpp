/*
 * Copyright (c) 2001-2017 Mellanox Technologies, Ltd. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include "ring.h"

#undef  MODULE_NAME
#define MODULE_NAME     "ring"
#undef  MODULE_HDR
#define MODULE_HDR      MODULE_NAME "%d:%s() "

ring::ring(int count, uint32_t mtu) :
	m_n_num_resources(count), m_p_n_rx_channel_fds(NULL), m_parent(NULL),
	m_is_mp_ring(false), m_mtu(mtu)
{
#ifdef DEFINED_VMAPOLL
	m_vma_active = true; /* TODO: This VMA version supports vma_poll() usage mode only */
	INIT_LIST_HEAD(&m_ec_list);
	m_vma_poll_completion = NULL;
#endif // DEFINED_VMAPOLL	
}

int ring::get_rx_channel_fds_index(uint32_t index) const {
	if (index < m_n_num_resources)
		return m_p_n_rx_channel_fds[index];
	return -1;
};
ring::~ring()
{
#ifdef DEFINED_VMAPOLL
	ring_logdbg("queue of event completion elements is %s",
			(list_empty(&m_ec_list) ? "empty" : "not empty"));
#endif // DEFINED_VMAPOLL		
}
