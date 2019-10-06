/*
 * gcc -trigraphs -o trigraph trigraph.c
 * This may looks like a joke, but it is not.
 * All occurrences of sequences ??<, ??>, ??(, ??), ??=, ??/, ??!, ??', ??- in a
 * source file are converted to one of characters { } [ ] # / | ^ ~.
 * So don't be surprised. As an aside, tokens <: :> <% %> %: behave as [ ] { } #
 * and ## (but the conversion is not performed in strings).
 */

??=include<stdio.h>

int main(void)
??<
    printf("Hello, World!??/n");

    return 0;
??>
