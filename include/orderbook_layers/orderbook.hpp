#pragma once
#include "./types.hpp"
#include <vector>

struct BookLevel {
  trading::Price price;
  trading::Quantity quantity;
};

class Book {
  std::vector<BookLevel> bids_;
  std::vector<BookLevel> asks_;
};

class OrderBook {};