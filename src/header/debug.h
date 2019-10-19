#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define LOG_DEBUG(message, ...)                                                \
    fprintf(stderr, "[DEBUG] (%s:%d) " message "\n", __FILE__, __LINE__,       \
            ##__VA_ARGS__)

#else
#define LOG_DEBUG(message, ...) {}
#endif

#define LOG_INFO(message, ...)                                                 \
    fprintf(stderr, "[INFO] (%s:%d) " message "\n", __FILE__, __LINE__,        \
            ##__VA_ARGS__)

#endif