#pragma once

namespace trading {
enum class Side { BUY, SELL };

enum class OrderType { FillAndKill, GoodTillCancel, GoodForDay };
} // namespace trading