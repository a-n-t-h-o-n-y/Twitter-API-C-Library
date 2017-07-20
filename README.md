# C++ Twitter API Library

```c++
#include <tal.hpp>
#include <iostream>

int main() {
    tal::App     app{"...consumer_key...", "...consumer_secret..."};
    tal::Account account{"...access_token...", "...access_token_secret..."};
    app.set_account(account);

    // Returns JSON response from twitter.
    std::cout << app.get_account_settings() << std::endl;

    // Update account's status.
    app.update_status(random_string(10));

    return 0;
}
```

### Library Dependencies
* Boost ASIO >= 1.58
* Boost Property Tree >= 1.58
* OpenSSL
* zlib

