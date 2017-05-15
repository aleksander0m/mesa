/*
 * Copyright 2016 Google Inc. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#pragma once

#ifdef HAS_GRALLOC_DRM_HEADERS

#include <gralloc_drm.h>
#include <gralloc_drm_handle.h>

#else

#define GRALLOC_MODULE_PERFORM_GET_DRM_FD 0x0FD4DEAD

/* Gross hack */
struct gralloc_drm_handle_t {
	native_handle_t base;

	/* file descriptors */
	int prime_fd;

	/* integers */
	int magic;

	int width;
	int height;
	int format;
	int usage;

	int name;   /* the name of the bo */
	int stride; /* the stride in bytes */

	int data_owner; /* owner of data (for validation) */
	union {
		void *data; /* pointer to struct gralloc_gbm_bo_t */
		uint64_t reserved;
	} __attribute__((aligned(8)));
};

struct gralloc_gbm_bo_t {
	struct gbm_bo *bo;
	void *map_data;

	struct gralloc_gbm_handle_t *handle;

	int imported;  /* the handle is from a remote proces when true */

	int lock_count;
	int locked_for;

	unsigned int refcount;
};

static inline struct gralloc_drm_handle_t *gralloc_drm_handle(buffer_handle_t _handle)
{
   return NULL; /* Not supported, return invalid handle. */
}

#endif
