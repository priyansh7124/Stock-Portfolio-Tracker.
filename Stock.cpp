#include "Stock.h"
#include <numeric>
#include <algorithm>
#include <cmath>

Stock::Stock(const std::string& sym, const std::string& name, double price, const std::string& sec)
    : symbol(sym), company_name(name), current_price(price), sector(sec) {
    price_history.push_back(price);  // Initialize with starting price
}

void Stock::updatePrice(double new_price) {
    price_history.push_back(new_price);  // DSA: Vector append O(1) amortized
    current_price = new_price;
}

double Stock::getPerformance() const {
    if (price_history.size() < 2) return 0.0;
    
    double initial_price = price_history.front();
    return ((current_price - initial_price) / initial_price) * 100.0;
}

double Stock::getAveragePrice() const {
    if (price_history.empty()) return 0.0;
    
    // DSA: Using STL algorithm for sum calculation
    double sum = std::accumulate(price_history.begin(), price_history.end(), 0.0);
    return sum / price_history.size();
}

double Stock::getVolatility() const {
    if (price_history.size() < 2) return 0.0;
    
    double avg = getAveragePrice();
    double variance = 0.0;
    
    // Calculate variance using DSA iteration
    for (const double& price : price_history) {
        variance += std::pow(price - avg, 2);
    }
    
    return std::sqrt(variance / price_history.size());
}

void Stock::displayInfo() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Symbol: " << symbol << "\n";
    std::cout << "Company: " << company_name << "\n";
    std::cout << "Current Price: $" << current_price << "\n";
    std::cout << "Performance: " << getPerformance() << "%\n";
    std::cout << "Sector: " << sector << "\n";
    std::cout << "Price History Size: " << price_history.size() << " entries\n";
    std::cout << "Average Price: $" << getAveragePrice() << "\n";
    std::cout << "Volatility: $" << getVolatility() << "\n";
    std::cout << "------------------------\n";
}

bool Stock::operator<(const Stock& other) const {
    return this->getPerformance() < other.getPerformance();
}
