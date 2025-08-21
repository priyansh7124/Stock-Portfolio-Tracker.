# 🚀 Stock Portfolio Tracker - DSA Project

A comprehensive **Data Structures and Algorithms** demonstration project that implements a real-world stock portfolio management system using C++.

## 🎯 Project Overview

This project showcases practical applications of various DSA concepts through a stock portfolio tracker that allows users to:

- Buy and sell stocks
- Track portfolio performance
- Analyze market trends
- Demonstrate algorithm efficiency

## 📊 DSA Concepts Implemented

### 1. **Hash Tables** (`std::unordered_map`)

- **Use Case**: Stock lookup and portfolio mapping
- **Time Complexity**: O(1) average case for insert/find/delete
- **Implementation**: Quick stock symbol lookup, portfolio holdings tracking

### 2. **Heaps** (`std::priority_queue`)

- **Use Case**: Finding top/worst performing stocks
- **Time Complexity**: O(log n) for insert/extract, O(1) for peek
- **Implementation**: Max heap for top performers, min heap for worst performers

### 3. **Vectors** (`std::vector`)

- **Use Case**: Price history tracking and transaction logs
- **Time Complexity**: O(1) amortized append, O(1) random access
- **Implementation**: Dynamic arrays for historical data storage

### 4. **Maps** (`std::map`)

- **Use Case**: Sector diversification analysis
- **Time Complexity**: O(log n) for insert/find (Red-Black Tree)
- **Implementation**: Ordered sector allocation tracking

### 5. **Sorting Algorithms**

- **Use Case**: Stock ranking by performance
- **Time Complexity**: O(n log n)
- **Implementation**: Custom comparators with `std::sort`

## 🏗️ System Architecture

```
Stock Portfolio Tracker
├── Stock Class          → Individual stock data management
├── Transaction Class    → Buy/sell transaction records
├── Portfolio Class      → Core portfolio management
└── Main Application     → User interface and market simulation
```

## 🔧 Features

### Core Functionality

- ✅ **Buy/Sell Stocks**: Execute transactions with balance validation
- ✅ **Portfolio Tracking**: Real-time portfolio value calculation
- ✅ **Performance Analysis**: Gain/loss tracking and percentage returns
- ✅ **Transaction History**: Complete transaction log with timestamps

### DSA Demonstrations

- 🔍 **Fast Stock Search**: Hash table lookup demonstration
- 🏆 **Top Performers**: Heap-based ranking system
- 📈 **Price History**: Vector-based time series data
- 🏭 **Sector Analysis**: Map-based categorization
- 🔢 **Sorting Demo**: Custom algorithm implementations

### Advanced Features

- 📊 **Market Simulation**: Random price movements
- 💹 **Volatility Calculation**: Statistical analysis
- 🎯 **Sector Diversification**: Portfolio risk analysis
- ⚡ **Performance Metrics**: Algorithm timing demonstrations

## 🚀 Quick Start

### Prerequisites

- C++17 compatible compiler (g++, clang++)
- Make utility (optional)

### Compilation

#### Using Makefile (Recommended)

```bash
# Build the project
make

# Build and run
make run

# Debug build
make debug

# Clean build files
make clean
```

#### Manual Compilation

```bash
g++ -std=c++17 -Wall -Wextra -O2 -o portfolio_tracker main.cpp Stock.cpp Transaction.cpp Portfolio.cpp
```

### Running the Application

```bash
./portfolio_tracker
```

## 📱 User Interface

The application provides an interactive menu system:

```
🚀 STOCK PORTFOLIO TRACKER - DSA DEMO
1. 📊 View Portfolio
2. 🛒 Buy Stock
3. 💰 Sell Stock
4. 📈 Market Overview
5. 🏆 Performance Analysis (Heaps Demo)
6. 🔍 Search Stock (Hash Table Demo)
7. 📋 Sort Stocks (Sorting Demo)
8. 🏭 Sector Analysis
9. 📜 Transaction History
10. 📈 Simulate Market Movement
11. 🔢 DSA Operations Demo
0. ❌ Exit
```

## 🧮 Algorithm Complexity Analysis

| Operation           | Data Structure | Time Complexity | Space Complexity |
| ------------------- | -------------- | --------------- | ---------------- |
| Stock Lookup        | Hash Table     | O(1) avg        | O(n)             |
| Top Performers      | Max Heap       | O(k log n)      | O(n)             |
| Price Update        | Vector         | O(1) amortized  | O(n)             |
| Sector Analysis     | Map            | O(n log n)      | O(n)             |
| Sort by Performance | Array + Sort   | O(n log n)      | O(n)             |

## 📈 Sample Data

The system includes pre-loaded sample stocks:

- **Technology**: AAPL, GOOGL, MSFT, NVDA, META
- **Automotive**: TSLA
- **E-commerce**: AMZN
- **Entertainment**: NFLX
- **Finance**: JPM
- **Healthcare**: JNJ

## 🎓 Learning Outcomes

This project demonstrates:

1. **Practical DSA Implementation**: Real-world application of theoretical concepts
2. **Time Complexity Analysis**: Understanding algorithm efficiency
3. **Data Structure Selection**: Choosing appropriate structures for specific use cases
4. **C++ STL Mastery**: Effective use of Standard Template Library
5. **System Design**: Modular architecture and class relationships

## 🔮 Future Enhancements

- 📊 **Graph Algorithms**: Stock correlation analysis
- 🌐 **Real API Integration**: Live market data
- 📱 **GUI Interface**: Graphical user interface
- 🤖 **Machine Learning**: Predictive analytics
- 📊 **Advanced Analytics**: Technical indicators

## 🏆 Key DSA Concepts Showcased

### Hash Tables

- Constant time stock lookups
- Efficient portfolio mapping
- Dynamic key-value storage

### Heaps

- Priority-based stock ranking
- Efficient min/max operations
- Real-time performance tracking

### Dynamic Arrays

- Flexible data storage
- Historical data management
- Efficient memory utilization

### Balanced Trees

- Ordered data maintenance
- Logarithmic search operations
- Range-based queries

## 📚 Technical Details

### Memory Management

- Smart pointers for automatic memory management
- RAII principles for resource safety
- Efficient container usage

### Performance Optimization

- Algorithm selection based on use case
- Minimized computational complexity
- Efficient data structure utilization

---

**Built with ❤️ to demonstrate the power of Data Structures and Algorithms in real-world applications!**
