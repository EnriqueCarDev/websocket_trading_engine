#pragma once
#include <vector>
#include "./types.hpp"
#include "price_level.hpp"

struct Trade {
   friend class Orderbook;

  private:
   Trade(std::uint32_t price, std::uint32_t quantity)
       : price_(price), quantity_(quantity) {}

  public:
   const std::uint32_t price_;
   const std::uint32_t quantity_;
};

class OrderBookListener {
  public:
   virtual void onOrder(const Order& order) {}
   virtual void onTrade(const Trade& trade) {}
};

struct BookLevel {
   std::uint32_t price;
   std::uint32_t quantity;
};

class Book {
   std::vector<BookLevel> bids_;
   std::vector<BookLevel> asks_;
};

class OrderBook {
   PriceLevel<std::vector<OrderList>> bids_ =
       PriceLevel<std::vector<OrderList>>(false);
   PriceLevel<std::vector<OrderList>> asks_ =
       PriceLevel<std::vector<OrderList>>(true);
   OrderBookListener& listener_;
   void matchOrders(Order::Side side);

  public:
   OrderBook(OrderBookListener& listener) : listener_(listener) {}

   void insertOrder(Order* order);
   void cancelOrder(Order* order);
};