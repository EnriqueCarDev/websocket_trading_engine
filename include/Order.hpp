#pragma once

#include "./enums.hpp"
#include "./types.hpp"
#include <vector>

class Order {
  trading::Id id_;
  trading::Price price_;
  trading::Side side_;
  trading::OrderType type_;
  trading::Quantity initial_quantity_;
  trading::Quantity remaining_quantity_;

public:
  Order(trading::Id id, trading::Price price, trading::Side side,
        trading::OrderType type, trading::Quantity initial_quantity)
      : id_{id}, price_{price}, side_{side}, type_{type},
        initial_quantity_{initial_quantity},
        remaining_quantity_{initial_quantity} {}

  trading::Id getId() const { return id_; }
  trading::Price getPrice() const { return price_; }
  trading::Side getSide() const { return side_; }
  trading::OrderType getType() const { return type_; }
  trading::Quantity getInitialQuantity() const { return initial_quantity_; }
  trading::Quantity getRemainingQuantity() const { return remaining_quantity_; }

  bool isFilled() const { return remaining_quantity_ == 0; }

  void fillOrder(trading::Quantity quantity) {
    if (quantity > remaining_quantity_)
      throw std::logic_error("Quantity is superior to remaining quantity");

    remaining_quantity_ -= quantity;
  }
};