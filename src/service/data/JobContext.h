/*
 * JobContext.h
 */

#ifndef SERVICE_DATA_JOBCONTEXT_H_
#define SERVICE_DATA_JOBCONTEXT_H_

#include <iostream>
#include <sstream>

#include "service/data/JobRequest.h"
#include "service/data/JobContext.h"
#include "service/data/JobImages.h"
#include "web/WebPortal.h"

class JobContext {

public:
    JobContext(WebPortal& webPortal, const std::string& jobId, const JobRequest& jobRequest) 
        : _webPortal{webPortal}, _jobId{jobId}, _jobRequest{jobRequest}, _jobImages{jobRequest.getUrls()}, _completed{false}
    {
        // Nothing else to do.
    }

    JobContext(const JobContext& context) 
        : _webPortal{context._webPortal}, _jobId{context._jobId}, _jobRequest{context._jobRequest}, _jobImages{context._jobImages}, _completed{context._completed}
    {
    	// Nothing else to do.
    }
    
    virtual ~JobContext()
    {
    	// Nothing to do.
    }
    
    bool isCompleted() const
    {
        return _completed;
    }

    void setCompleted(bool completed)
    {
        _completed = completed;
    }

    const std::string& getJobId() const
    {
        return _jobId;
    }

    const JobRequest& getJobRequest() const
    {
        return _jobRequest;
    }

    JobImages& getJobImages()
    {
        return _jobImages;
    }

    WebPortal& getWebPortal() const
    {
    	return _webPortal;
    }
    
    const std::string to_string() const
    {
        std::stringstream ss;
        ss << "{" << std::endl;
        ss << "\"jobId\" : " << "\"" << _jobId << "\"" << "," << std::endl;
        ss << "\"completed\" : " << (_completed?"true":"false") << "," << std::endl;
        ss << "\"jobRequest\" : " << _jobRequest.to_string() << "," << std::endl;
        ss << "\"jobImages\" : " << _jobImages.to_string() << std::endl;
        ss << "}" << std::endl;
        
        return ss.str();  // move semantics!
    }

private:
    WebPortal& _webPortal;
    std::string _jobId;
    JobRequest _jobRequest;
    JobImages _jobImages;
    bool _completed;
};

#endif /* SERVICE_DATA_JOBCONTEXT_H_ */
