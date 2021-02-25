/*
 * PageCrawler.cpp
 */

#include <iostream>
#include <thread>
#include <algorithm>

#include "service/PageCrawler.h"

PageCrawler::PageCrawler(WebPortal& webPortal, const UrlEntry& urlEntry, bool extractLinks) 
    : _webPortal{webPortal}, _urlEntry{urlEntry}, _extractLinks{extractLinks}
{
    // Nothing else to do.
}

PageCrawler::~PageCrawler()
{
    // Nothing to do.
}

void PageCrawler::run()
{
	const WebPortal::PageCrawlResponse& crawlResponse = _webPortal.crawlPage(_urlEntry.getUrlToVisit());

    _foundImages = crawlResponse._images;

	if(_extractLinks)
	{
	   _foundLinks = crawlResponse._links;
	}
}

const UrlEntry& PageCrawler::getUrlEntry() const
{
	return _urlEntry;
}