#pragma once
#include <vector>
#include "pricelevels.hpp"

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
   PriceLevels<std::vector<OrderList>> bids_ =
       PriceLevels<std::vector<OrderList>>(false);
   PriceLevels<std::vector<OrderList>> asks_ =
       PriceLevels<std::vector<OrderList>>(true);
   OrderBookListener& listener_;
   void matchOrders(Order::Side side);

  public:
   OrderBook(OrderBookListener& listener) : listener_(listener) {}

   void insertOrder(Order* order);
   void cancelOrder(Order* order);
};