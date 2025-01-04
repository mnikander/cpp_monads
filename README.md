# Monads in C++

Some common monads are easy to implement in C++.

Note that the implementations for 'Maybe' and 'Result' in this repository do _not_ strictly encapsulate the values.
It is possible to check if there is a value in the Maybe, and unwrap it manually.
Strictly speaking, this should not be allowed, and instead 'bind' or function lifting should be used to raise all functions into the monadic context.
Since this is often non-trivial in C++, i.e. the possibility to manually unwrap the values has been left open.

## Getting started

1. Install dependencies
```bash
sudo apt get install g++ cmake libgtest-dev
```

2. Clone the repo
```bash
git clone #...
cd #... navigate into the freshly cloned repo
```

3. Build and run:
```bash
mkdir out && cd out && cmake .. && cd .. # out-of-source build
cmake --build out/ && ./out/unit_tests
```

