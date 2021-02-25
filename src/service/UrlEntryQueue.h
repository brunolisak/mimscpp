/*
 * Queue for Url entries that are to be visited for a specific job.
 */

#ifndef SERVICE_URLENTRYQUEUE_H_
#define SERVICE_URLENTRYQUEUE_H_

#include <set>
#include <queue>
#include <string>

class UrlEntry;

class UrlEntryQueue {
public:
	UrlEntryQueue();
	virtual ~UrlEntryQueue();
	
    void push(const UrlEntry& urlEntry);
    const UrlEntry& pop();
    const int size() const;
    
    const std::string to_string() const;
    
private:
    // Optimization to avoid visiting the same URL more than once.
    std::set<std::string> _visitedURLs;
    std::queue<UrlEntry> _urlEntries;
};

#endif /* SERVICE_URLENTRYQUEUE_H_ */
