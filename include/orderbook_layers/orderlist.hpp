#pragma once
#include "order.hpp"

class OrderList {
private:
  Node *head = nullptr;
  Node *tail = nullptr;
  std::int32_t price_;

public:
  OrderList(std::int32_t price) : price_{price} {}
  const std::int32_t getPrice() const { return price_; }
  struct Iterator {
    friend class OrderList;
    using iteratorCategory = std::forward_iterator_tag;
    using differenceType = std::ptrdiff_t;
    using valueType = Order *;
    using reference = valueType &;
    valueType operator*() const { return current->order; }
    Iterator &operator++() {
      current = current->next;
      return *this;
    }
    bool operator==(const Iterator &other) const {
      return current == other.current;
    }
    operator void *() const { return current; }

  private:
    Iterator(Node *node) : current(node) {}
    Node *current;
  };
};