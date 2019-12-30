#include "SymboleTable.h"
#include <condition_variable>
#include <mutex>

std::condition_variable  SymboleTable :: cv;

std::mutex SymboleTable :: mut;

