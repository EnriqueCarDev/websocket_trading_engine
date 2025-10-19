#include "orderbook_layers/orderbook.hpp"

void OrderBook::matchOrders(Order::Side side) {}

void OrderBook::insertOrder(Order* order) {
   if (order->getSide() == Order::Side::BUY) {
      bids_.insertOrder(order);
   } else {
      asks_.insertOrder(order);
   }

   matchOrders(order->getSide());
}

void OrderBook::cancelOrder(Order* order) {}