#pragma once

#define URGENCY_NORMAL 0
#define URGENCY_WARN 1
#define URGENCY_ERR 2
#define URGENCY_CRITICAL 3

void info(char *format, ...);
void warn(char *format, ...);
void err(char *format, ...);
void critical(char *format, ...);