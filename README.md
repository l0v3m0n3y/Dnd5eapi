# Dnd5eapi
api for dnd5eapi.co site for things within the Official 5th Edition SRD
# main
```cpp
#include "Dnd5eapi.h"
#include <iostream>

int main() {
   Dnd5eapi api;

    auto properties = api.weapon_properties().then([](json::value result) {
        std::cout << result<< std::endl;
    });
    properties.wait();
    
    return 0;
}
```

# Launch (your script)
```
g++ -std=c++11 -o main main.cpp -lcpprest -lssl -lcrypto -lpthread -lboost_system -lboost_chrono -lboost_thread
./main
```

