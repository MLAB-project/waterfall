/**
 * \file   Agent.h
 * \author Jan Milik <milikjan@fit.cvut.cz>
 * \date   2014-10-12
 *
 * \brief  Header file for the Agent class.
 */

#ifndef AGENT_MKX11VD
#define AGENT_MKX11VD

#include <cppapp/cppapp.h>
using namespace cppapp;

/**
 * \todo Write documentation for class Agent.
 */
class Agent : public DIObject {
private:
	Agent(const Agent& other);
	
	Thread *thread_;

	void* internalRun() {
		this->run();
		return NULL;
	}

protected:
	virtual void run() = 0;

public:
	/**
	 * Constructor.
	 */
	Agent() :
		thread_(NULL)
	{}
	/**
	 * Destructor.
	 */
	virtual ~Agent() {}
	
	virtual string getName() { return "Unnamed agent."; }
	
	virtual void start() {
		thread_ = new MethodThread<void, Agent>(this, &Agent::internalRun);
	}
	
	virtual void stop() {
		if (thread_ != NULL) {
			thread_->requestStop();
		}
	}
	
	virtual void join() {
		if (thread_ != NULL) {
			thread_->join();
			thread_ = NULL;
		}
	}
};

#endif /* end of include guard: AGENT_MKX11VD */

