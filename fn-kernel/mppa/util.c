/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * mppa/util.c - Utility library implementation.
 */

#include <arch.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <mppa/osconfig.h>

/*
 * Prints an error message and exits.
 */
void error(const char *msg)
{
	fprintf(stderr, "error: %s\n", msg);
	exit(EXIT_FAILURE);
}

/*
 * Safe malloc().
 */
void *smalloc(size_t size)
{
	void *p;
	
	p = malloc(size);
	
	/* Failed to allocate memory. */
	if (p == NULL)
		error("cannot malloc()");
	
	return (p);
}

/*
 * Timer residual error.
 */
uint64_t timer_error = 0;

/*
 * Gets the current timer value.
 */
uint64_t timer_get(void)
{
	return (__k1_io_read64((void *)0x70084040) / MPPA_FREQUENCY);
}

/*
 * Initializes the timer.
 */
void timer_init(void)
{
  uint64_t start, end;
  
  start = timer_get();
  end = timer_get();
  
  timer_error = (end - start);
}

/*
 * Computers the difference between two times
 */
uint64_t timer_diff(uint64_t t1, uint64_t t2)
{
	return (t2 - t1 - timer_error);
}
