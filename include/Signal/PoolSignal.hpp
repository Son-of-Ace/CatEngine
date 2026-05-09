#pragma once

#include <functional>
#include <iostream>
#include <print>
#include <utility>
#include <vector>

template <typename... Args> class PoolSignal {
public:
  PoolSignal() = default;

  PoolSignal(const PoolSignal &) = delete;

  PoolSignal &operator=(const PoolSignal &) = delete;

  PoolSignal(PoolSignal &&) = delete;

  PoolSignal &operator=(PoolSignal &&) = delete;

  using Callback = std::function<void(Args...)>;

private:
  struct Slot {
    Callback callback;
    size_t generation;
    bool alive;
  };

  std::vector<Slot> pool;

public:
  struct Handle {
    PoolSignal *sig;
    size_t index;
    size_t generation;

    void Disconnect() {
      if (sig) {
        std::print("Found signal, calling disconnect!\n");
        sig->Disconnect(*this);
      }
    }
  };

  Handle Connect(Callback callback) {
    Handle handle;

    for (size_t i = 0; i < pool.size(); i++) {
      if (!pool[i].alive) {
        std::print("Found reusable handle: {}\n", i);

        Slot &slot = pool[i];

        slot.alive = true;
        slot.callback = callback;
        ++slot.generation;

        handle = {
            .sig = this,
            .index = i,
            .generation = slot.generation,
        };

        return handle;
      }
    }

    Slot newSlot = {
        .callback = callback,
        .generation = 0,
        .alive = true,
    };

    pool.push_back(std::move(newSlot));

    handle = {
        .sig = this,
        .index = pool.size() - 1,
        .generation = newSlot.generation,
    };

    std::print("Created new handle: {}\n", handle.index);

    return handle;
  }

  void Fire(const Args &...args) {
    for (Slot &s : pool) {
      if (s.alive && s.callback) {
        s.callback(args...);
      }
    }
  }

private:
  void Disconnect(Handle h) {
    int index = h.index;

    std::print("Disconnecting\n");

    if (index >= pool.size())
      return;

    Slot &s = pool[h.index];

    if (h.generation != s.generation)
      return;

    pool[index].alive = false;

    std::print("Disconnected signal with index: {}\n", index);
  }
};
