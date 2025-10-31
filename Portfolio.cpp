#include "Portfolio.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

Portfolio::Portfolio(const std::string& name, double initial_cash)
    : portfolio_name(name), cash_balance(initial_cash) {}

bool Portfolio::buyStock(const std::string& symbol, int quantity, double price) {
    double total_cost = quantity * price;
    
    if (total_cost > cash_balance) {
        std::cout << "Insufficient funds! Need $" << total_cost 
                  << ", but only have $" << cash_balance << std::endl;
        return false;
    }
    
    // Update cash balance
    cash_balance -= total_cost;
    
    // Update quantity (DSA: Hash table operation O(1))
    stock_quantities[symbol] += quantity;
    
    // Add transaction to history (DSA: Vector append)
    transaction_history.emplace_back(symbol, TransactionType::BUY, quantity, price);
    
    std::cout << "Successfully bought " << quantity << " shares of " << symbol 
              << " at $" << price << " each\n";
    return true;
}

bool Portfolio::sellStock(const std::string& symbol, int quantity, double price) {
    // Check if we own enough shares (DSA: Hash table lookup O(1))
    if (stock_quantities[symbol] < quantity) {
        std::cout << "Cannot sell " << quantity << " shares of " << symbol 
                  << ". Only own " << stock_quantities[symbol] << " shares.\n";
        return false;
    }
    
    double total_revenue = quantity * price;
    
    // Update cash balance
    cash_balance += total_revenue;
    
    // Update quantity
    stock_quantities[symbol] -= quantity;
    
    // Remove stock if quantity becomes 0
    if (stock_quantities[symbol] == 0) {
        stock_quantities.erase(symbol);
    }
    
    // Add transaction to history
    transaction_history.emplace_back(symbol, TransactionType::SELL, quantity, price);
    
    std::cout << "Successfully sold " << quantity << " shares of " << symbol 
              << " at $" << price << " each\n";
    return true;
}

void Portfolio::addStock(std::shared_ptr<Stock> stock) {
    // DSA: Hash table insertion O(1)
    stocks[stock->getSymbol()] = stock;
    updateSectorAllocation();
}

std::shared_ptr<Stock> Portfolio::findStock(const std::string& symbol) {
    // DSA: Hash table lookup O(1)
    auto it = stocks.find(symbol);
    return (it != stocks.end()) ? it->second : nullptr;
}

std::vector<std::shared_ptr<Stock>> Portfolio::getTopPerformers(int count) {
    // DSA: Using priority queue (max heap) for top performers
    std::priority_queue<std::shared_ptr<Stock>, 
                       std::vector<std::shared_ptr<Stock>>, 
                       StockPerformanceComparator> max_heap;
    
    // Add all owned stocks to heap
    for (const auto& pair : stocks) {
        if (stock_quantities.count(pair.first) > 0 && stock_quantities.at(pair.first) > 0) {
            max_heap.push(pair.second);
        }
    }
    
    std::vector<std::shared_ptr<Stock>> top_performers;
    int added = 0;
    
    while (!max_heap.empty() && added < count) {
        top_performers.push_back(max_heap.top());
        max_heap.pop();
        added++;
    }
    
    return top_performers;
}

std::vector<std::shared_ptr<Stock>> Portfolio::getWorstPerformers(int count) {
    // DSA: Using priority queue (min heap) for worst performers
    std::priority_queue<std::shared_ptr<Stock>, 
                       std::vector<std::shared_ptr<Stock>>, 
                       std::greater<std::shared_ptr<Stock>>> min_heap;
    
    for (const auto& pair : stocks) {
        if (stock_quantities.count(pair.first) > 0 && stock_quantities.at(pair.first) > 0) {
            min_heap.push(pair.second);
        }
    }
    
    std::vector<std::shared_ptr<Stock>> worst_performers;
    int added = 0;
    
    while (!min_heap.empty() && added < count) {
        worst_performers.push_back(min_heap.top());
        min_heap.pop();
        added++;
    }
    
    return worst_performers;
}

std::vector<std::shared_ptr<Stock>> Portfolio::getStocksBySector(const std::string& sector) {
    std::vector<std::shared_ptr<Stock>> sector_stocks;
    
    // DSA: Linear search through hash table
    for (const auto& pair : stocks) {
        if (pair.second->getSector() == sector && 
            stock_quantities.count(pair.first) > 0 && 
            stock_quantities.at(pair.first) > 0) {
            sector_stocks.push_back(pair.second);
        }
    }
    
    return sector_stocks;
}

double Portfolio::getTotalValue() const {
    double total = cash_balance;
    
    // Calculate value of all holdings
    for (const auto& pair : stock_quantities) {
        if (pair.second > 0) {
            auto stock_it = stocks.find(pair.first);
            if (stock_it != stocks.end()) {
                total += pair.second * stock_it->second->getCurrentPrice();
            }
        }
    }
    
    return total;
}

double Portfolio::getTotalGainLoss() const {
    double total_invested = 0.0;
    double current_value = 0.0;
    
    // Calculate based on transaction history
    for (const auto& transaction : transaction_history) {
        if (transaction.getType() == TransactionType::BUY) {
            total_invested += transaction.getTotalValue();
        } else {
            total_invested -= transaction.getTotalValue();
        }
    }
    
    // Current portfolio value minus cash (only holdings)
    for (const auto& pair : stock_quantities) {
        if (pair.second > 0) {
            auto stock_it = stocks.find(pair.first);
            if (stock_it != stocks.end()) {
                current_value += pair.second * stock_it->second->getCurrentPrice();
            }
        }
    }
    
    return current_value - total_invested;
}

