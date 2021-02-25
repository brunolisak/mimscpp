/*
 * WebPortal.h
 *
 * Interface for all portals for accessing web pages.
 */

#ifndef WEB_WEBPORTAL_H_
#define WEB_WEBPORTAL_H_

#include <vector>
#include <string>

class WebPortal
{
public:

	//
	// The crawling response. For now, only images and links.
	//
	struct PageCrawlResponse
	{
		const std::vector<std::string> _links;
		const std::vector<std::string> _images;
	};

	virtual const PageCrawlResponse& crawlPage(const std::string& url) = 0;
};

#endif /* WEB_WEBPORTAL_H_ */
