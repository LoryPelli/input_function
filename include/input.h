#ifndef INPUT_H
#define INPUT_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#define f_in(f) in(f, NULL)

#define s_in(s, ...) in(NULL, s, ##__VA_ARGS__)

#define b_in(s, ...)                                 \
    ({                                               \
        char b = c(s_in(s "(y/N) ", ##__VA_ARGS__)); \
        b == 'y' || b == 'Y';                        \
    })

typedef char *str;

bool v_str(const str, str);
str ln(const str);
size_t len(const str);
void c_str(str, const size_t, const char);
void f_cat(const str, const size_t, const char, str, ...);
void f_cpy(const str, str);
void f_repeat(const str, const char, const size_t, const bool);
void c_config(void);
str f_replace(const str, const char, const char);
str in(const str, str, ...);
size_t sel_in(const size_t, str, str, ...);
char c(const str);
int i(const str);
long l(const str);
long long ll(const str);
float f(const str);
double d(const str);

#endif /* INPUT_H */