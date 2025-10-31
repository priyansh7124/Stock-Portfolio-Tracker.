#include "Portfolio.h"
#include "Stock.h"
#include "Transaction.h"
#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

class StockMarketSimulator {
private:
    std::vector<std::shared_ptr<Stock>> market_stocks;
    std::mt19937 rng;
    std::uniform_real_distribution<double> price_change;

public:
    StockMarketSimulator() : rng(std::random_device{}()), price_change(-0.05, 0.05) {
        initializeMarket();
    }
    
    void initializeMarket() {
        // Create sample stocks with realistic data
        market_stocks = {
            std::make_shared<Stock>("AAPL", "Apple Inc.", 175.50, "Technology"),
            std::make_shared<Stock>("GOOGL", "Alphabet Inc.", 142.30, "Technology"),
            std::make_shared<Stock>("MSFT", "Microsoft Corp.", 378.85, "Technology"),
            std::make_shared<Stock>("TSLA", "Tesla Inc.", 248.50, "Automotive"),
            std::make_shared<Stock>("AMZN", "Amazon.com Inc.", 155.20, "E-commerce"),
            std::make_shared<Stock>("NVDA", "NVIDIA Corp.", 875.30, "Technology"),
            std::make_shared<Stock>("META", "Meta Platforms", 485.50, "Technology"),
            std::make_shared<Stock>("NFLX", "Netflix Inc.", 445.75, "Entertainment"),
            std::make_shared<Stock>("JPM", "JPMorgan Chase", 185.40, "Finance"),
            std::make_shared<Stock>("JNJ", "Johnson & Johnson", 162.80, "Healthcare")
        };
        
        // Add some price history to demonstrate trends
        simulateHistoricalData();
    }
    
    void simulateHistoricalData() {
        // Simulate 30 days of price history
        for (int day = 0; day < 30; day++) {
            for (auto& stock : market_stocks) {
                double current = stock->getCurrentPrice();
                double change = price_change(rng);
                double new_price = current * (1.0 + change);
                stock->updatePrice(std::max(new_price, 1.0)); // Minimum price of $1
            }
        }
    }
    
    void simulateMarketMovement() {
        std::cout << "\n📈 Simulating market movement...\n";
        for (auto& stock : market_stocks) {
            double current = stock->getCurrentPrice();
            double change = price_change(rng);
            double new_price = current * (1.0 + change);
            stock->updatePrice(std::max(new_price, 1.0));
        }
        std::cout << "✅ Market prices updated!\n";
    }
    
    std::vector<std::shared_ptr<Stock>> getAvailableStocks() const {
        return market_stocks;
    }
    
    std::shared_ptr<Stock> findStock(const std::string& symbol) {
        for (auto& stock : market_stocks) {
            if (stock->getSymbol() == symbol) {
                return stock;
            }
        }
        return nullptr;
    }
};

class PortfolioManager {
private:
    Portfolio portfolio;
    StockMarketSimulator market;
    
public:
    PortfolioManager(const std::string& name) : portfolio(name) {
        // Add all market stocks to portfolio for tracking
        for (auto stock : market.getAvailableStocks()) {
            portfolio.addStock(stock);
        }
    }
    
    void displayMenu() {
        std::cout << "\n" << std::string(60, '=') << "\n";
        std::cout << "🚀 STOCK PORTFOLIO TRACKER - DSA DEMO\n";
        std::cout << std::string(60, '=') << "\n";
        std::cout << "1. 📊 View Portfolio\n";
        std::cout << "2. 🛒 Buy Stock\n";
        std::cout << "3. 💰 Sell Stock\n";
        std::cout << "4. 📈 Market Overview\n";
        std::cout << "5. 🏆 Performance Analysis (Heaps Demo)\n";
        std::cout << "6. 🔍 Search Stock (Hash Table Demo)\n";
        std::cout << "7. 📋 Sort Stocks (Sorting Demo)\n";
        std::cout << "8. 🏭 Sector Analysis\n";
        std::cout << "9. 📜 Transaction History\n";
        std::cout << "10. 📈 Simulate Market Movement\n";
        std::cout << "11. 🔢 DSA Operations Demo\n";
        std::cout << "0. ❌ Exit\n";
        std::cout << std::string(60, '-') << "\n";
        std::cout << "Choose option: ";
    }
    
    void buyStock() {
        std::string symbol;
        int quantity;
        
        std::cout << "\nEnter stock symbol: ";
        std::cin >> symbol;
        
        auto stock = market.findStock(symbol);
        if (!stock) {
            std::cout << "❌ Stock not found!\n";
            return;
        }
        
        std::cout << "Current price: $" << stock->getCurrentPrice() << "\n";
        std::cout << "Enter quantity to buy: ";
        std::cin >> quantity;
        
        if (quantity <= 0) {
            std::cout << "❌ Invalid quantity!\n";
            return;
        }
        
        portfolio.buyStock(symbol, quantity, stock->getCurrentPrice());
    }
    
    void sellStock() {
        std::string symbol;
        int quantity;
        
        std::cout << "\nEnter stock symbol: ";
        std::cin >> symbol;
        
        auto stock = market.findStock(symbol);
        if (!stock) {
            std::cout << "❌ Stock not found!\n";
            return;
        }
        
        std::cout << "Current price: $" << stock->getCurrentPrice() << "\n";
        std::cout << "Enter quantity to sell: ";
        std::cin >> quantity;
        
        if (quantity <= 0) {
            std::cout << "❌ Invalid quantity!\n";
            return;
        }
        
        portfolio.sellStock(symbol, quantity, stock->getCurrentPrice());
    }
    
