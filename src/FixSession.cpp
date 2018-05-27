
# include <FixSession.hpp>

# include <atomic>

using namespace std;

class FM::FixSession::Impl
{
  atomic<unsigned long> seq_number = { 0 };

public:

  Impl(const string & ip_addr, int port) {}

};
