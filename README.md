# Ray Tracer Challenge (C++17)

Project for implementing the exercises from _The Ray Tracer Challenge_ using modern C++ and CMake.

### Build With Ninja (from the build directory)

```bash
cmake -S .. -G Ninja
cmake --build .
```

## Run

```bash
./build/raytracer
```

## Build and Run Tests (from the build directory)

```bash
cmake -S .. -DRAYTRACER_BUILD_TESTS=ON -G Ninja
cmake --build .
ctest --test-dir .
```

## BDD-style Tests (Catch2)

This project uses Catch2 for testing. You can write BDD-style tests using Catch2's `SCENARIO`/`GIVEN`/`WHEN`/`THEN` macros.

Example test (put in `tests/`):

```cpp
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "lib/tuple.h"

using namespace rtc;
using Catch::Approx;

SCENARIO("Magnitude and normalization", "[tuple][bdd]") {
	GIVEN("a vector (1,2,3)") {
		Tuple v = Tuple::vector(1, 2, 3);

		WHEN("magnitude is computed") {
			THEN("it equals sqrt(14)") {
				REQUIRE(magnitude(v) == Approx(std::sqrt(14.0)));
			}
		}
	}
}
```

Run the tests from the `build` directory as shown above. Catch2's output will display each `SCENARIO` as a separate test.