    void showMarketOverview() {
        std::cout << "\n=== MARKET OVERVIEW ===\n";
        auto stocks = market.getAvailableStocks();
        
        std::cout << std::left << std::setw(8) << "Symbol" 
                  << std::setw(20) << "Company" 
                  << std::setw(10) << "Price" 
                  << std::setw(12) << "Performance"
                  << "Sector\n";
        std::cout << std::string(70, '-') << "\n";
        
        for (auto stock : stocks) {
            std::cout << std::left << std::setw(8) << stock->getSymbol()
                      << std::setw(20) << stock->getCompanyName().substr(0, 18)
                      << "$" << std::setw(9) << std::fixed << std::setprecision(2) 
                      << stock->getCurrentPrice()
                      << std::setw(10) << stock->getPerformance() << "%"
                      << stock->getSector() << "\n";
        }
    }
    
    void searchStock() {
        std::string symbol;
        std::cout << "\n🔍 Enter stock symbol to search: ";
        std::cin >> symbol;
        
        // Demonstrate hash table lookup
        auto start = std::chrono::high_resolution_clock::now();
        auto stock = portfolio.findStock(symbol);
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        if (stock) {
            std::cout << "\n✅ Stock found in " << duration.count() << " microseconds!\n";
            std::cout << "📊 Hash Table Lookup Performance: O(1) - Constant Time\n\n";
            stock->displayInfo();
        } else {
            std::cout << "\n❌ Stock not found in portfolio!\n";
            std::cout << "⏱️ Hash table lookup time: " << duration.count() << " microseconds\n";
        }
    }
    
    void demonstrateDSA() {
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "🔢 DATA STRUCTURES & ALGORITHMS DEMONSTRATION\n";
        std::cout << std::string(50, '=') << "\n";
        
        // 1. Hash Table Operations
        std::cout << "\n1. 📊 HASH TABLE (std::unordered_map)\n";
        std::cout << "   - Stock lookup: O(1) average case\n";
        std::cout << "   - Portfolio mapping: O(1) insertion/deletion\n";
        std::cout << "   - Total stocks in hash table: " << portfolio.getStockCount() << "\n";
        
        // 2. Heap Operations
        std::cout << "\n2. 🏔️ HEAP (std::priority_queue)\n";
        auto top_performers = portfolio.getTopPerformers(3);
        std::cout << "   - Top performers (Max Heap): O(log n) insertion\n";
        for (size_t i = 0; i < top_performers.size(); i++) {
            std::cout << "     " << (i+1) << ". " << top_performers[i]->getSymbol() 
                      << ": " << top_performers[i]->getPerformance() << "%\n";
        }
        
        // 3. Vector Operations
        std::cout << "\n3. 📋 VECTOR (std::vector)\n";
        auto transactions = portfolio.getTransactionHistory();
        std::cout << "   - Price history storage: O(1) amortized append\n";
        std::cout << "   - Transaction log: O(1) access by index\n";
        std::cout << "   - Total transactions recorded: " << transactions.size() << "\n";
        
        // 4. Map Operations
        std::cout << "\n4. 🗺️ MAP (std::map)\n";
        std::cout << "   - Sector allocation: O(log n) insertion (Red-Black Tree)\n";
        std::cout << "   - Ordered traversal: In-order traversal\n";
        portfolio.displaySectorDiversification();
        
        // 5. Sorting Algorithm
        std::cout << "\n5. 🔢 SORTING ALGORITHMS\n";
        std::cout << "   - Custom comparator sorting: O(n log n)\n";
        std::cout << "   - std::sort with lambda functions\n";
        portfolio.sortStocksByPerformance();
        
        std::cout << "\n📚 Time Complexity Summary:\n";
        std::cout << "   - Hash Table Lookup: O(1)\n";
        std::cout << "   - Heap Insert/Extract: O(log n)\n";
        std::cout << "   - Vector Append: O(1) amortized\n";
        std::cout << "   - Map Insert/Find: O(log n)\n";
        std::cout << "   - Sorting: O(n log n)\n";
    }
    
    void run() {
        int choice;
        bool running = true;
        
        std::cout << "🎉 Welcome to the Stock Portfolio Tracker!\n";
        std::cout << "💰 Starting with $" << portfolio.getCashBalance() << " cash\n";
        
        while (running) {
            displayMenu();
            std::cin >> choice;
            
            switch (choice) {
                case 1:
                    portfolio.displayPortfolio();
                    break;
                case 2:
                    buyStock();
                    break;
                case 3:
                    sellStock();
                    break;
                case 4:
                    showMarketOverview();
                    break;
                case 5:
                    portfolio.displayPerformanceAnalysis();
                    break;
                case 6:
                    searchStock();
                    break;
                case 7:
                    portfolio.sortStocksByPerformance();
                    break;
                case 8:
                    portfolio.displaySectorDiversification();
                    break;
                case 9:
                    portfolio.displayTransactionHistory();
                    break;
                case 10:
                    market.simulateMarketMovement();
                    break;
                case 11:
                    demonstrateDSA();
                    break;
                case 0:
                    std::cout << "\n👋 Thank you for using Stock Portfolio Tracker!\n";
                    std::cout << "💡 This demo showcased:\n";
                    std::cout << "   - Hash Tables for O(1) lookups\n";
                    std::cout << "   - Heaps for top/worst performers\n";
                    std::cout << "   - Vectors for price history\n";
                    std::cout << "   - Maps for ordered data\n";
                    std::cout << "   - Sorting algorithms\n";
                    running = false;
                    break;
                default:
                    std::cout << "❌ Invalid option! Please try again.\n";
            }
            
            if (running) {
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                std::cin.get();
            }
        }
    }
};

int main() {
    try {
        PortfolioManager manager("My Investment Portfolio");
        manager.run();
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
