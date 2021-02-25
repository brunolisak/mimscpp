/*
 * CrawlerJobManager.cpp
 */

#include <sstream>

#include "service/CrawlerJobManager.h"
#include "service/CrawlerJobExecutor.h"

CrawlerJobManager::CrawlerJobManager(WebPortal& webPortal) : _webPortal{webPortal}, _maxJobThreads{10}, _maxLinkDepth{2}
{
    // Nothing to do.
}

CrawlerJobManager::~CrawlerJobManager()
{
    // TODO - cleanup the executors.
}

const std::string CrawlerJobManager::submit(const JobRequest& jobRequest)
{
	if(jobRequest.getNumThreads() > _maxJobThreads)
	{
        std::stringstream ss;
        ss << "Invalid job number of threads [" << jobRequest.getNumThreads() << "], must between 1 and " << _maxJobThreads << std::endl;
        throw std::invalid_argument(ss.str());
	}
	
    // Create a new job context.
	JobContext& jobContext = createJobContext(jobRequest);

    // Create and start the new job executor.
    // See the "NOTE" in the header file.
    CrawlerJobExecutor executor {jobContext, _maxLinkDepth};
    executors.push_back(std::move(executor));

    CrawlerJobExecutor& executorToLaunch = executors.back();  // get the latest created executor
    std::thread executorThread([&executorToLaunch](){executorToLaunch.visitAllEntries();});
    
    executorThreads.push_back(std::move(executorThread));
    
    return jobContext.getJobId();
}

JobContext& CrawlerJobManager::createJobContext(const JobRequest& jobRequest)
{
    const std::string jobId = createJobId();
    JobContext jobContext {_webPortal, jobId, jobRequest};
    _jobContexts.insert({jobId, std::move(jobContext)});
    
    return _jobContexts.at(jobId);
}

const JobContext& CrawlerJobManager::getJobContext(const std::string& jobId) const
{
	// Intercept any exception to return a meaningful message to the caller.
	try
	{
        return _jobContexts.at(jobId);
	}
	catch(const std::out_of_range& e)
	{
		std::stringstream ss;
		ss << "Unknown job [" << jobId << "]" << std::endl;
		throw std::invalid_argument(ss.str());
	}
}


void CrawlerJobManager::validateJobEntry(const JobRequest& jobRequest) const
{
	int numThreads = jobRequest.getNumThreads();
    if(numThreads > _maxJobThreads)
    {
    	std::stringstream ss;
    	ss << "Invalid job number of threads [" << numThreads << "], must be between 1 and " << _maxJobThreads << std::endl;
        throw std::invalid_argument(ss.str());
    }
    
    
}

// See the "NOTE" section in the header file.
void CrawlerJobManager::waitForTermination()
{
    std::for_each(executorThreads.begin(), executorThreads.end(), [](std::thread& t)
    { 
    	t.join();
    });
}

const std::string CrawlerJobManager::createJobId() const
{
    // TOOD - use an external UUID generator.
    std::stringstream ss;
    ss << "CrawlerJob-" << createIdSection() << "-" << createIdSection() << "-" << createIdSection();
    return ss.str();
}

const std::string CrawlerJobManager::createIdSection() const
{
	return std::to_string(rand() % 100000 + 1);
}
