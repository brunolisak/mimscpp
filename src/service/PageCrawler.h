/*
 * PageCrawler.h
 */

#ifndef SERVICE_PAGECRAWLER_H_
#define SERVICE_PAGECRAWLER_H_

#include <vector>

#include "service/data/UrlEntry.h"
#include "web/WebPortal.h"

class PageCrawler {
public:
	PageCrawler(WebPortal& webPortal, const UrlEntry& urlEntry, bool extractLinks);
	virtual ~PageCrawler();
	
	void run();
	const UrlEntry& getUrlEntry() const;
	const std::vector<std::string>& getFoundLinks() const { return _foundLinks; }
	const std::vector<std::string>& getFoundImages() const { return _foundImages; }
	
private:
	WebPortal& _webPortal;
    const UrlEntry& _urlEntry;
	bool _extractLinks;
    std::vector<std::string> _foundLinks;
    std::vector<std::string> _foundImages;
};

#endif /* SERVICE_PAGECRAWLER_H_ */
