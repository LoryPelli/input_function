#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "input.h"

#ifdef __has_include
#if __has_include("config.h")
#include "config.h"
#ifndef SUPPRESS_WARNINGS
#warning Define SUPPRESS_WARNINGS in the config.h header file to disable warnings
#endif
#else
#warning Create config.h header file and define SUPPRESS_WARNINGS to disable warnings
#endif
#else
#ifndef SUPPRESS_WARNINGS
#warning Define SUPPRESS_WARNINGS to disable warnings
#endif
#endif

static const str config = "#ifndef CONFIG_H\n"
                          "#define CONFIG_H\n"
                          "\n"
                          "#define SUPPRESS_WARNINGS\n"
                          "\n"
                          "#endif /* CONFIG_H */";

static str string = NULL;

static size_t position = 0;

static str input(const str fname, str m, const va_list args) {
    FILE *f = fopen(fname, "r");
    if (m && f) {
        #ifndef SUPPRESS_WARNINGS
        printf("You provided a file and a message, but the message will be ignored\n");
        printf("Use SUPPRESS_WARNINGS macro to disable warnings\n");
        #endif
    } else if (!m && !f) {
        #ifndef SUPPRESS_WARNINGS
        printf("Message is NULL, default one will be used instead\n");
        printf("Use SUPPRESS_WARNINGS macro to disable warnings\n");
        #endif
        m = "Enter Something: ";
    }
    if (!f) {
        #ifndef SUPPRESS_WARNINGS
        printf("File is NULL, stdin will be used instead\n");
        printf("Use SUPPRESS_WARNINGS macro to disable warnings\n");
        #endif
        f = stdin;
        vprintf(m, args);
    }
    size_t buffer_size = 4;
    str buffer = malloc(sizeof(char) * buffer_size);
    if (!buffer) {
        fprintf(stderr, "Buffer is NULL\n");
        free(buffer);
        buffer = NULL;
        return "";
    }
    int c = fgetc(f);
    size_t i = 0;
    for (i = 0; f == stdin ? c != '\n' : !feof(f); i++) {
        buffer[i] = c;
        if (i >= buffer_size - 1) {
            buffer_size *= 2;
            const str temp_buffer = realloc(buffer, sizeof(char) * buffer_size);
            if (!temp_buffer) {
                fprintf(stderr, "Buffer is NULL\n");
                free(buffer);
                buffer = NULL;
                return "";
            }
            buffer = temp_buffer;
        }
        c = fgetc(f);
    }
    buffer[i] = '\0';
    if (f != stdin) {
        fclose(f);
    }
    return buffer;
}

bool v_str(const str v, str m) {
    if (!v) {
        fprintf(stderr, "Value is NULL\n");
        return false;
    }
    if (!m) {
        #ifndef SUPPRESS_WARNINGS
        printf("Message is NULL, default one will be used instead\n");
        printf("Use SUPPRESS_WARNINGS macro to disable warnings\n");
        #endif
        m = "Enter Something: ";
    }
    str s = s_in(m);
    const size_t l = len(s);
    if (l <= 0) {
        fprintf(stderr, "Length is zero or less than zero\n");
        free(s);
        s = NULL;
        return false;
    }
    for (size_t i = 0; i < l; i++) {
        if (s[i] != v[i]) {
            free(s);
            s = NULL;
            return false;
        }
    }
    free(s);
    s = NULL;
    return true;
}

str ln(const str s) {
    if (!s) {
        fprintf(stderr, "String is NULL\n");
        return "";
    }
    if (string && s != string) {
        #ifndef SUPPRESS_WARNINGS
        printf("You provided a string that is different from the one you started the function with, position will be set back to 0\n");
        printf("Use SUPPRESS_WARNINGS macro to disable warnings\n");
        #endif
        position = 0;
    }
    size_t buffer_size = 4;
    str buffer = malloc(sizeof(char) * buffer_size);
    if (!buffer) {
        fprintf(stderr, "Buffer is NULL\n");
        free(buffer);
        buffer = NULL;
        return "";
    }
    size_t i = 0;
    for (i = 0; s[i + position] != '\n' && s[i + position]; i++) {
        buffer[i] = s[i + position];
        if (i >= buffer_size - 1) {
            buffer_size *= 2;
            const str temp_buffer = realloc(buffer, sizeof(char) * buffer_size);
            if (!temp_buffer) {
                fprintf(stderr, "Buffer is NULL\n");
                free(buffer);
                buffer = NULL;
                return "";
            }
            buffer = temp_buffer;
        }
    }
    if (!s[i + position]) {
        position = 0;
        string = NULL;
    } else if (!string) {
        position += i + 1;
        string = s;
    }
    buffer[i] = '\0';
    return buffer;
}

size_t len(const str s) {
    size_t i;
    for (i = 0; s[i]; i++) {}
    return i;
}

void c_str(const str s, const size_t p, const char c) {
    if (!s) {
        fprintf(stderr, "String is NULL\n");
        return;
    }
    s[p] = c;
}

