/*
 * CrawlerJobExecutor.cpp
 */

#include <algorithm>
#include <vector>

#include "service/CrawlerJobExecutor.h"
#include "service/data/JobContext.h"
#include "service/data/UrlEntry.h"

CrawlerJobExecutor::CrawlerJobExecutor(JobContext& jobContext, int maxDepth) : _jobContext{jobContext}
{
    // Initialize the url queue with the job request urls.
	const std::vector<std::string>& jobUrls = _jobContext.getJobRequest().getUrls();
	std::for_each(jobUrls.begin(), jobUrls.end(), [this](const std::string& url)
	{
		UrlEntry urlEntry{url, url, 1};
		_urlQueue.push(urlEntry);
	});
}

CrawlerJobExecutor::~CrawlerJobExecutor()
{
    // Nothing to do.
}

void CrawlerJobExecutor::visitAllEntries()
{
	int numThreads = _jobContext.getJobRequest().getNumThreads();

	while(_urlQueue.size() > 0)
	{
        // Create a set of page crawlers, with a single url to visit each.
        int numCrawlers = std::min(_urlQueue.size(), numThreads);

        std::vector<PageCrawler> crawlers = createPageCrawlers(numCrawlers);
        executePageCrawlers(crawlers);
        
        // Collect the web crawling results.
        collectResults(crawlers);
	}
	
	_jobContext.setCompleted(true);  // the only thread that changes this value
}

std::vector<PageCrawler> CrawlerJobExecutor::createPageCrawlers(int numCrawlers)
{
    std::vector<PageCrawler> crawlers;
    for(int i = 0; i < numCrawlers; i++)
    {
    	const UrlEntry& urlEntry = _urlQueue.pop();
        PageCrawler crawler {_jobContext.getWebPortal(), urlEntry, urlEntry.getDepth() <= _maxDepth};
        crawlers.push_back(crawler);
    }
    return crawlers;
}


void CrawlerJobExecutor::executePageCrawlers(std::vector<PageCrawler>& crawlers)
{
    std::vector<std::thread> crawlerThreads;
    
    // Launch the crawler threads
    std::for_each(crawlers.begin(), crawlers.end(), [&crawlerThreads](PageCrawler& crawler)
    {
        std::thread crawlerThread([&crawler](){crawler.run();});
        crawlerThreads.push_back(std::move(crawlerThread));
    });
    
    // Wait for them to complete.
    std::for_each(crawlerThreads.begin(), crawlerThreads.end(), [](std::thread& t){t.join();});
}


void CrawlerJobExecutor::collectResults(const std::vector<PageCrawler>& crawlers)
{
    std::for_each(crawlers.begin(), crawlers.end(), [this](const PageCrawler& crawler)
    {
        const UrlEntry& urlEntry = crawler.getUrlEntry();
        collectImages(urlEntry, crawler);
        collectLinks(urlEntry, crawler);
    });
}

void CrawlerJobExecutor::collectImages(const UrlEntry& urlEntry, const PageCrawler& crawler)
{
    JobImages& jobImages = _jobContext.getJobImages();
    jobImages.addAll(urlEntry.getJobUrl(), crawler.getFoundImages());
}

void CrawlerJobExecutor::collectLinks(const UrlEntry& urlEntry, const PageCrawler& crawler)
{
    const std::vector<std::string>& foundLinks = crawler.getFoundLinks();
    
    std::for_each(foundLinks.begin(), foundLinks.end(), [this, &urlEntry](const std::string& link)
    {
        UrlEntry newUrlEntry{urlEntry.getJobUrl(), link, urlEntry.getDepth() + 1};
        _urlQueue.push(newUrlEntry);
    });
}
