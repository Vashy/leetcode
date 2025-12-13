const std = @import("std");
const testing = std.testing;
const debug = std.debug;

pub fn binarySearch(arr: []const i32, value: i32) ?usize {
    if (arr.len == 0) {
        return null;
    }
    var low: usize = 0;
    var high: usize = arr.len - 1;
    while (low <= high) {
        const mid: usize = low + (high - low) / 2;
        if (arr[mid] == value) {
            return mid;
        }

        if (value < arr[mid]) {
            if (mid == 0) break;
            high = mid - 1;
        } else if (value > arr[mid]) {
            low = mid + 1;
        }
    }
    return null;
}

test "30 in [0 2 2 30 40] -> 3" {
    const search_arr = [_]i32{ 0, 2, 2, 30, 40 };
    const result = binarySearch(&search_arr, 30).?;
    try testing.expect(result == 3);
}

test "1 in [1] -> 0" {
    const search_arr = [_]i32{1};
    const result = binarySearch(&search_arr, 1).?;
    try testing.expect(result == 0);
}

test "1 in [2, 3, 4] -> null" {
    const search_arr = [_]i32{ 2, 3, 4 };
    const result = binarySearch(&search_arr, 1);
    try testing.expect(result == null);
}

test "5 in [5, 7, 10, 10, 15] -> 0" {
    const search_arr = [_]i32{ 5, 7, 10, 10, 15 };
    const result = binarySearch(&search_arr, 5).?;
    try testing.expect(result == 0);
}

test "50 in [5, 7, 10, 10, 15, 50] -> 5" {
    const search_arr = [_]i32{ 5, 7, 10, 10, 15, 50 };
    const result = binarySearch(&search_arr, 50).?;
    try testing.expect(result == 5);
}
