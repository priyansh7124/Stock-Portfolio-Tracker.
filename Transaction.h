#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <chrono>
#include <iostream>

enum class TransactionType {
    BUY,
    SELL
};


class Transaction {
private:
    std::string stock_symbol;
    TransactionType type;
    int quantity;
    double price_per_share;
    std::chrono::system_clock::time_point timestamp;
    double total_value;
};
#endif