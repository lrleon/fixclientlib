
# include <chrono>
# include <tclap/CmdLine.h>
# include <asio.hpp>
# include <FixSession.hpp>

using namespace std;
using namespace std::chrono;
using namespace FM;
using namespace TCLAP;
using namespace asio;

CmdLine cmd = { "test-fix-session", ' ', "0" };

ValueArg<string> ip_addr =
  { "i", "ip", "ip address", false, "127.0.0.1", "ip address", cmd };

ValueArg<int> port =
  { "p", "port", "port number", false, 0, "port number", cmd };

ValueArg<size_t> hb_period =
  { "H", "heartbeat", "heartbeat", false, 20, "heartbeat", cmd };

ValueArg<size_t> duration =
  { "d", "duration", "duration in secs", false, 60, "duration", cmd };

int test(int argc, char *argv[])
{
  cmd.parse(argc, argv);

  cout << "Starting FixSession simulation" << endl
       << endl;

  FixSession s(ip_addr.getValue(), port.getValue(), hb_period.getValue());
  s.logon();

  cout << "logon performed" << endl;

  io_service io;
  basic_waitable_timer<system_clock> timer(io, seconds(::duration.getValue()));
  timer.wait();

  cout << "Simulation finished" << endl;

  return 0;
}

int main(int argc, char *argv[])
{
  return test(argc, argv);
}

