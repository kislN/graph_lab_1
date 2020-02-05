#include "Graph.h"
#include "check_bridge.h"
#include "find_bridges.h"
#include "weights_sort.h"
#include "real_graph.h"
#include "stress_tests.h"
#include "experiments.h"
#include <cmath>
#include <limits>


int main() {

    all_experiments();
    stress_DBS();
    stress_RBS();

}