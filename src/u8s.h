#ifndef U8S_H
#define U8S_H

#include <stddef.h>

typedef char * u8s_ptr;
typedef const char * u8s_cptr;

/* Get beginning of next UTF-8 character. */
u8s_cptr u8s_next(u8s_cptr str);
/* Get length of UTF-8 string in characters. */
size_t u8s_strlen(u8s_cptr str);
/* Get length of UTF-8 string in bytes. */
size_t u8s_strlenb(u8s_cptr str);
/* Copy UTF-8 string into target. */
u8s_ptr u8s_strcpy(u8s_ptr target, u8s_cptr src);
/* Copy at most bufsiz bytes of the source UTF-8 string into target, respecting
    UTF-8 character boundaries, and ensuring that the target is
    NULL-terminated. */
u8s_ptr u8s_strncpy(u8s_ptr target, u8s_cptr src, size_t bufsiz);
/* Compare two NULL-terminated UTF-8 strings. */
int u8s_strcmp(u8s_cptr a, u8s_cptr b);
/* Compare at most the first bufsiz bytes of two possibly non-NULL-terminated
    UTF-8 strings. */
int u8s_strncmp(u8s_cptr a, u8s_cptr b, size_t bufsiz);
/* Create a copy of a NULL-terminated UTF-8 string with memory allocated via
    malloc(). */
u8s_ptr u8s_strdup(u8s_cptr s);

#endif
