

#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <map>
#include <algorithm>
#include <string>
using namespace std;
/*
 // Prototype of a utility function to swap two integers 
    int cache_max_size = 5;
    int cache_size = 0;
    vector<pair<int, int> > cache; //cache ,key and numbers
    map<int, char[256]> indices; 

bool isExist(int key){
    for (int i=0; i<cache.size(); i++) 
    { 
        if(cache[i].second == key){
            return true;
        }
    }
    return false; 
}
void insertCache(int key, int times){
    if(cache_size != cache_max_size){
        if(!isExist(key))
        {
            cache.push_back(make_pair(key, times));
        }
        else{

        }
    }
}

void getCache(){
    for (int i=0; i<cache.size(); i++) 
    { 
        cout << cache[i].first << " "
             << cache[i].second << endl; 
    } 
}
bool sortbysec(const pair<int,int> &a, 
              const pair<int,int> &b) 
{ 
    return (a.second < b.second); 
} 
void deleteMin(){
    sort(cache.begin(), cache.end(), sortbysec);
    cache.erase(cache.begin());
}*/
int cache_max_size = 5;
map<string, int> cache;
map<string, string> indices;

bool pairCompare(pair<string, int> i, pair<string, int> j)
{
    return i.second < j.second;
}
void insertCache(string key, string values)
{
    if (cache.size() != cache_max_size) //nếu cahe page chưa đạt max size
    {
        if (cache.find(key) == cache.end())
        { //nếu key chưa tồn tại
            cache[key] = 1;
            indices.insert(pair<string, string>(key, values));
        }
        else
        {
            cache[key]++;
        }
    }
    else
    { //ngược lại thì xóa block có tần suất thấp nhất
        if (cache.find(key) == cache.end())
        {
            map<string, int>::iterator it = min_element(cache.begin(), cache.end(), pairCompare); // phần tử có tần suất thấp nhất
            cout << it->first << " " << it->second << endl;
            cache.erase(it); //xóa phần tử
            indices.erase(it->first);
            cache[key] = 1;  //thêm giá trị mới vào
            indices.insert(pair<string, string>(key, values));
        }
        else{
            cache[key]++;
        }
    }
}

void getCache()
{
    cout << "\ncache\n";
    map<string, int>::iterator it;
    for (it = cache.begin(); it != cache.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
}
void getIndices()
{
    cout << "\nindiecs\n";
    map<string, string>::iterator it;
    for (it = indices.begin(); it != indices.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
}
bool containKey(string key)
    {
        return cache.find(key) == cache.end(); //true-> tồn tại key
    }
    string get(string key)
    {
        return indices[key];
    }
int main(int argc, char const *argv[])
{
    insertCache("abc.txt", "1234");
    insertCache("abc.txt", "1234");
    insertCache("cat.png", "1234");
    insertCache("cat.png", "1234");
    insertCache("cat.png", "1234");
    insertCache("d", "1234");
    insertCache("h", "1234");
    insertCache("g", "1234");
    insertCache("g", "1234");
    insertCache("g", "1234");
    insertCache("g", "1234");
    insertCache("g", "1234");
    insertCache("g", "1234");
    insertCache("d", "1234");
    insertCache("m", "1234");
    //insertCache("m", "1234");
    //deleteMin();*/
    cout << cache.size() << endl;
    getCache();

    getIndices();
    return 0;
}
