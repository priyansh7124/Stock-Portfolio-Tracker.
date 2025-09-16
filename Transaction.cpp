#include "Transaction.h"
#include <iomanip>

Transaction::Transaction(const std::string& symbol, TransactionType t, int qty, double price)
    : stock_symbol(symbol), type(t), quantity(qty), price_per_share(price) {
    timestamp = std::chrono::system_clock::now();
    total_value = quantity * price_per_share;
}

std::string Transaction::getTypeString() const {
    return (type == TransactionType::BUY) ? "BUY" : "SELL";
}

void Transaction::displayTransaction() const {
    std::cout << std::fixed << std::setprecision(2);
    
    auto time_t = std::chrono::system_clock::to_time_t(timestamp);
    std::cout << "Transaction: " << getTypeString() << " " << quantity 
              << " shares of " << stock_symbol 
              << " at $" << price_per_share 
              << " (Total: $" << total_value << ")\n";
    
    std::cout << "Date: " << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S") << "\n";
    std::cout << "------------------------\n";
}

bool Transaction::operator<(const Transaction& other) const {
    return this->timestamp < other.timestamp;
}

bool Transaction::operator>(const Transaction& other) const {
    return this->timestamp > other.timestamp;
}
