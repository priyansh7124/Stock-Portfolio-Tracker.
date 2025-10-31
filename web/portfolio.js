// Stock Portfolio Tracker - Web Version
// Demonstrating DSA concepts in JavaScript

class Stock {
    constructor(symbol, name, price, sector = 'Technology') {
        this.symbol = symbol;
        this.name = name;
        this.currentPrice = price;
        this.initialPrice = price;
        this.priceHistory = [price]; // Array (Dynamic Array DSA)
        this.sector = sector;
    }

    updatePrice(newPrice) {
        this.priceHistory.push(newPrice); // O(1) amortized append
        this.currentPrice = newPrice;
    }

    getPerformance() {
        return ((this.currentPrice - this.initialPrice) / this.initialPrice) * 100;
    }

    getAveragePrice() {
        // Using reduce (similar to accumulate in C++)
        const sum = this.priceHistory.reduce((acc, price) => acc + price, 0);
        return sum / this.priceHistory.length;
    }
}

class Portfolio {
    constructor(initialCash = 10000) {
        this.cashBalance = initialCash;
        this.holdings = new Map(); // Hash Map for O(1) lookup
        this.transactions = []; // Array for transaction history
        this.stocks = new Map(); // Hash Map for available stocks
        
        this.initializeMarket();
    }

    initializeMarket() {
        // Initialize market with sample stocks
        const marketData = [
            ['AAPL', 'Apple Inc.', 175.50, 'Technology'],
            ['GOOGL', 'Alphabet Inc.', 142.30, 'Technology'],
            ['MSFT', 'Microsoft Corp.', 378.85, 'Technology'],
            ['TSLA', 'Tesla Inc.', 248.50, 'Automotive'],
            ['AMZN', 'Amazon.com Inc.', 155.20, 'E-commerce'],
            ['NVDA', 'NVIDIA Corp.', 875.30, 'Technology'],
            ['META', 'Meta Platforms', 485.50, 'Technology'],
            ['NFLX', 'Netflix Inc.', 445.75, 'Entertainment'],
            ['JPM', 'JPMorgan Chase', 185.40, 'Finance'],
            ['JNJ', 'Johnson & Johnson', 162.80, 'Healthcare']
        ];

        marketData.forEach(([symbol, name, price, sector]) => {
            this.stocks.set(symbol, new Stock(symbol, name, price, sector));
        });

        // Simulate some price history
        this.simulateHistoricalData();
    }

    simulateHistoricalData() {
        // Simulate 30 days of price history
        for (let day = 0; day < 30; day++) {
            this.stocks.forEach(stock => {
                const change = (Math.random() - 0.5) * 0.1; // ±5% max change
                const newPrice = Math.max(stock.currentPrice * (1 + change), 1);
                stock.updatePrice(newPrice);
            });
        }
    }

    // Hash Table Lookup - O(1) time complexity
    findStock(symbol) {
        return this.stocks.get(symbol) || null;
    }

    buyStock(symbol, quantity) {
        const stock = this.findStock(symbol); // O(1) lookup
        if (!stock) {
            throw new Error('Stock not found');
        }

        const totalCost = quantity * stock.currentPrice;
        if (totalCost > this.cashBalance) {
            throw new Error('Insufficient funds');
        }

        this.cashBalance -= totalCost;
        
        // Update holdings using Hash Map
        const currentHolding = this.holdings.get(symbol) || 0;
        this.holdings.set(symbol, currentHolding + quantity);

        // Record transaction
        this.transactions.push({
            type: 'BUY',
            symbol,
            quantity,
            price: stock.currentPrice,
            timestamp: new Date(),
            total: totalCost
        });

        return true;
    }

    sellStock(symbol, quantity) {
        const stock = this.findStock(symbol);
        if (!stock) {
            throw new Error('Stock not found');
        }

        const currentHolding = this.holdings.get(symbol) || 0;
        if (currentHolding < quantity) {
            throw new Error('Insufficient shares');
        }

        const totalRevenue = quantity * stock.currentPrice;
        this.cashBalance += totalRevenue;

        // Update holdings
        const newHolding = currentHolding - quantity;
        if (newHolding === 0) {
            this.holdings.delete(symbol);
        } else {
            this.holdings.set(symbol, newHolding);
        }

        // Record transaction
        this.transactions.push({
            type: 'SELL',
            symbol,
            quantity,
            price: stock.currentPrice,
            timestamp: new Date(),
            total: totalRevenue
        });

        return true;
    }

