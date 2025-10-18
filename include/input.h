#ifndef INPUT_H
#define INPUT_H

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

bool v_str(str, str);
str ln(str);
size_t len(str);
void c_str(str, size_t, char);
void f_cat(str, size_t, char, str, ...);
void f_cpy(str, str);
void f_repeat(str, char, size_t, bool);
void c_config(void);
str f_replace(str, char, char);
str in(str, str, ...);
size_t sel_in(size_t, str, str, ...);
char c(str);
int i(str);
long l(str);
long long ll(str);
float f(str);
double d(str);

#endif /* INPUT_H */