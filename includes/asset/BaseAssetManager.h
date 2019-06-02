#ifndef NEWNEW_BASEASSETMANAGER_H
#define NEWNEW_BASEASSETMANAGER_H

#include <string>
#include <map>

class BaseAssetManager {

public:
    template <class T> void loadResource(std::string filename, std::map<std::string, std::unique_ptr<T>>& resourceMap);
    template <class T> void releaseResource(std::string filename, std::map<std::string, std::unique_ptr<T>>& resourceMap);
private:
    template <class T> bool mapContainsValueForKey(std::string key, std::map<std::string, std::unique_ptr<T>>& resourceMap);
};


template <class T> void BaseAssetManager::loadResource(std::string filename, std::map<std::string, std::unique_ptr<T>>& resourceMap) {
    T* resource = new T();
    if(!mapContainsValueForKey<T>(filename, resourceMap)) {
        resource->loadFromFile(filename);
        resourceMap.insert(std::make_pair(filename, std::unique_ptr<T>(resource)));
    }
}

template <class T> void BaseAssetManager::releaseResource(std::string filename, std::map<std::string, std::unique_ptr<T>>& resourceMap) {
    typename std::map<std::string, std::unique_ptr<T>>::iterator itr = resourceMap.find(filename);
    if(itr != resourceMap.end()) {
        itr->second.reset();
        resourceMap.erase(itr);
    }
}

template <class T> bool BaseAssetManager::mapContainsValueForKey(std::string key, std::map<std::string, std::unique_ptr<T>>& m) {
    typename std::map<std::string, std::unique_ptr<T>>::iterator itr = m.find(key);
    if(m.find(key) != m.end()) {
        return true;
    }
    return false;
}



#endif //NEWNEW_BASEASSETMANAGER_H