void f_cat(const str cname, const size_t n, const char sep, str fname, ...) {
    va_list args;
    if (!fname) {
        fprintf(stderr, "File name is NULL\n");
        return;
    }
    va_start(args, fname);
    FILE *f = fopen(fname, "r");
    if (!f) {
        fprintf(stderr, "File is NULL\n");
        return;
    }
    size_t j = 0;
    size_t buffer_size = 4;
    str buffer = malloc(sizeof(char) * buffer_size);
    if (!buffer) {
        fprintf(stderr, "Buffer is NULL\n");
        free(buffer);
        buffer = NULL;
        return;
    }
    for (size_t i = 0; j < n; i++) {
        const int c = fgetc(f);
        buffer[i] = c != EOF ? c : j < n - 1 ? sep : '\0';
        if (i >= buffer_size - 1) {
            buffer_size *= 2;
            const str temp_buffer = realloc(buffer, sizeof(char) * buffer_size);
            if (!temp_buffer) {
                fprintf(stderr, "Buffer is NULL\n");
                free(buffer);
                buffer = NULL;
                return;
            }
            buffer = temp_buffer;
        }
        if (feof(f)) {
            fclose(f);
            fname = va_arg(args, str);
            f = fopen(fname, "r");
            if (!f && j < n - 1) {
                fprintf(stderr, "File is NULL\n");
                free(buffer);
                buffer = NULL;
                return;
            }
            j++;
        }
    }
    FILE *out = fopen(cname, "w");
    if (!out) {
        fprintf(stderr, "File is NULL\n");
        free(buffer);
        buffer = NULL;
        return;
    }
    fputs(buffer, out);
    fclose(out);
    va_end(args);
    free(buffer);
    buffer = NULL;
}

void f_cpy(const str src, const str dest) {
    FILE *in = fopen(src, "r");
    if (!in) {
        fprintf(stderr, "File is NULL\n");
        return;
    }
    FILE *out = fopen(dest, "w");
    if (!out) {
        fprintf(stderr, "File is NULL\n");
        return;
    }
    while (!feof(in)) {
        const int c = fgetc(in);
        if (c != EOF) {
            fputc(c, out);
        }
    }
    fclose(in);
    fclose(out);
}

void f_repeat(const str fname, const char c, const size_t n, const bool b) {
    FILE *f;
    if (b) {
        f = fopen(fname, "w");
    }
    else {
        f = fopen(fname, "a");
    }
    if (!f) {
        #ifndef SUPPRESS_WARNINGS
        printf("File is NULL, stdout will be used instead\n");
        printf("Use SUPPRESS_WARNINGS macro to disable warnings\n");
        #endif
        f = stdout;
    }
    for (size_t i = 0; i < n; i++) {
        fputc(c, f);
    }
    if (f != stdout) {
        fclose(f);
    }
}

void c_config(void) {
    FILE *f = fopen("config.h", "w");
    if (!f) {
        fprintf(stderr, "File is NULL\n");
        return;
    }
    fputs(config, f);
    fclose(f);
}

str f_replace(const str fname, const char c, const char r) {
    FILE *f = fopen(fname, "r");
    if (!f) {
        fprintf(stderr, "File is NULL\n");
        return "";
    }
    int d = fgetc(f);
    size_t buffer_size = 4;
    str buffer = malloc(sizeof(char) * buffer_size);
    if (!buffer) {
        fprintf(stderr, "Buffer is NULL\n");
        free(buffer);
        buffer = NULL;
        return "";
    }
    size_t i = 0;
    for (i = 0; !feof(f); i++) {
        if (d == c) {
            buffer[i] = r;
        } else {
            buffer[i] = d;
        }
        if (i >= buffer_size - 1) {
            buffer_size *= 2;
            const str temp_buffer = realloc(buffer, sizeof(char) * buffer_size);
            if (!temp_buffer) {
                fprintf(stderr, "Buffer is NULL\n");
                free(buffer);
                buffer = NULL;
                return "";
            }
            buffer = temp_buffer;
        }
        d = fgetc(f);
    }
    buffer[i] = '\0';
    fclose(f);
    return buffer;
}

str in(const str fname, const str s, ...) {
    va_list args;
    va_start(args, s);
    const str res = input(fname, s, args);
    va_end(args);
    return res;
}

size_t sel_in(const size_t n, str m, str s, ...) {
    va_list args;
    if (!s) {
        fprintf(stderr, "String is NULL\n");
        return 0;
    }
    va_start(args, s);
    if (!m) {
        #ifndef SUPPRESS_WARNINGS
        printf("Message is NULL, default one will be used instead\n");
        printf("Use SUPPRESS_WARNINGS macro to disable warnings\n");
        #endif
        m = "Select > ";
    }
    for (size_t i = 0; i < n; i++) {
        printf("%zu: %s\n", i + 1, s);
        s = va_arg(args, str);
    }
    int c;
    do {
        c = i(s_in(m));
        if (c <= 0 || c > n) {
            printf("Selected option doesn't exists, please try again!\n");
        }
    } while (c <= 0 || c > n);
    va_end(args);
    return c;
}

char c(str s) {
    if (!s) {
        fprintf(stderr, "String is NULL\n");
        return '\0';
    }
    const char res = s[0];
    free(s);
    s = NULL;
    return res;
}

int i(str s) {
    if (!s) {
        fprintf(stderr, "String is NULL\n");
        return 0;
    }
    const int res = atoi(s);
    free(s);
    s = NULL;
    return res;
}

long l(str s) {
    if (!s) {
        fprintf(stderr, "String is NULL\n");
        return 0;
    }
    const long res = atol(s);
    free(s);
    s = NULL;
    return res;
}

long long ll(str s) {
    if (!s) {
        fprintf(stderr, "String is NULL\n");
        return 0;
    }
    const long long res = atoll(s);
    free(s);
    s = NULL;
    return res;
}

float f(str s) {
    if (!s) {
        fprintf(stderr, "String is NULL\n");
        return 0;
    }
    const float res = (float)atof(s);
    free(s);
    s = NULL;
    return res;
}

double d(str s) {
    if (!s) {
        fprintf(stderr, "String is NULL\n");
        return 0;
    }
    const double res = atof(s);
    free(s);
    s = NULL;
    return res;
}