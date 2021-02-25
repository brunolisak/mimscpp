/*
 * MockWebPortal.h
 *
 * This class simply fakes a crawl response to a given web page.
 */

#ifndef MOCKWEBPORTAL_H_
#define MOCKWEBPORTAL_H_

#include "web/WebPortal.h"

class MockWebPortal: public WebPortal {
	
public:
	MockWebPortal();
	virtual ~MockWebPortal();

    const WebPortal::PageCrawlResponse& crawlPage(const std::string& url);
};

#endif /* MOCKWEBPORTAL_H_ */
