#pragma once

#define DEFAULT_LOG info("Keyboard shortcuts: arrow keys -> cursor movement, i -> insert byte, del -> delete byte, s -> save")

#define LOG_RESERVED_SPACE 2

#define URGENCY_NORMAL 0
#define URGENCY_WARN 1
#define URGENCY_ERR 2
#define URGENCY_CRITICAL 3

void info(char *format, ...);
void warn(char *format, ...);
void err(char *format, ...);
void critical(char *format, ...);