/*
    Copyright (C) 2026, The AROS Development Team. All rights reserved.

    What Mbed TLS asks of the system and AROS answers in its own way.
    Compiled into libmbedcrypto.a.
*/

#include <time.h>
#include <unistd.h>
#include <sys/time.h>

#include <mbedtls/build_info.h>
#include <mbedtls/entropy.h>
#include <mbedtls/platform_time.h>

/* MBEDTLS_ENTROPY_HARDWARE_ALT: the library's one entropy source.
   getentropy() gives 256 bytes at most per call. */
int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen)
{
    size_t at = 0;
    (void)data;
    while (at < len)
    {
        size_t n = len - at > 256 ? 256 : len - at;
        if (getentropy(output + at, n) != 0)
            return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
        at += n;
    }
    *olen = len;
    return 0;
}

/* MBEDTLS_PLATFORM_MS_TIME_ALT */
mbedtls_ms_time_t mbedtls_ms_time(void)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) != 0)
        return (mbedtls_ms_time_t)time(NULL) * 1000;
    return (mbedtls_ms_time_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
