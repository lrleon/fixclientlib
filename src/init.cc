
# include <thread>
# include <asio.hpp>

using namespace std;

namespace FM
{

asio::io_service io_service;

void init()
{
  thread th([] ()
	    {
	      io_service.run();
	    });
  
}

}
