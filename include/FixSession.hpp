#ifndef FIXSESSION_HPP
#define FIXSESSION_HPP

# include <memory>
# include <string>

namespace FM // the Feature Mine namespace
{

  /** This class models a FIX session.

      The amount of sessions is arbitrary, subject to the resources.

      Each session object could be accessed from any thread. So
      reentracy must be guaranteed.

   */
class FixSession
{
public:

  FixSession(const std::string & ip_addr,
	     const int port,
	     const size_t heartbeat_period);
  
  ~FixSession();

  bool logon(/* specific parameters */);

  // TODO: other methods characterizing different interaction with the server
    
  // TODO: other more traditional methods for observing the session state

  bool logout(/* specific parameters */); 

private:

  // Initially we propose the pimpl idiom in order to eventually
  // separate styles, transport protocols, protocol version, etc,
  // through several implementations.

  class Impl;
  std::unique_ptr<Impl> pimpl;
};


  /* Here we would put machinery for retrieving any session according
     several criteria.

     This class would be a singleton

   */
class FixSessionFinder
{
  // TODO
};

extern void init();

}

#endif
