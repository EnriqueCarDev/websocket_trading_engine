#pragma once

#include "order.hpp"
#include "orderlist.hpp"
#include <algorithm>
#include <concepts>

struct PriceCompare {
  const bool ascending_;
  explicit PriceCompare(bool ascending) : ascending_(ascending) {}
  template <typename T, typename U>
  inline bool operator()(const T &t, const U &u) const {
    return (ascending_) ? t.price() < u : t.price() > u;
  }
};

template <typename Container>
concept ContainerOfStruct = requires(Container c) {
  typename Container::value_type;
  requires(std::same_as<typename Container::value_type, OrderList>);
};

template <typename ContainerOfStruct> class PriceLevel {
  const PriceCompare compFn;
  ContainerOfStruct levels;

public:
  PriceLevel(bool ascending) : compFn(ascending) {}
  void insertOrder(Order *order) {
    auto it = std::lower_bound(levels.begin(), levels.end(),
                               order -> getPrice(), compFn)

  };
};