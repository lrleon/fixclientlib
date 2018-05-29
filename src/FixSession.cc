
# include <FixSession.hpp>

# include <chrono>
# include <vector>
# include <functional>
# include <iostream>
# include <asio.hpp>

using namespace std;
using namespace asio;
using namespace asio::ip;

namespace FM
{
  extern io_service io_service; // global for all the process
}

class FM::FixSession::Impl
{
public:
  
  const string ip_addr;
  const int port;
  const size_t heartbeat_period;

private:

  // TODO: persistence of not acknowledged messages. I would like a
  // very simple model, preferably *non based on a sql data
  // base*. Maybe a pair of very simple sequential ring files that
  // allow to retrieve entries given the sequence number. A file would
  // have constant entry size having the sequence number and the
  // offset of the body message in the second ring file.

  tcp::resolver resolver;
  tcp::socket socket;
  tcp::endpoint endpoint;

  basic_waitable_timer<chrono::system_clock> timer;

  // Since proactor model is used, this counter, as well as any other
  // multithreaded accessed data does not require lock
  unsigned long seq_number = 0;

  void heartbeat_sending()
  {
    constexpr int Num_HeartBeats = 10;
    static int count = 0; // tmp, only for bounding the number of executions
    cout << "Sending Heartbeat " << ++seq_number << endl; // TMP trace
    timer.expires_at(timer.expires_at() +
		     chrono::seconds(this->heartbeat_period));
    if (++count < Num_HeartBeats)
      timer.async_wait(std::bind(&FM::FixSession::Impl::heartbeat_sending, this));
  }

  void receive() // simulate reception of messages coming of a server
  {

  }

public:

  Impl(const string & ip_addr, const int port, const size_t heartbeat_period)
    : ip_addr(ip_addr), port(port), heartbeat_period(heartbeat_period),
      resolver(io_service), socket(io_service),
      endpoint(address::from_string(ip_addr), port),
      timer(io_service, chrono::seconds(heartbeat_period))
  {
    // empty
    cout << "Created instance of FixSession" << endl
	 << "  ip_addr = " << ip_addr << endl
	 << "  port = " << port << endl
	 << "  hb period = " << heartbeat_period << endl;
  }

  bool logon()
  {
    try
      {
	cout << "Simulating connection to server" << endl;
	socket.connect(endpoint);
      }
    catch (exception & e)
      {
	// it is needed more stuff here
	cout << e.what() << endl;
	// probably rethrow or return false
      }

    // here we must review if the connection has been
    // established. Next to send the logon header and wait for
    // response. Then either to manage error or to prepare everything
    // that would be needed for speaking fix

    timer.async_wait(std::bind(&FM::FixSession::Impl::heartbeat_sending, this));

    cout << "Leaving logon() method" << endl;

    return true;
  }

  bool logout(/* specific parameters */)
  {
    // TODO: perform the logout

    cout << "Simulating logout" << endl;

    timer.cancel();

    return true;
  }

  ~Impl()
  {
    logout();
  }
};

io_service & FM::FixSession::get_io_service() noexcept
{
  return FM::io_service;
}

FM::FixSession::FixSession(const std::string & ip_addr,
			   const int port, const size_t heartbeat_period)
  : pimpl(new FM::FixSession::Impl(ip_addr, port, heartbeat_period))
{
  // empty
}

FM::FixSession::~FixSession() {}

bool FM::FixSession::logon()
{
  return pimpl->logon();
}

bool FM::FixSession::logout()
{
  return pimpl->logout();
}
