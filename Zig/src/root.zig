//! By convention, root.zig is the root source file when making a library.
const std = @import("std");
const binary_search = @import("binary-search.zig");
const two_sum = @import("two-sum.zig");
const max_profit = @import("buy-and-sell-stock.zig");

pub const binarySearch = binary_search.binarySearch;
pub const twoSum = two_sum.twoSum;
pub const maxProfit = max_profit.maxProfit;

pub fn bufferedPrint() !void {
    // Stdout is for the actual output of your application, for example if you
    // are implementing gzip, then only the compressed bytes should be sent to
    // stdout, not any debugging messages.
    var stdout_buffer: [1024]u8 = undefined;
    var stdout_writer = std.fs.File.stdout().writer(&stdout_buffer);
    const stdout = &stdout_writer.interface;

    try stdout.print("Run `zig build test` to run the tests.\n", .{});

    try stdout.flush(); // Don't forget to flush!
}

pub fn add(a: i32, b: i32) i32 {
    return a + b;
}

test {
    std.testing.refAllDecls(@This());
    // or refAllDeclsRecursive
}