    // Heap-like operation using Array.sort() - O(n log n)
    getTopPerformers(count = 5) {
        const ownedStocks = Array.from(this.holdings.keys())
            .map(symbol => this.findStock(symbol))
            .filter(stock => stock !== null);

        // Sort by performance (descending) - similar to max heap
        return ownedStocks
            .sort((a, b) => b.getPerformance() - a.getPerformance())
            .slice(0, count);
    }

    getTotalValue() {
        let total = this.cashBalance;
        
        // Iterate through holdings - O(n) where n is number of unique stocks
        this.holdings.forEach((quantity, symbol) => {
            const stock = this.findStock(symbol);
            if (stock) {
                total += quantity * stock.currentPrice;
            }
        });

        return total;
    }

    simulateMarketMovement() {
        // Simulate random market movement
        this.stocks.forEach(stock => {
            const change = (Math.random() - 0.5) * 0.1; // ±5% change
            const newPrice = Math.max(stock.currentPrice * (1 + change), 1);
            stock.updatePrice(newPrice);
        });
    }

    getAllStocks() {
        return Array.from(this.stocks.values());
    }

    getOwnedStocks() {
        return Array.from(this.holdings.keys())
            .map(symbol => ({
                stock: this.findStock(symbol),
                quantity: this.holdings.get(symbol)
            }))
            .filter(item => item.stock !== null);
    }
}

// Global portfolio instance
const portfolio = new Portfolio();

// UI Functions
function updateDisplay() {
    // Update portfolio value
    const totalValue = portfolio.getTotalValue();
    document.getElementById('portfolioValue').textContent = `$${totalValue.toLocaleString('en-US', {
        minimumFractionDigits: 2,
        maximumFractionDigits: 2
    })}`;

    // Update cash balance
    document.getElementById('cashBalance').textContent = `$${portfolio.cashBalance.toLocaleString('en-US', {
        minimumFractionDigits: 2,
        maximumFractionDigits: 2
    })}`;

    // Update holdings count
    document.getElementById('holdingsCount').textContent = `${portfolio.holdings.size} Stocks`;

    // Update performance
    const performance = ((totalValue - 10000) / 10000) * 100;
    const performanceElement = document.getElementById('performance');
    const performanceClass = performance >= 0 ? 'positive' : 'negative';
    const performanceSign = performance >= 0 ? '+' : '';
    performanceElement.innerHTML = `<span class="${performanceClass}">${performanceSign}${performance.toFixed(2)}% Total</span>`;

    // Update stock grid
    updateStockGrid();
}

function updateStockGrid() {
    const stockGrid = document.getElementById('stockGrid');
    const ownedStocks = portfolio.getOwnedStocks();
    
    if (ownedStocks.length === 0) {
        stockGrid.innerHTML = '<div style="text-align: center; color: #718096; padding: 40px;">No stocks owned. Buy some stocks to get started!</div>';
        return;
    }

    stockGrid.innerHTML = ownedStocks.map(({stock, quantity}) => {
        const performance = stock.getPerformance();
        const performanceClass = performance >= 0 ? 'positive' : 'negative';
        const totalValue = quantity * stock.currentPrice;
        
        return `
            <div class="stock-item">
                <div class="stock-info">
                    <h4>${stock.symbol} - ${stock.name}</h4>
                    <div style="color: #718096;">Shares: ${quantity} | Sector: ${stock.sector}</div>
                </div>
                <div style="text-align: right;">
                    <div class="stock-price">$${stock.currentPrice.toFixed(2)}</div>
                    <div class="${performanceClass}">${performance >= 0 ? '+' : ''}${performance.toFixed(2)}%</div>
                    <div style="font-size: 0.9rem; color: #718096;">Value: $${totalValue.toFixed(2)}</div>
                </div>
            </div>
        `;
    }).join('');
}

