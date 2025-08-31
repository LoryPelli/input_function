#include <stdio.h>

#include "input.h"

int main(void) {
    c_config();
    str string = s_in("Inserisci una stringa: ");
    printf("%s\n", string);
    printf("Length: %zu\n", len(string));
    char character = c(s_in("Inserisci un carattere: "));
    printf("%c\n", character);
    int integer_number = i(s_in("Inserisci un numero (intero): "));
    printf("%d\n", integer_number);
    float floating_number = f(s_in("Inserisci un numero (decimale): "));
    printf("%f\n", floating_number);
    double double_number = d(s_in("Inserisci un numero (decimale doppio): "));
    printf("%lf\n", double_number);
    long long_number = l(s_in("Inserisci un numero (intero lungo): "));
    printf("%ld\n", long_number);
    long long long_long_number = ll(s_in("Inserisci un numero (intero lungo lungo): "));
    printf("%lld\n", long_long_number);
    bool valid = v_str("Test di validazione!", NULL);
    if (valid) {
        printf("Validazione passata!\n");
    } else {
        printf("Validazione non passata\n");
    }
    bool valid2 = v_str("Test di validazione!", "Messaggio personalizzato: ");
    if (valid2) {
        printf("Validazione passata!\n");
    } else {
        printf("Validazione non passata\n");
    }
    str file_string = f_in("test.txt");
    printf("%s\n", file_string);
    printf("Length: %zu\n", len(file_string));
    char file_character = c(file_string);
    printf("%c\n", file_character);
    int p = i(s_in("Inserisci la posizione del carattere: "));
    char r = c(s_in("Inserisci il carattere da rimpiazzare: "));
    c_str(string, p, r);
    printf("%s\n", string);
    int n = i(s_in("Inserisci la lunghezza dell'array: "));
    int int_arr[n];
    for (int j = 0; j < n; j++) {
        int_arr[j] = i(s_in("Inserisci l'elemento %d: ", j + 1));
        printf("%d\n", int_arr[j]);
    }
    file_string = f_in("test_line.txt");
    str line = ln(file_string);
    printf("%s\n", line);
    line = ln(file_string);
    printf("%s\n", line);
    line = ln(file_string);
    printf("%s\n", line);
    f_cat("concat.txt", 3, '\n', "f1.txt", "f2.txt", "f3.txt");
    f_cpy("src.txt", "dest.txt");
    r = c(s_in("Inserisci il carattere da ripetere: "));
    n = i(s_in("Inserisci quante volte ripeterlo: "));
    f_repeat("repeat.txt", r, n, false);
    str new_content = f_replace("replace.txt", '!', '.');
    printf("%s\n", new_content);
    bool b = b_in("Sei sicuro? ");
    if (b) {
        printf("L'utente ha risposto di sì\n");
    } else {
        printf("L'utente ha risposto di no\n");
    }
    n = i(s_in("Inserisci la lunghezza dell'array: "));
    str str_arr[n];
    for (int j = 0; j < n; j++) {
        b = b_in("Vuoi inserire l'elemento %d? ", j + 1);
        if (b) {
            str_arr[j] = s_in("Inserisci l'elemento %d: ", j + 1);
        } else {
            str_arr[j] = "";
        }
        printf("%s\n", str_arr[j]);
    }
    size_t c = sel_in(3, NULL, "Prima opzione", "Seconda opzione", "Terza opzione");
    switch (c) {
        case 1: {
            printf("Hai scelto la prima opzione\n");
            break;
        }
        case 2: {
            printf("Hai scelto la seconda opzione\n");
            break;
        }
        case 3: {
            printf("Hai scelto la terza opzione\n");
            break;
        }
    }
    c = sel_in(3, "Seleziona un'opzione > ", "Prima opzione", "Seconda opzione", "Terza opzione");
    switch (c) {
        case 1: {
            printf("Hai scelto la prima opzione\n");
            break;
        }
        case 2: {
            printf("Hai scelto la seconda opzione\n");
            break;
        }
        case 3: {
            printf("Hai scelto la terza opzione\n");
            break;
        }
    }
    return 0;
}