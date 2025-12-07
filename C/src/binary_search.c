#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool binary_search(int ordered_array[], size_t size, int value_to_search)
{
    if (size == 0)
        return false;
    size_t low = 0;
    size_t high = size - 1;

    while (low <= high)
    {
        size_t mid = low + (high - low) / 2;
        int mid_value = ordered_array[mid];

        if (mid_value == value_to_search)
            return true;

        if (value_to_search < mid_value)
            high = mid - 1;
        else if (value_to_search > mid_value)
            low = mid + 1;
    }
    return false;
}

void run_test(int arr[], size_t size, int value_to_search, bool expected_outcome)
{
    static int test_count = 0;
    printf("\n---\n");
    bool res_1 = binary_search(arr, size, value_to_search);
    printf("res_%d: %d\n", test_count++, res_1);
    assert(res_1 == expected_outcome);
}

int main()
{
    int arr_1[] = {1, 2, 3, 4};
    run_test(arr_1, sizeof(arr_1) / sizeof(int), 3, true);

    int arr_2[] = {1, 2, 3, 5, 6};
    run_test(arr_2, sizeof(arr_2) / sizeof(int), 4, false);

    int arr_3[] = {1, 2, 3, 5, 6};
    run_test(arr_3, sizeof(arr_3) / sizeof(int), 4, false);

    int arr_4[] = {4, 4, 4, 4, 4};
    run_test(arr_4, sizeof(arr_4) / sizeof(int), 5, false);

    int arr_5[] = {4, 4, 5, 5, 6, 6};
    run_test(arr_5, sizeof(arr_5) / sizeof(int), 5, true);

    int *arr_6 = malloc(4);
    run_test(arr_6, 0, 5, false);
    free(arr_6);

    int arr_7[] = {4};
    run_test(arr_7, sizeof(arr_7) / sizeof(int), 4, true);

    int arr_8[] = {4, 5};
    run_test(arr_8, sizeof(arr_8) / sizeof(int), 5, true);
}
