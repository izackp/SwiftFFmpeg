#ifndef CFFMPEG_LOG_SHIM_H
#define CFFMPEG_LOG_SHIM_H

#ifdef __cplusplus
extern "C" {
#endif

/// Set a Swift-compatible log callback. The callback receives a fully
/// formatted, null-terminated log line (no va_list). Pass NULL to restore
/// FFmpeg's default stderr callback.
void swift_av_log_set_callback(void (*callback)(int level, const char *line));

/// Restore FFmpeg's default stderr callback.
void swift_av_log_unset_callback(void);

#ifdef __cplusplus
}
#endif

#endif /* CFFMPEG_LOG_SHIM_H */
