
# include <thread>
# include <list>
# include <asio.hpp>

using namespace std;

namespace FM
{

  asio::io_service io_service; 

  static list<thread> thread_list; // very probably only a thread

  void init()
  {
    // thread th([] ()
    // 	      {
    // 		io_service.run();
    // 	      });
    // thread_list.push_back(move(th)); // remember that thread object is movable
    io_service.run();
  }

void wait_for_termination()
{
  // for (auto & th : thread_list)
  //   th.join();
}

}
