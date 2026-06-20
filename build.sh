#!/bin/bash
LIBAVCODEC_MAJOR=$(pkg-config --modversion libavcodec 2>/dev/null | cut -d. -f1)
export LIBAVCODEC_MAJOR="${LIBAVCODEC_MAJOR:-0}"
OUTFILE=$(mktemp /tmp/build_output_XXXXXX.txt)
swift build --target SwiftFFmpeg >"$OUTFILE" 2>&1
STATUS=$?
grep -E "^/home/$(whoami)/Projects/SwiftFFmpeg/Sources/.*error:" "$OUTFILE" | sed "s|/home/$(whoami)/Projects/SwiftFFmpeg/||" | head -10
if [ $STATUS -eq 0 ]; then
    echo "Build succeeded."
else
    echo "Build FAILED. Full output: $OUTFILE"
fi
