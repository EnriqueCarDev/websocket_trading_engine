#include <vector>

enum class Side { BUY, SELL };
enum class OrderType { FillAndKill, GoodTillCancel, GoodForDay };

using Price = std::uint32_t;
using Quantity = std::uint32_t;
using Id = std::uint64_t;

class Order {
  Id id_;
  Price price_;
  Side side_;
  OrderType type_;
  Quantity initial_quantity_;
  Quantity remaining_quantity_;

public:
  Order(Id id, Price price, Side side, OrderType type,
        Quantity initial_quantity)
      : id_{id}, price_{price}, side_{side}, type_{type},
        initial_quantity_{initial_quantity},
        remaining_quantity_{initial_quantity} {}
};