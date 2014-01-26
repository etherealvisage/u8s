#include <stdlib.h>
#include <string.h>

#include "u8s.h"

u8s_cptr u8s_next(u8s_cptr str) {
    // non-extended character?
    if((*str & 0xc0) == 0x0) return str+1;
    // the annoying case, in the middle of a character
    if((*str & 0xc0) == 0x80) {
        while((*str & 0xc0) == 0x80) str ++;
        return str;
    }
    // beginning of extended character. We know what to do!
    // two-byte?
    if((*str & 0xe0) == 0xc0) return str+2;
    // three-byte?
    if((*str & 0xf0) == 0xe0) return str+3;
    // four-byte?
    if((*str & 0xf8) == 0xf0) return str+4;
    // five-byte?
    if((*str & 0xfc) == 0xf8) return str+5;
    // six-byte?
    if((*str & 0xfe) == 0xfc) return str+6;

    // This should never happen, it's a malformed byte.
    return str+1;
}

size_t u8s_strlen(u8s_cptr str) {
    size_t result = 0;
    while(*str != 0) {
        str = u8s_next(str);
        result ++;
    }
    return result;
}

size_t u8s_strlenb(u8s_cptr str) {
    size_t result = 0;
    while(*str != 0) str ++, result ++;
    return result;
}

u8s_ptr u8s_strcpy(u8s_ptr target, u8s_cptr src) {
    do {
        *(target ++) = *(src ++);
    } while(*src != 0);
    *target = 0;
    return target;
}

u8s_ptr u8s_strncpy(u8s_ptr target, u8s_cptr src, size_t bufsiz) {
    size_t used = 0;
    while(*src != 0) {
        u8s_cptr next = u8s_next(src);
        ptrdiff_t len = next-src;
        if(used+len >= bufsiz) break;
        memcpy(target, src, len);
        target += len, src += len;
    }
    *target = 0;
    return target;
}

int u8s_strcmp(u8s_cptr a, u8s_cptr b) {
    return u8s_strncmp(a, b, (unsigned)-1);
}

int u8s_strncmp(u8s_cptr a, u8s_cptr b, size_t bufsiz) {
    return strncmp(a, b, bufsiz);
}

u8s_ptr u8s_strdup(u8s_cptr s) {
    return u8s_strcpy(malloc(u8s_strlenb(s)), s);
}
