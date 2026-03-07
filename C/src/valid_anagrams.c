/*
Given two strings s and t, return true if the two strings are anagrams of each other, otherwise return false.

An anagram is a string that contains the exact same characters as another string, but the order of the characters can be
different.

Example 1:

Input: s = "racecar", t = "carrace"

Output: true

Example 2:

Input: s = "jar", t = "jam"

Output: false

Constraints:

    s and t consist of lowercase English letters.
*/

#include <assert.h>
#include <hashmap.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int letter;
    int count;
} anagram_count;

int anagram_count_compare(const void *a, const void *b, void *udata)
{
    (void) udata;
    const anagram_count *pa = a;
    const anagram_count *pb = b;
    return pa->letter - pb->letter;
}

uint64_t anagram_count_hash(const void *item, uint64_t seed0, uint64_t seed1)
{
    const anagram_count *pitem = item;
    return hashmap_sip(&pitem->letter, sizeof(char), seed0, seed1);
}

static void increment_count_or_put(struct hashmap* map, char letter)
{
    anagram_count *found = (anagram_count *)hashmap_get(map, &(anagram_count){.letter = (int) letter});

    if (found != NULL)
    {
        found->count++;
    }
    else
    {
        hashmap_set(map, &(anagram_count){.count = 1, .letter = letter});
    }
}

bool is_anagram(char *s, char *t)
{
    if (strlen(s) != strlen(t))
        return false;

    struct hashmap *s_map =
        hashmap_new(sizeof(anagram_count), 0, 0, 0, anagram_count_hash, anagram_count_compare, NULL, NULL);
    struct hashmap *t_map =
        hashmap_new(sizeof(anagram_count), 0, 0, 0, anagram_count_hash, anagram_count_compare, NULL, NULL);

    size_t i = 0;
    while (s[i])
    {
        increment_count_or_put(s_map, s[i]);
        i++;
    }
    i = 0;
    while (t[i])
    {
        increment_count_or_put(t_map, t[i]);
        i++;
    }
    size_t iter = 0;
    void *item;
    bool different_match = false;
    while (!different_match && hashmap_iter(s_map, &iter, &item))
    {
        const anagram_count *s_ac = item;
        const anagram_count *t_ac = hashmap_get(t_map, &(anagram_count){.letter = s_ac->letter});
        if (t_ac == NULL || s_ac->count != t_ac->count)
        {
            different_match = true;
        }
        hashmap_delete(t_map, &(anagram_count){.letter = s_ac->letter});
        hashmap_delete(s_map, &(anagram_count){.letter = s_ac->letter});
    }

    hashmap_free(s_map);
    hashmap_free(t_map);

    return !different_match;
}

int main()
{
    char s1[] = "racecar";
    char t1[] = "carrace";
    printf("is_anagram(%s, %s); expect true\n", s1, t1);
    assert(is_anagram(s1, t1));

    char s2[] = "jar";
    char t2[] = "jam";
    printf("is_anagram(%s, %s); expect false\n", s2, t2);
    assert(!is_anagram(s2, t2));

    printf("is_anagram(%s, %s); expect false\n", s1, t2);
    assert(!is_anagram(s1, t2));

    return 0;
}
