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

public:
    // Constructor
    Transaction(const std::string& symbol, TransactionType t, int qty, double price);
     // Getters
    std::string getStockSymbol() const { return stock_symbol; }
    TransactionType getType() const { return type; }
    int getQuantity() const { return quantity; }
    double getPricePerShare() const { return price_per_share; }
    double getTotalValue() const { return total_value; }
    std::chrono::system_clock::time_point getTimestamp() const { return timestamp; }
      // Utility
    void displayTransaction() const;
    std::string getTypeString() const;
    // For sorting transactions by date
    bool operator<(const Transaction& other) const;
    bool operator>(const Transaction& other) const;
};
#endif