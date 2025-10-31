# Multi-stage Dockerfile for Stock Portfolio Tracker

# Stage 1: Build the C++ application
FROM gcc:9 as cpp-builder

WORKDIR /app

# Copy source files
COPY *.cpp *.h Makefile ./

# Build the application
RUN make clean && make

# Stage 2: Web server for hosting
FROM nginx:alpine

# Copy C++ executable
COPY --from=cpp-builder /app/portfolio_tracker /usr/local/bin/

# Copy web files
COPY web/ /usr/share/nginx/html/

# Copy documentation
COPY README.md /usr/share/nginx/html/

# Create custom nginx config
RUN echo 'server { \
    listen 80; \
    server_name localhost; \
    \
    location / { \
        root /usr/share/nginx/html; \
        index index.html; \
        try_files $uri $uri/ =404; \
    } \
    \
    location /api/ { \
        # Future API endpoint for C++ backend \
        proxy_pass http://localhost:8080/; \
    } \
}' > /etc/nginx/conf.d/default.conf

EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]
