/*
 * UrlEntry.h
 */

#ifndef SERVICE_DATA_URLENTRY_H_
#define SERVICE_DATA_URLENTRY_H_

#include <sstream>

/**
 * URL entry for processing.
 * Note that instances of this class are immutable.
 */
class UrlEntry {

public:
    
    UrlEntry(const std::string& jobUrl, const std::string& url, int depth) : _jobUrl{jobUrl}, _urlToVisit{url}, _depth{depth}
	{
    	// Nothing else to do.
    }

    virtual ~UrlEntry()
    {
        // Nothing to do.
    }

    const std::string& getUrlToVisit() const
    {
        return _urlToVisit;
    }

    const int getDepth() const
    {
        return _depth;
    }

    const std::string& getJobUrl() const
    {
        return _jobUrl;
    }

    const std::string to_string() const
    {
    	std::stringstream ss;
    	ss << "UrlEntry: {" << std::endl;
        ss << "jobUrl: " << _jobUrl << std::endl;
        ss << "urlToVisit: " << _urlToVisit << std::endl;
        ss << "depth: " << _depth << std::endl;
        ss << "}" << std::endl;
        return ss.str();
    }

private:
    const std::string _jobUrl;  // the instance will have its own copy of the link
    const std::string _urlToVisit;  // the instance will have its own copy of the link
    int _depth;
};

#endif /* SERVICE_DATA_URLENTRY_H_ */
