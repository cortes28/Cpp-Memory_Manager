#include <iostream>
#include <chrono>
#include "mem_mgr.hpp"

// Using Complex as the object to duplicate


int main(int argc, char* argv[]) {
  const auto start = std::chrono::steady_clock::now();


  const auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Time in seconds: " << elapsed.count() << '\n';

  return 0;
  }