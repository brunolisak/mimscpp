/*
 * JobImages.h
 */

#ifndef SERVICE_DATA_JOBIMAGES_H_
#define SERVICE_DATA_JOBIMAGES_H_

#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>

//
// Collection of found images for a set of job (as defined by the job URL).
//
class JobImages
{

public:
	JobImages(const std::vector<std::string>& jobUrls) : _imagesByJobUrl{}
	{
        std::for_each(jobUrls.begin(), jobUrls.end(), [this](const std::string& url)
        {
        	_imagesByJobUrl.insert({url, std::set<std::string>()});
        });
	}
		
    virtual ~JobImages()
    {
        // Nothing to do.
    }

    void addAll(const std::string& jobUrl, const std::vector<std::string>& imageUrls)
    {
        _imagesByJobUrl.at(jobUrl).insert(imageUrls.begin(), imageUrls.end());
    }
    
    const auto& getImagesByJobUrl() const
    {
    	return _imagesByJobUrl;
    }
    
    const std::string to_string() const
    {
    	std::stringstream ss;
    	
    	ss << "{" << std::endl;
    	for(const auto& [jobUrl, imageSet] : _imagesByJobUrl) {
    	    ss << "\"" << jobUrl << "\"" << " : [";
    	    std::for_each(imageSet.begin(), imageSet.end(), [&ss](const std::string& imageUrl){ss << "\"" << imageUrl << "\"" << ",";});
    	    ss << "]," << std::endl;
    	}
    	ss << "}";
    	
        return ss.str();  // move semantics!
    }
    
private:
    // Collection: map<jobUrl, Set<image urls>> - sets are used to avoid a duplication of image urls.
    std::map<const std::string, std::set<std::string> > _imagesByJobUrl;
};

#endif /* SERVICE_DATA_JOBIMAGES_H_ */
