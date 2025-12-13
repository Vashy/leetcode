/// 121. Best Time to Buy and Sell Stock
///
/// You are given an array prices where prices[i] is the price of a given stock on the ith day.
///
/// You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
///
/// Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
const std = @import("std");

pub fn maxProfit(prices: []const i32) i32 {
    if (prices.len == 0) return 0;

    var max_profit: i32 = 0;
    var min_buy_value: i32 = prices[0];

    for (prices[1..]) |price| {
        if (price < min_buy_value) {
            min_buy_value = price;
        } else if (max_profit < price - min_buy_value) {
            max_profit = price - min_buy_value;
        }
    }
    return max_profit;
}

test "[5, 117, 1, 116] -> 115" {
    const array = [_]i32{ 5, 117, 1, 116 };
    const result = maxProfit(&array);
    try std.testing.expect(result == 116 - 1);
}

test "[7, 1, 5, 3, 6, 4] -> 5" {
    const array = [_]i32{ 7, 1, 5, 3, 6, 4 };
    const result = maxProfit(&array);
    try std.testing.expect(result == 6 - 1);
}

test "[7, 6, 4, 3, 1] -> 0" {
    const array = [_]i32{ 7, 6, 4, 3, 1 };
    const result = maxProfit(&array);
    try std.testing.expect(result == 0);
}

test "[] -> 0" {
    const array = [_]i32{};
    const result = maxProfit(&array);
    try std.testing.expect(result == 0);
}
