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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_anagram(char *s, char *t)
{
    assert(false);
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
