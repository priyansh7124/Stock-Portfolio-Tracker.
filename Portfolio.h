#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "Stock.h"
#include "Transaction.h"
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
#include <memory>

// Custom comparator for priority queue (max heap for top performers)
struct StockPerformanceComparator {
    bool operator()(const std::shared_ptr<Stock>& a, const std::shared_ptr<Stock>& b) const {
        return a->getPerformance() < b->getPerformance();  // Max heap
    }
};

class Portfolio {
private:
    std::string portfolio_name;
    double cash_balance;
    
    // DSA: Hash table for O(1) stock lookup
    std::unordered_map<std::string, std::shared_ptr<Stock>> stocks;
    
    // DSA: Hash table for tracking quantities
    std::unordered_map<std::string, int> stock_quantities;
    
    // DSA: Vector for transaction history
    std::vector<Transaction> transaction_history;
    
    // DSA: Map for sector diversification (ordered)
    std::map<std::string, double> sector_allocation;
    // Implemented using O(1) stock lockup using unordered_map and heap based performance
public:
    // Constructor
    Portfolio(const std::string& name, double initial_cash = 10000.0);
    
    // Core Operations
    bool buyStock(const std::string& symbol, int quantity, double price);
    bool sellStock(const std::string& symbol, int quantity, double price);
    void addStock(std::shared_ptr<Stock> stock);
    
    // DSA Demonstrations
    std::vector<std::shared_ptr<Stock>> getTopPerformers(int count = 5);  // Using heaps
    std::vector<std::shared_ptr<Stock>> getWorstPerformers(int count = 5); // Using heaps
    std::shared_ptr<Stock> findStock(const std::string& symbol);  // Hash table lookup
    std::vector<std::shared_ptr<Stock>> getStocksBySector(const std::string& sector);
    
    // Portfolio Analysis
    double getTotalValue() const;
    double getTotalGainLoss() const;
    double getPerformancePercentage() const;
    void updateSectorAllocation();
    
    // Transaction Management
    std::vector<Transaction> getTransactionHistory() const { return transaction_history; }
    std::vector<Transaction> getRecentTransactions(int count = 10);
    
    // Display Functions
    void displayPortfolio() const;
    void displayPerformanceAnalysis();
    void displaySectorDiversification();
    void displayTransactionHistory(int count = 10);
    
    // Getters
    double getCashBalance() const { return cash_balance; }
    std::string getPortfolioName() const { return portfolio_name; }
    size_t getStockCount() const { return stocks.size(); }
    
    // Utility
    void sortStocksByPerformance();  // Sorting algorithm demonstration
};

#endif
