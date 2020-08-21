#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_map>
#include <sstream>
#include <set>
#include <functional>
#include <algorithm>
using namespace std;





int main()
{

    set<int> m_set1 , m_set2 , un_match;
    m_set1.insert(1);
    m_set1.insert(2);
    m_set1.insert(3);

    m_set2.insert(1);
    m_set2.insert(3);

    set_difference(m_set1.begin() , m_set1.end() , m_set2.begin() , m_set2.end() , insert_iterator<set<int>>(un_match , un_match.begin()));

    for(auto v:un_match)
    {
        std::cout << v << std::endl;
    }


    return 1;
}
