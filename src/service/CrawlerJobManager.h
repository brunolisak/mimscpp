/*
 * CrawlerJobManager.h
 */

#ifndef SERVICE_CRAWLERJOBMANAGER_H_
#define SERVICE_CRAWLERJOBMANAGER_H_

#include <map>
#include <vector>
#include <thread>
#include <string>

#include "service/data/JobRequest.h"
#include "service/data/JobContext.h"
#include "service/CrawlerJobExecutor.h"
#include "web/WebPortal.h"

/**
 * The crawler job manager orchestrates the execution of the submitted crawler jobs.
 */
class CrawlerJobManager
{

public:
	CrawlerJobManager(WebPortal& webPortal);
	virtual ~CrawlerJobManager();

    const std::string submit(const JobRequest& jobRequest);
    const JobContext& getJobContext(const std::string& jobId) const;
    
    void waitForTermination();
    
private:
	
	const std::string createJobId() const;
	const std::string createIdSection() const;
	void validateJobEntry(const JobRequest& jobRequest) const;
	JobContext& createJobContext(const JobRequest& jobRequest);
	
	WebPortal& _webPortal;
	
    std::map<std::string, JobContext> _jobContexts;
    
    // TODO - Eventually, these can be parameterized
    const int _maxJobThreads;
    const int _maxLinkDepth;
    
    // To keep track of all crawler executors.
    // NOTE: In a web server context, this would not be necessary since these executor threads would be detached, but here, in a command line
    // testing context, we need to ensure that all of them are terminated before c;losing the test application.
    std::vector<std::thread> executorThreads;
    std::vector<CrawlerJobExecutor> executors;
};

#endif /* SERVICE_CRAWLERJOBMANAGER_H_ */