function showBuyModal() {
    document.getElementById('buyModal').style.display = 'block';
}

function closeBuyModal() {
    document.getElementById('buyModal').style.display = 'none';
}

function showSellModal() {
    const sellSymbol = document.getElementById('sellSymbol');
    const ownedStocks = portfolio.getOwnedStocks();
    
    if (ownedStocks.length === 0) {
        alert('You don\'t own any stocks to sell!');
        return;
    }

    sellSymbol.innerHTML = ownedStocks.map(({stock, quantity}) => 
        `<option value="${stock.symbol}">${stock.symbol} - ${stock.name} (${quantity} shares)</option>`
    ).join('');

    document.getElementById('sellModal').style.display = 'block';
}

function closeSellModal() {
    document.getElementById('sellModal').style.display = 'none';
}

function buyStock() {
    try {
        const symbol = document.getElementById('buySymbol').value;
        const quantity = parseInt(document.getElementById('buyQuantity').value);

        if (!quantity || quantity <= 0) {
            alert('Please enter a valid quantity');
            return;
        }

        portfolio.buyStock(symbol, quantity);
        alert(`Successfully bought ${quantity} shares of ${symbol}!`);
        closeBuyModal();
        updateDisplay();
        
        // Clear form
        document.getElementById('buyQuantity').value = '';
    } catch (error) {
        alert(`Error: ${error.message}`);
    }
}

function sellStock() {
    try {
        const symbol = document.getElementById('sellSymbol').value;
        const quantity = parseInt(document.getElementById('sellQuantity').value);

        if (!quantity || quantity <= 0) {
            alert('Please enter a valid quantity');
            return;
        }

        portfolio.sellStock(symbol, quantity);
        alert(`Successfully sold ${quantity} shares of ${symbol}!`);
        closeSellModal();
        updateDisplay();
        
        // Clear form
        document.getElementById('sellQuantity').value = '';
    } catch (error) {
        alert(`Error: ${error.message}`);
    }
}

function simulateMarket() {
    portfolio.simulateMarketMovement();
    alert('📈 Market prices updated! Check your portfolio performance.');
    updateDisplay();
}

function showDSADemo() {
    const dsaDemo = document.getElementById('dsaDemo');
    dsaDemo.style.display = dsaDemo.style.display === 'none' ? 'block' : 'none';
}

function searchStock() {
    const symbol = prompt('Enter stock symbol to search (e.g., AAPL):');
    if (!symbol) return;

    // Demonstrate hash table lookup with timing
    const startTime = performance.now();
    const stock = portfolio.findStock(symbol.toUpperCase());
    const endTime = performance.now();
    const lookupTime = (endTime - startTime).toFixed(4);

    if (stock) {
        alert(`✅ Stock found in ${lookupTime}ms!\n\n` +
              `${stock.symbol} - ${stock.name}\n` +
              `Current Price: $${stock.currentPrice.toFixed(2)}\n` +
              `Performance: ${stock.getPerformance().toFixed(2)}%\n` +
              `Sector: ${stock.sector}\n\n` +
              `🔍 Hash Table Lookup: O(1) time complexity`);
    } else {
        alert(`❌ Stock '${symbol}' not found!\n` +
              `Lookup time: ${lookupTime}ms\n\n` +
              `Available stocks: AAPL, GOOGL, MSFT, TSLA, AMZN, NVDA, META, NFLX, JPM, JNJ`);
    }
}

// Close modals when clicking outside
window.onclick = function(event) {
    const buyModal = document.getElementById('buyModal');
    const sellModal = document.getElementById('sellModal');
    
    if (event.target === buyModal) {
        closeBuyModal();
    }
    if (event.target === sellModal) {
        closeSellModal();
    }
}

// Initialize display on page load
document.addEventListener('DOMContentLoaded', function() {
    updateDisplay();
    
    // Add some demo data
    setTimeout(() => {
        try {
            portfolio.buyStock('AAPL', 5);
            portfolio.buyStock('GOOGL', 3);
            portfolio.buyStock('TSLA', 2);
            updateDisplay();
        } catch (error) {
            console.log('Demo data setup failed:', error);
        }
    }, 1000);
});
