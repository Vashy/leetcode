
/*
 https://neetcode.io/problems/duplicate-integer/question?list=neetcode150

 Given an integer array nums, return true if any value appears more than once
 in the array, otherwise return false.

 Examples

 Input: nums = [1, 2, 3, 3]
 Output: true

 Input: nums = [1, 2, 3, 4]

 Output: false

 Recommended Time & Space Complexity
 - You should aim for a solution with O(n) time and O(n) space, where n is the size of the input array.

*/

#include "hashset.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define HASH_SET_SIZE 1024
#define TEST1 1
#define TEST2 1
#define TEST3 1
#define TEST4 1

bool has_duplicate_Onxn(int *nums, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (i == j)
                continue;

            if (nums[i] == nums[j])
            {
                return true;
            }
        }
    }
    return false;
}

bool has_duplicate(int *nums, size_t size)
{
    struct IntHashSet *hash_set = inthashset_create(HASH_SET_SIZE);
    bool found_duplicate = false;
    for (size_t i = 0; i < size; i++)
    {
        int num_outer = nums[i];
        bool value_exists = inthashset_contains(hash_set, num_outer);
        if (value_exists)
        {
            found_duplicate = true;
            break;
        }
        inthashset_put(hash_set, num_outer);
    }

    inthashset_destroy(hash_set);

    return found_duplicate;
}

char *to_str(bool value)
{
    if (value)
    {
        return "true";
    }
    return "false";
}

void print_arr(int *arr, size_t size)
{
    printf("[ ");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

int main()
{
    size_t count = 4;
#ifdef TEST1
    int with_duplicate[] = {1, 2, 3, 3};
    print_arr(with_duplicate, count);
    bool result_1 = has_duplicate(with_duplicate, count);
    printf("result_1: %s\n\n\n", to_str(result_1));
    assert(result_1 == true);
#endif /* ifndef TEST1 */

#ifdef TEST2
    count = 4;
    int without_duplicate[] = {1, 2, 3, 4};
    print_arr(without_duplicate, count);
    bool result_2 = has_duplicate(without_duplicate, count);
    printf("result_2: %s\n\n\n", to_str(result_2));
    assert(result_2 == false);
#endif /* ifndef TEST2 */

#ifdef TEST3
    count = 18;
    int tricky_one[] = {
        1, 3, 10, 9, 6, 5, 7, 8, 12, 14, 15, 20, 19, 18, 17, 4, HASH_SET_SIZE + 1, HASH_SET_SIZE * 2 + 1};
    print_arr(tricky_one, count);
    bool result_3 = has_duplicate(tricky_one, count);
    printf("result_3: %s\n\n\n", to_str(result_3));
    assert(result_3 == false);
#endif /* ifndef TEST3 */

#ifdef TEST4
    count = 18;
    int tricky_two[] = {1, 3, 10, 9, 6, 5, 7, 8, 12, 14, 15, 20, 19, 18, 17, 4, HASH_SET_SIZE + 1, 20};
    print_arr(tricky_two, count);
    bool result_4 = has_duplicate(tricky_two, count);
    printf("result_4: %s\n\n\n", to_str(result_4));
    assert(result_4 == true);
#endif /* ifndef TEST4 */

    return 0;
}
