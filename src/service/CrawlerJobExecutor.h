/*
 * CrawlerJobExecutor.h
 */

#ifndef SERVICE_CRAWLERJOBEXECUTOR_H_
#define SERVICE_CRAWLERJOBEXECUTOR_H_

#include <thread>

#include "service/UrlEntryQueue.h"
#include "service/PageCrawler.h"

class JobContext;

class CrawlerJobExecutor {
public:
	CrawlerJobExecutor(JobContext& jobContext, int maxDepth);
	virtual ~CrawlerJobExecutor();
    void visitAllEntries();
	
private:
	std::vector<PageCrawler> createPageCrawlers(int numCrawlers);
	void executePageCrawlers(std::vector<PageCrawler>& crawlers);
	
	void collectResults(const std::vector<PageCrawler>& crawlers);
	void collectImages(const UrlEntry& urlEntry, const PageCrawler& crawler);
	void collectLinks(const UrlEntry& urlEntry, const PageCrawler& crawler);
	
    JobContext& _jobContext;
    int _maxDepth;
    UrlEntryQueue _urlQueue;
};

#endif /* SERVICE_CRAWLERJOBEXECUTOR_H_ */
