/// Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to target.
///
/// You may assume that each input would have exactly one solution, and you may not use the same element twice.
///
/// You can return the answer in any order.
/// Example 1:
///
/// Input: nums = [2,7,11,15], target = 9
/// Output: [0,1]
/// Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
///
/// Example 2:
///
/// Input: nums = [3,2,4], target = 6
/// Output: [1,2]
///
/// Example 3:
///
/// Input: nums = [3,3], target = 6
/// Output: [0,1]
///
const std = @import("std");

pub fn twoSumBruteforce(nums: []const i32, target: i32) !struct { i32, i32 } {
    for (nums, 0..) |value, i| {
        for (nums[i + 1 ..], i + 1..) |next_value, j| {
            if (value + next_value == target) {
                return .{ i, j };
            }
        }
    }
    unreachable;
}

pub fn twoSum(allocator: std.mem.Allocator, nums: []const i32, target: i32) !struct { usize, usize } {
    var complement_map = std.AutoHashMap(i32, usize).init(allocator);
    defer complement_map.deinit();

    for (nums, 0..) |value, i| {
        if (complement_map.get(target - value)) |complement_index| {
            return .{ complement_index, i };
        }
        try complement_map.put(value, i);
    }
    unreachable;
}

test "9 in [2, 7, 11, 15] -> {0, 1}" {
    const arr = [_]i32{ 2, 7, 11, 15 };
    const first, const second = try twoSum(std.testing.allocator, &arr, 9);
    try std.testing.expect(first == 0);
    try std.testing.expect(second == 1);
}

test "6 in [3, 2, 4] -> {1, 2}" {
    const arr = [_]i32{ 3, 2, 4 };
    const first, const second = try twoSum(std.testing.allocator, &arr, 6);
    try std.testing.expect(first == 1);
    try std.testing.expect(second == 2);
}

test "6 in [3, 3] -> {0, 1}" {
    const arr = [_]i32{ 3, 3 };
    const first, const second = try twoSum(std.testing.allocator, &arr, 6);
    try std.testing.expect(first == 0);
    try std.testing.expect(second == 1);
}

test "17 in [5, 2, 7, 13, 12, 29, 7] -> {0, 4}" {
    const arr = [_]i32{ 5, 2, 7, 13, 12, 29, 7 };
    const first, const second = try twoSum(std.testing.allocator, &arr, 17);
    try std.testing.expect(first == 0);
    try std.testing.expect(second == 4);
}
