#pragma once

#include <vector>

class OrderList;
class Order;

class Node {
   friend class OrderList;
   friend class Order;
   Node* prev = nullptr;
   Node* next = nullptr;
   Order* order = nullptr;
};

class Order {
  public:
   enum Side { BUY, SELL };
   enum OrderType { FillAndKill, GoodTillCancel, GoodForDay };

   friend class OrderList;

  private:
   Order* next = nullptr;
   Node node;
   std::string id_;
   std::uint32_t price_;
   std::uint32_t avgPrice_ = 0;
   Side side_;
   OrderType type_;
   std::uint32_t initial_quantity_;
   std::uint32_t remaining_quantity_;
   std::uint32_t cumQty_ = 0;

   void fillOrder(std::uint32_t quantity) {
      if (quantity > remaining_quantity_)
         throw std::logic_error("Quantity is superior to remaining quantity");

      remaining_quantity_ -= quantity;
      avgPrice_ =
          (avgPrice_ * cumQty_) + (price_ * quantity) / (cumQty_ + quantity);
      cumQty_ += quantity;
   }

  public:
   Order(long exchangeId, std::string id, std::uint32_t price, Side side,
         OrderType type, std::uint32_t initial_quantity)
       : exchangeId_{exchangeId},
         id_{id},
         price_{price},
         side_{side},
         type_{type},
         initial_quantity_{initial_quantity},
         remaining_quantity_{initial_quantity} {}

   const long exchangeId_;
   const std::string& getId() const { return id_; }
   const std::uint32_t& getPrice() const { return price_; }
   const Side& getSide() const { return side_; }
   const OrderType& getType() const { return type_; }
   const std::uint32_t& getInitialQuantity() const { return initial_quantity_; }
   const std::uint32_t& getRemainingQuantity() const {
      return remaining_quantity_;
   }

   bool isFilled() const { return remaining_quantity_ == 0; }
};