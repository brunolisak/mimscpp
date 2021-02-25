/*
 * JobRequest.h
 */

#ifndef SERVICE_DATA_JOBREQUEST_H_
#define SERVICE_DATA_JOBREQUEST_H_

#include <vector>
#include <sstream>
#include <algorithm>

//
// A crawling job request.
// This request is composed of a set of urls to crawl, along with the number of threads
// to use in the crawling execution.
// 
// Note that instances of this class are immutable. 
//
class JobRequest {

public:

	/*
     *	
	 */
    JobRequest(const std::vector<std::string>& jobUrls, int numThreads) : _jobUrls{jobUrls}, _numThreads{numThreads}
    {
        if(numThreads < 1)
        {
        	std::stringstream ss;
        	ss << "Invalid job number of threads [" << numThreads << "], must be 1 or more." << std::endl;
            throw std::invalid_argument(ss.str());
        }
        if(jobUrls.size() < 1)
        {
            std::stringstream ss;
            ss << "Invalid number of urls [" << jobUrls.size() << "], must be 1 or more." << std::endl;
        	throw std::invalid_argument(ss.str());
        }
    }

    JobRequest(const JobRequest& request) : _jobUrls{request._jobUrls}, _numThreads{request._numThreads}
    {
    	// Nothing to do.
    }
    
    virtual ~JobRequest()
    {
        // Nothing to do.
    }

    const std::vector<std::string>& getUrls() const
    {
        return _jobUrls;
    }

    const int getNumThreads() const
    {
        return _numThreads;
    }

    const std::string to_string() const
    {
        std::stringstream ss;
        
        ss << "{" << std::endl;
        ss << "\"numThreads\" : " << _numThreads << "," << std::endl;
        ss << "\"jobUrls\" : [" << std::endl;
        std::for_each(_jobUrls.begin(), _jobUrls.end(), [&ss](const std::string& jobUrl){ss << "\"" << jobUrl << "\"" << ",";});
        ss << "]" << std::endl;
        ss << "}";
        
        return ss.str();  // move semantics!
    }

private:
    std::vector<std::string> _jobUrls;
    int _numThreads;
};




#endif /* SERVICE_DATA_JOBREQUEST_H_ */