double Portfolio::getPerformancePercentage() const {
    double initial_investment = 10000.0;  // Starting cash
    double current_total = getTotalValue();
    
    return ((current_total - initial_investment) / initial_investment) * 100.0;
}

void Portfolio::updateSectorAllocation() {
    sector_allocation.clear();
    double total_value = getTotalValue() - cash_balance;  // Only holdings
    
    if (total_value <= 0) return;
    
    // DSA: Using map for ordered sector data
    for (const auto& pair : stock_quantities) {
        if (pair.second > 0) {
            auto stock_it = stocks.find(pair.first);
            if (stock_it != stocks.end()) {
                std::string sector = stock_it->second->getSector();
                double holding_value = pair.second * stock_it->second->getCurrentPrice();
                sector_allocation[sector] += (holding_value / total_value) * 100.0;
            }
        }
    }
}

std::vector<Transaction> Portfolio::getRecentTransactions(int count) {
    std::vector<Transaction> recent = transaction_history;
    
    // DSA: Sort by timestamp (most recent first)
    std::sort(recent.begin(), recent.end(), std::greater<Transaction>());
    
    if (recent.size() > static_cast<size_t>(count)) {
        recent.erase(recent.begin() + count, recent.end());
    }
    
    return recent;
}

void Portfolio::sortStocksByPerformance() {
    // DSA: Sorting algorithm demonstration
    std::vector<std::pair<std::string, std::shared_ptr<Stock>>> stock_pairs;
    
    for (const auto& pair : stocks) {
        if (stock_quantities.count(pair.first) > 0 && stock_quantities.at(pair.first) > 0) {
            stock_pairs.push_back(pair);
        }
    }
    
    std::sort(stock_pairs.begin(), stock_pairs.end(), 
              [](const auto& a, const auto& b) {
                  return a.second->getPerformance() > b.second->getPerformance();
              });
    
    std::cout << "\n=== STOCKS SORTED BY PERFORMANCE ===\n";
    for (const auto& pair : stock_pairs) {
        std::cout << pair.first << ": " << std::fixed << std::setprecision(2) 
                  << pair.second->getPerformance() << "%\n";
    }
}

void Portfolio::displayPortfolio() const {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "PORTFOLIO: " << portfolio_name << "\n";
    std::cout << std::string(50, '=') << "\n";
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Cash Balance: $" << cash_balance << "\n";
    std::cout << "Total Portfolio Value: $" << getTotalValue() << "\n";
    std::cout << "Total Gain/Loss: $" << getTotalGainLoss() << "\n";
    std::cout << "Performance: " << getPerformancePercentage() << "%\n\n";
    
    std::cout << "HOLDINGS:\n";
    std::cout << std::string(50, '-') << "\n";
    
    for (const auto& pair : stock_quantities) {
        if (pair.second > 0) {
            auto stock_it = stocks.find(pair.first);
            if (stock_it != stocks.end()) {
                auto stock = stock_it->second;
                double holding_value = pair.second * stock->getCurrentPrice();
                
                std::cout << stock->getSymbol() << " (" << stock->getCompanyName() << ")\n";
                std::cout << "  Shares: " << pair.second << "\n";
                std::cout << "  Price: $" << stock->getCurrentPrice() << "\n";
                std::cout << "  Value: $" << holding_value << "\n";
                std::cout << "  Performance: " << stock->getPerformance() << "%\n\n";
            }
        }
    }
}

void Portfolio::displayPerformanceAnalysis() {
    std::cout << "\n=== PERFORMANCE ANALYSIS ===\n";
    
    auto top_performers = getTopPerformers(3);
    auto worst_performers = getWorstPerformers(3);
    
    std::cout << "\nTOP PERFORMERS:\n";
    for (size_t i = 0; i < top_performers.size(); i++) {
        std::cout << (i+1) << ". " << top_performers[i]->getSymbol() 
                  << ": " << std::fixed << std::setprecision(2) 
                  << top_performers[i]->getPerformance() << "%\n";
    }
    
    std::cout << "\nWORST PERFORMERS:\n";
    for (size_t i = 0; i < worst_performers.size(); i++) {
        std::cout << (i+1) << ". " << worst_performers[i]->getSymbol() 
                  << ": " << std::fixed << std::setprecision(2) 
                  << worst_performers[i]->getPerformance() << "%\n";
    }
}

void Portfolio::displaySectorDiversification() {
    updateSectorAllocation();
    
    std::cout << "\n=== SECTOR DIVERSIFICATION ===\n";
    for (const auto& pair : sector_allocation) {
        std::cout << pair.first << ": " << std::fixed << std::setprecision(1) 
                  << pair.second << "%\n";
    }
}

void Portfolio::displayTransactionHistory(int count) {
    auto recent = getRecentTransactions(count);
    
    std::cout << "\n=== RECENT TRANSACTIONS ===\n";
    for (const auto& transaction : recent) {
        transaction.displayTransaction();
    }
}
