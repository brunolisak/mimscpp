
/*
 * Web Crawler test application.
 */

#include <iostream>

#include "MockWebPortal.h"
#include "service/data/JobRequest.h"
#include "service/data/JobContext.h"
#include "service/CrawlerJobManager.h"
#include "service/PageCrawler.h"


int main()
{
	std::cout << "Starting the Web Crawler test application." << std::endl;
	
    MockWebPortal mockPortal;
    CrawlerJobManager manager(mockPortal);
    
    JobRequest jobRequest1 {{"www.aaa.com", "www.bbb.com"}, 3};
    const std::string& jobId1 = manager.submit(jobRequest1);
    std::cout << "Submitted job1: " << jobId1 << std::endl;

    const JobContext& incompleteContext1 = manager.getJobContext(jobId1);
    std::cout << "Incompleted job1 context: " << std::endl;
    std::cout << incompleteContext1.to_string() << std::endl;

    // See the "NOTE" section in the CrawlerJobManager header file.
    manager.waitForTermination();
    
    const JobContext& completedContext1 = manager.getJobContext(jobId1);
    std::cout << "Completed job1 context: " << std::endl;
    std::cout << completedContext1.to_string() << std::endl;
    
    std::cout << "End of the Web Crawler test application." << std::endl;
	return 0;
}
