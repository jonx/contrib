/*
    Copyright (C) 2026, The AROS Development Team. All rights reserved.

    AROS changes to Mbed TLS's default configuration, read after it
    (MBEDTLS_USER_CONFIG_FILE). The library keeps everything the default
    offers, client and server, except what AROS cannot give it.
*/

/* bsdsocket.library sockets are not file descriptors: the application
   gives the library its own send and receive (mbedtls_ssl_set_bio) */
#undef MBEDTLS_NET_C
/* needs POSIX timers and signals */
#undef MBEDTLS_TIMING_C
/* no key storage on disk */
#undef MBEDTLS_PSA_ITS_FILE_C
#undef MBEDTLS_PSA_CRYPTO_STORAGE_C
/* no CPU-specific code: one source for every AROS target */
#undef MBEDTLS_AESNI_C
#undef MBEDTLS_AESCE_C
#undef MBEDTLS_PADLOCK_C
/* the x86_64 link has no 128-bit division helper */
#define MBEDTLS_NO_UDBL_DIVISION

/* randomness: getentropy(), which posixc answers from entropy.resource
   (mbedtls_hardware_poll in mbedtls_aros.c); there is no /dev/urandom */
#define MBEDTLS_NO_PLATFORM_ENTROPY
#define MBEDTLS_ENTROPY_HARDWARE_ALT
/* milliseconds: mbedtls_ms_time in mbedtls_aros.c */
#define MBEDTLS_PLATFORM_MS_TIME_ALT
