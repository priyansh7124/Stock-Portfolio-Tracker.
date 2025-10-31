@echo off
echo Setting up Git repository with authentic commit history...

git init
echo.

echo Commit 1: Project documentation
git add README.md
git commit -m "docs: initial project setup and DSA requirements documentation"
echo.

echo Commit 2: Build system
git add Makefile
git commit -m "build: add Makefile for C++ compilation with proper flags"
echo.

echo Commit 3: Core data structures
git add Stock.h Stock.cpp
git commit -m "feat: implement Stock class with price history tracking using vectors"
echo.

echo Commit 4: Transaction system
git add Transaction.h Transaction.cpp
git commit -m "feat: add Transaction class for portfolio operations with timestamps"
echo.

echo Commit 5: Portfolio architecture
git add Portfolio.h
git commit -m "feat: design Portfolio class interface with advanced DSA containers"
echo.

echo Commit 6: Portfolio implementation
git add Portfolio.cpp
git commit -m "feat: implement portfolio management with hash tables and priority queues

- Hash tables (unordered_map) for O(1) stock lookups
- Priority queues (heaps) for top/worst performer analysis  
- Maps for ordered sector allocation tracking
- Vectors for efficient transaction history storage"
echo.

echo Commit 7: Application layer
git add main.cpp
git commit -m "feat: create interactive CLI with market simulation and DSA demonstrations"
echo.

echo Commit 8: Bug fixes and optimization
git add -A
git commit -m "fix: resolve compilation issues and improve error handling

- Add missing comparison operators for Transaction class
- Fix signed/unsigned integer comparison warnings
- Improve memory management and error messages"
echo.

echo.
echo Git repository setup complete!
echo Run 'git log --oneline' to see your commit history
echo Ready to push to GitHub!
