/*
 * UrlEntryQueue.cpp
 */

#include <sstream>
#include <algorithm>

#include "service/UrlEntryQueue.h"
#include "service/data/UrlEntry.h"

UrlEntryQueue::UrlEntryQueue()
{
    // Nothing to do.
}

UrlEntryQueue::~UrlEntryQueue()
{
    // Nothing to do.
}

void UrlEntryQueue::push(const UrlEntry& urlEntry)
{
    const std::string& urlToVisit = urlEntry.getUrlToVisit();
    if(_visitedURLs.find(urlToVisit) == _visitedURLs.end())
    {
        _urlEntries.push(urlEntry);
        _visitedURLs.insert(urlToVisit);
    }
}

const UrlEntry& UrlEntryQueue::pop()
{
	if(_urlEntries.empty())
	{
		throw std::out_of_range("Url Entry queue is empty!");
	}
	const UrlEntry& entry = _urlEntries.front();
    _urlEntries.pop();
    return entry;
}

const int UrlEntryQueue::size() const
{
    return _urlEntries.size();
}


const std::string UrlEntryQueue::to_string() const
{
	std::stringstream ss;
    ss << "UrlEntryQueue size: " << _urlEntries.size() << std::endl;
    ss << "Visited: [" << std::endl;
    std::for_each(_visitedURLs.begin(), _visitedURLs.end(), [&ss](const std::string& visited){ss << visited << " ";});
    ss << "]" << std::endl;
    return ss.str();
}

