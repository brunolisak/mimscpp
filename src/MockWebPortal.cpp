/*
 * MockWebPortal.cpp
 * Portal that returns mock "crawl" results.
 */

#include "MockWebPortal.h"

#include <map>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

WebPortal::PageCrawlResponse response1
{
	{"www.link2.com", "www.link3.com"},
    {"image1.png", "image2.png", "image3.png", "image4.png", "image5.png", "image6.png", "image7.png", "image8.png", "image9.png", "image10.png"}
};

WebPortal::PageCrawlResponse response2
{
    {"www.link4.com"},
	{"image11.png", "image12.png", "image13.png", "image14.png", "image15.png", "image16.png", "image17.png", "image18.png", "image19.png", "image20.png"}
};

WebPortal::PageCrawlResponse response3
{
    {"www.link5.com", "www.link6.com"},
	{"image31.png", "image32.png", "image33.png"}
};

std::map<std::string, WebPortal::PageCrawlResponse> responses
{
	{"www.aaa.com", response1}, {"www.bbb.com", response2}, {"www.ccc.com", response3},
	{"www.link2.com", response2}, {"www.link3.com", response3}, {"link4.com", response3},
	{"www.link5.com", response1}, {"www.link6.com", response2}
};

MockWebPortal::MockWebPortal()
{
    // Nothing to do.
}

MockWebPortal::~MockWebPortal()
{
    // Nothing to do.
}

const WebPortal::PageCrawlResponse& MockWebPortal::crawlPage(const std::string& url)
{
	// Simulate a network delay between 1 and 5 seconds
	std::cout << "...sleeping to simulate network delay..." << std::endl;
	int delay = rand() % 5 + 1;
	std::this_thread::sleep_for (std::chrono::seconds(delay));
	
    auto it = responses.find(url);

    if(it != responses.end())
	{
        return it->second;
	}
    return response1;  // catch all response
}
