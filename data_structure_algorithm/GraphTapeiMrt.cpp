#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random> // For Test
# include <unordered_map>
# include <unordered_set>
#include <queue>

struct IMetro {
    virtual void AddConnection(std::string station_name_a, std::string station_name_b) = 0;
    virtual bool IsConnected(std::string station_name_a, std::string station_name_b) = 0;
    virtual bool HasPath(std::string station_name_a, std::string station_name_b) = 0;
    virtual std::vector<std::string> ShortestPath(std::string station_name_a, std::string station_name_b) = 0;
    virtual ~IMetro() {}
};


/// YOUR CODE
using namespace std;
# include <unordered_map>
# include <unordered_set>
# include <set>
#include <queue>
class Metro : public IMetro {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> connections;

public:
    void AddConnection(std::string station_name_a, std::string station_name_b) override {
        if (station_name_a.empty() || station_name_b.empty()) {
            return;
        }
        
        connections[station_name_a].insert(station_name_b);
        connections[station_name_b].insert(station_name_a);
    }

    bool IsConnected(std::string station_name_a, std::string station_name_b) override {
        if (station_name_a == station_name_b) {
            return false;
        }
        
        return connections[station_name_a].count(station_name_b) > 0;
    }

    bool HasPath(std::string station_name_a, std::string station_name_b) override {
        if (station_name_a == station_name_b) {
            return true;
        }
        
        std::unordered_set<std::string> visited;
        std::queue<std::string> queue;
        
        visited.insert(station_name_a);
        queue.push(station_name_a);
        
        while (!queue.empty()) {
            std::string current_station = queue.front();
            queue.pop();
            
            for (const auto& neighbor : connections[current_station]) {
                if (visited.count(neighbor) == 0) {
                    visited.insert(neighbor);
                    queue.push(neighbor);
                    
                    if (neighbor == station_name_b) {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }

std::vector<std::string> ShortestPath(std::string station_name_a, std::string station_name_b) override {
        std::unordered_map<std::string, std::vector<std::vector<std::string>>> paths;
        std::vector<std::string> initial_path = {station_name_a};
        paths[station_name_a].push_back(initial_path);

        std::queue<std::string> queue;
        queue.push(station_name_a);

        while (!queue.empty()) {
            std::string current_station = queue.front();
            queue.pop();

            if (current_station == station_name_b)
                break;

            for (const std::string& neighbor : connections[current_station]) {
                if (paths[neighbor].empty() || paths[neighbor][0].size() == paths[current_station][0].size() + 1) {
                    paths[neighbor].reserve(paths[neighbor].size() + paths[current_station].size());
                    for (const std::vector<std::string>& path : paths[current_station]) {
                        std::vector<std::string> new_path = path;
                        new_path.push_back(neighbor);
                        paths[neighbor].push_back(new_path);
                    }

                    if (!paths[neighbor].empty() && paths[neighbor][0].size() == paths[current_station][0].size() + 1)
                        queue.push(neighbor);
                }
            }
        }

        std::vector<std::string> shortest_path;
        shortest_path.reserve(1000000);
        if (!paths[station_name_b].empty())
            shortest_path = paths[station_name_b][0];

        for (const std::vector<std::string>& path :paths[station_name_b]) {
            if (path.size() < shortest_path.size() || (path.size() == shortest_path.size() && path < shortest_path)) {
            shortest_path = path;
            }
        }
          return shortest_path;
        }

};





void Dump(const std::vector<std::string>&);

void Test1(); // Sample1
void Test2(); // AddConnection, IsConnected 
void Test3(); // AddConnection, IsConnected 
void Test4(); // AddConnection, HasPath 
void Test5(); // AddConnection, HasPath
void Test6(); // AddConnection, ShortestPath 
void Test7(); // AddConnection, ShortestPath

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = { Test1, Test2, Test3, Test4, Test5, Test6, Test7};
    f[id-1]();
}

void Dump(const std::vector<std::string>& path) {
    bool isFirst = true;
    for (const std::string& s : path) {
        if (!isFirst) {
            std::cout << " -> ";
        } else {
            isFirst = false;
        }
        std::cout << s;
    }
    std::cout << std::endl;
}

namespace Feis {}

void Test1() {
    Metro m;
    m.AddConnection("A", "Ce");
    m.AddConnection("Ce", "Cc");
    m.AddConnection("Cc", "Dd");

    m.AddConnection("A", "ak");
    m.AddConnection("ak", "af");
    m.AddConnection("af", "Dd");
    // m.AddConnection("TaipeiMainStation", "Ximen");
    // m.AddConnection("Shuanglian", "Zhongshan");
    // m.AddConnection("Beimen", "Zhongshan");
    // m.AddConnection("Beimen", "Ximen");
    // m.AddConnection("MinquanWRd", "Shuanglian");
    // m.AddConnection("MinquanWRd", "Yuanshan");
    // m.AddConnection("MinquanWRd", "ZhongshangElementarySchool");
    // m.AddConnection("XingtianTample", "ZhongshangElementarySchool");
    // m.AddConnection("XingtianTample", "SongjianNanjing");
    // m.AddConnection("ZhongxiaoXinsheng", "SongjianNanjing");
    // m.AddConnection("ZhongxiaoXinsheng", "Dongmen");
    // m.AddConnection("ShandoTemple", "ZhongxiaoXinsheng");
    // m.AddConnection("ZhongxiaoXinsheng", "ZhongxiaoFuxing");
    // m.AddConnection("ZhongxiaoFuxing", "SunYatSenMemorialHall");
    // m.AddConnection("SunYatSenMemorialHall", "TaipeiCityHall");
    // m.AddConnection("TaipeiCityHall", "Yongchun");
    // m.AddConnection("Yongchun", "Houshanpi");
    // m.AddConnection("Houshanpi", "Kunyang");
    // m.AddConnection("Kunyang", "Nanggong");

    // std::cout << "01) " << std::boolalpha << m.IsConnected("TaipeiMainStation", "Ximen") << std::endl;

    // std::cout << "02) " << std::boolalpha << m.IsConnected("TaipeiMainStation", "Beimen") << std::endl;

    // std::cout << "03) " << std::boolalpha << m.IsConnected("TaipeiMainStation", "TaipeiMainStation") << std::endl;

    // std::cout << "04) " << std::boolalpha << m.HasPath("TaipeiMainStation", "Beimen") << std::endl;

    // std::cout << "05) " << std::boolalpha << m.HasPath("TaipeiMainStation", "FuJenUniversity") << std::endl;

    // std::cout << "06) " << std::boolalpha << m.HasPath("TaipeiMainStation", "TaipeiMainStation") << std::endl;

    std::cout << "07) ";
    Dump(m.ShortestPath("A", "Dd"));

    // std::cout << "08) ";
    // Dump(m.ShortestPath("TaipeiMainStation", "Nanggong"));

    // std::cout << "09) ";
    // Dump(m.ShortestPath("TaipeiMainStation", "SongjianNanjing"));

    // m.AddConnection("Zhongshan", "SongjianNanjing");

    // std::cout << "10) ";
    // Dump(m.ShortestPath("TaipeiMainStation", "SongjianNanjing"));

    // std::cout << "11) ";
    // Dump(m.ShortestPath("TaipeiMainStation", "TaipeiMainStation"));
}

void Test2() {}
void Test3() {}
void Test4() {}
void Test5() {}
void Test6() {}
void Test7() {}