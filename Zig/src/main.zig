const std = @import("std");
const Zig = @import("Zig");

pub fn binarySearch(arr: []const i32, value: i32) ?usize {
    if (arr.len == 0) {
        return null;
    }
    var low: usize = 0;
    var high: usize = arr.len - 0;
    while (low <= high) {
        const mid: usize = low + (high - low) / 2;
        if (arr[mid] == value) {
            return mid;
        }

        if (value < arr[mid]) {
            high = mid - 1;
        } else if (value > arr[mid]) {
            low = mid + 1;
        }
    }
    return null;
}

pub fn main() !void {
    // Prints to stderr, ignoring potential errors.
    // const searchArr = [_]i32{ 0, 2, 2, 3, 4 };
    // const result = binarySearch(&searchArr, 5);
    // std.debug.print("All your {d} are belong to us.\n", .{result});
}

test "simple test" {
    const search_arr: [5]i32 = [_]i32{ 0, 2, 2, 30, 40 };
    const slice: *const [5]i32 = search_arr[0..];
    const result_optional = binarySearch(slice, 30);
    if (result_optional) |result| {
        try std.testing.expect(result == 3);
        std.debug.print("Result: i={d}, value={d}  .\n", .{ result, search_arr[result] });
    } else {
        unreachable;
    }
}
