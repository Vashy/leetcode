/* Top K Frequent Elements
https://neetcode.io/problems/top-k-elements-in-list/question?list=blind75

Given an integer array nums and an integer k, return the k most frequent elements within the array.

The test cases are generated such that the answer is always unique.

You may return the output in any order.

Example 1:
Input: nums = [1,2,2,3,3,3], k = 2
Output: [2,3]

Example 2:
Input: nums = [7,7], k = 1
Output: [7]

Constraints:
    1 <= nums.length <= 10^4.
    -1000 <= nums[i] <= 1000
    1 <= k <= number of distinct elements in nums.

vector<int> topKFrequent(vector<int>& nums, int k) {

}
*/

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct {
    int32_t value;
    uint32_t freq;
} frequency;

typedef struct {
    size_t count;
    size_t capacity;
    frequency* elems;
} array_frequency;

typedef struct {
    size_t count;
    size_t capacity;
    int32_t* elems;
} array_int;

#define array_init(arr, initial_capacity) \
    do { \
        assert((arr) != NULL); \
        assert((initial_capacity) > 0); \
        (arr)->elems = malloc((initial_capacity) * sizeof((arr)->elems[0])); \
        (arr)->capacity = (initial_capacity); \
        (arr)->count = 0; \
    } while (0)

#define array_free(arr) \
    do { \
        assert((arr) != NULL && (arr)->elems != NULL); \
        free((arr)->elems); \
        (arr)->count = 0; \
        (arr)->capacity = 0; \
        (arr)->elems = NULL; \
    } while (0)

#define array_push(arr, value) \
    do { \
        assert((arr) != NULL && (arr)->elems != NULL); \
        if ((arr)->count == (arr)->capacity) \
        { \
            (arr)->capacity *= 2; \
            (arr)->elems = realloc((arr)->elems, (arr)->capacity * sizeof((arr)->elems[0])); \
        } \
        (arr)->elems[(arr)->count] = value; \
        (arr)->count++; \
    } while (0)

frequency frequency_array_get(array_frequency* arr, size_t index)
{
    assert(arr != NULL && arr->elems != NULL);
    assert(index < arr->count);
    return arr->elems[index];
}

#define array_print(arr, type, printstm) \
    do { \
        assert((arr) != NULL && (arr)->elems != NULL); \
        printf("["); \
        for (size_t i = 0; i < (arr)->count; ++i) \
        { \
            if (i > 0) printf(", "); \
            type element = (arr)->elems[i]; \
            (printstm); \
        } \
        printf("]\n"); \
    } while (0)

#define array_push_all(arr, type, ...) \
    do { \
        type temp[] = { __VA_ARGS__ }; \
        size_t count = sizeof(temp) / sizeof(temp[0]); \
        for (size_t i = 0; i < count; ++i) \
            array_push((arr), temp[i]); \
    } while (0)

array_int* topk_frequent(array_int* nums, uint32_t k)
{
    assert(k > 0);
    uint32_t freq[2000] = {0}; // PRE: nums[i] in (-1000..=1000)
    uint32_t offset = 1000;

    array_int* result = malloc(sizeof(array_int));
    array_init(result, 1);
    uint32_t max_freq = 0;
    for (size_t i = 0; i < nums->count; ++i)
    {
        int32_t current_num = nums->elems[i];
        assert(current_num >= -1000 && current_num <= 1000);
        size_t offset_index = current_num + offset;
        freq[offset_index]++;
        uint32_t current_freq = freq[offset_index];
        if (max_freq < current_freq) {
            max_freq = current_freq;
        }
    }

    size_t k_max_count = max_freq + 1;
    array_int k_max[k_max_count];
    for (size_t i = 0; i < k_max_count; ++i)
    {
        array_init(&k_max[i], 1);
    }

    for (size_t i = 0; i < sizeof(freq) / sizeof(freq[0]); ++i)
    {
        uint32_t current_num_frequency = freq[i];
        int32_t current_num = (int) i - offset;
        if (current_num_frequency > 0) {
            assert(current_num_frequency <= max_freq);
            array_push(&k_max[current_num_frequency], current_num);
        }
    }

    for (size_t i = max_freq; i > 0 && result->count < k; --i)
    {
        array_int current_value = k_max[i];
        for (size_t j = 0; j < current_value.count && result->count < k; j++) {
            array_push(result, current_value.elems[j]);
        }
    }

    for (size_t i = 0; i < k_max_count; ++i)
    {
        array_free(&k_max[i]);
    }

    return result;
}

int main(int argc, char** argv)
{
    if (argc <= 2) {
        fprintf(stderr, "usage: %s {k} ...NUMS\n", argv[0]);
        return 1;
    }
    array_int input_arr = {0};
    array_init(&input_arr, argc - 2);

    uint32_t k = atoi(argv[1]);
    for (int i = 2; i < argc; i++)
        array_push(&input_arr, atoi(argv[i]));

    printf("k=%u, input_arr=", k);
    array_print(&input_arr, int32_t, printf("%d", element));
    array_int* result = topk_frequent(&input_arr, k);
    printf("result_arr=");
    array_print(result, int32_t, printf("%d", element));
    array_free(result);
    free(result);
    array_free(&input_arr);
    return 0;
}
