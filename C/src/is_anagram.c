#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define ASCII_SIZE 256

bool is_anagram(char* a, char* b)
{
    assert(a != NULL && b != NULL);
    if (strlen(a) != strlen(b))
        return false;

    int32_t entries[ASCII_SIZE] = {0};

    size_t i = 0;
    while (a[i])
    {
        int letter = (int) a[i];
        entries[letter]++;
        i++;
    }
    i = 0;
    while (b[i])
    {
        int letter = (int) b[i];
        entries[letter]--;
        i++;
    }

    for (size_t i = 0; i < ASCII_SIZE; i++)
    {
        if (entries[i] != 0)
            return false;
    }
    return true;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("usage: %s racecar carrace\n", argv[0]);
        return 1;
    }

    char* a_word = argv[1];
    char* b_word = argv[2];

    if (is_anagram(a_word, b_word))
        printf("%s and %s are anagrams\n", a_word, b_word);
    else
        printf("%s and %s are not anagrams\n", a_word, b_word);
    return 0;
}
