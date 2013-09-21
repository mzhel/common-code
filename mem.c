#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <log.h>

void*
mem_alloc(
          size_t len
          )
{
	void* r = NULL;

	do {

		r = malloc(len);

		if (!r){

		    LOG_ERROR("Failed to allocate memory.");

		    break;

		}

		memset(r, 0, len);

	} while (false);

	return r;
}

void
mem_free(
         void* m
         )
{
	do {

	    free(m);

	} while (false);

}
