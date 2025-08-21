#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class Stock {
private:
    std::string symbol;
    std::string company_name;
    double current_price;
    std::vector<double> price_history; 
    std::string sector;

public:
    Stock(const std::string& sym, const std::string& name, double price, const std::string& sec = "Technology");
    
    std::string getSymbol() const { return symbol; }
    std::string getCompanyName() const { return company_name; }
    double getCurrentPrice() const { return current_price; }
    std::string getSector() const { return sector; }
    const std::vector<double>& getPriceHistory() const { return price_history; }
    
    void updatePrice(double new_price); 
    double getPerformance() const;       
    double getAveragePrice() const;      
    double getVolatility() const; 
    
    void displayInfo() const;
    bool operator<(const Stock& other) const; 
};

#endif
