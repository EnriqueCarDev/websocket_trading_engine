#include "orderbook_layers/orderbook.hpp"

void OrderBook::matchOrders(Order::Side aggressorSide) {
   while (!bids_.empty() && !asks_.empty()) {
      Order* bestBid = bids_.front();
      Order* bestAsk = asks_.front();

      if (bestBid->price_ >= bestAsk->price_) {
         std::uint32_t quantity = std::min(bestBid->getRemainingQuantity(),
                                           bestAsk->getRemainingQuantity());
         std::uint32_t price = std::min(bestBid->price_, bestAsk->price_);

         Order* aggressor = aggressorSide == Order::BUY ? bestBid : bestAsk;
         Order* opposite = aggressorSide == Order::BUY ? bestAsk : bestBid;

         aggressor->fillOrder(quantity);
         opposite->fillOrder(quantity);

         const Trade trade(price, quantity, *aggressor, *opposite);

         if (bestBid->remaining_quantity_ == 0) bids_.removeOrder(bestBid);
         if (bestAsk->remaining_quantity_ == 0) asks_.removeOrder(bestAsk);

         listener_.onOrder(*bestBid);
         listener_.onOrder(*bestAsk);
         listener_.onTrade(trade);
      } else {
         break;
      }
   }

   auto orders = aggressorSide == Order::BUY ? bids_ : asks_;

   if (!orders.empty()) {
      Order* order = orders.front();
      if (order->isMarket()) {
         order->cancel();
         orders.removeOrder(order);
         listener_.onOrder(*order);
      }
   }
}

void OrderBook::insertOrder(Order* order) {
   if (order->getSide() == Order::BUY) {
      bids_.insertOrder(order);
   } else {
      asks_.insertOrder(order);
   }

   matchOrders(order->getSide());
}

void OrderBook::cancelOrder(Order* order) {
   if (order->getSide() == Order::BUY) {
      bids_.removeOrder(order);
   } else {
      asks_.removeOrder(order);
   }
}