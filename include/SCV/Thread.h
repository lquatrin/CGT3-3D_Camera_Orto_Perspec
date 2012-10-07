/*!
\file       Thread.h
\brief      Implementation of a pThread interface.
\author     SCV Team
*/

#ifndef __SCV_THREAD_H__
#define __SCV_THREAD_H__

#include <pThread/pthread.h>

namespace scv {

/*! Class for easy creation of threads.
 * \ingroup util
 */

//! See advanced commands in pThread Documentation.
class Thread {
public:

   /*! Default constructor
   \param detachstate The detachstate can be set to either
      PTHREAD_CREATE_DETACHED or PTHREAD_CREATE_JOINABLE.
   */

	Thread(int detachstate = PTHREAD_CREATE_JOINABLE);
   //! Default destructor.
   //! Destroy the thread(pthread_t _pThread) and attribute(pthread_attr_t _attr).
   virtual ~Thread(void);

   //! Basic pThread control.
   //! \sa stop(void), join(void)
   void run(void);

   //! Basic pThread control.
   //! \sa run(void), join(void)
   void stop(void);

   //! Basic pThread control.
   //! \sa run(void), stop(void)
   void join(void);

   /*! Gets the pThread handler.
   \return pThread handler.
   Any pThread advanced command should use this.
   */
   pthread_t& getPThread(void);

protected:
   static void * entryPoint(void *arg);

   //! Do any setup here.
   virtual void setup(void);

   //! Put the thread execution code here.
   virtual void execute(void) = 0;

private:
   pthread_attr_t _attr;
   pthread_t _pThread;
};

} // namespace scv

#endif // __SCV_THREAD_H__