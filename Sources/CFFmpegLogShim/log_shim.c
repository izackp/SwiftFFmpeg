#include "CFFmpegLogShim.h"
#include <libavutil/log.h>
#include <stdio.h>
#include <string.h>

static void (*g_swift_callback)(int level, const char *line) = NULL;

static void ffmpeg_log_callback(void *avcl, int level, const char *fmt, va_list vl) {
    if (!g_swift_callback) return;

    char line[1024];
    int print_prefix = 1;
    av_log_format_line(avcl, level, fmt, vl, line, sizeof(line), &print_prefix);

    // Strip trailing newline — callers can add their own.
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0';

    g_swift_callback(level, line);
}

void swift_av_log_set_callback(void (*callback)(int level, const char *line)) {
    g_swift_callback = callback;
    av_log_set_callback(ffmpeg_log_callback);
}

void swift_av_log_unset_callback(void) {
    g_swift_callback = NULL;
    av_log_set_callback(av_log_default_callback);
}
