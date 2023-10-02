//Midterm 2 code


#include <iostream>
 #include <list>
 #include <vector>
 #include <cassert>
 using namespace std;


bool smallbig(list <int> &c1, vector <int> &c2)
 { 
   vector <int> temp;
   list <int>:: iterator it = c1.begin();
   if (c1.size() != c2.size())
     return false;
   if (c1.empty() && c2.empty())
     return true;

   for (it; it != c1.end(); it++)
     {
       int i = *it;
       if (*it > c2[i])
       {
           //replace the element
           temp.push_back(c2[i]);
           c2[i] = *it;
           *it = temp[i];
       }
     }
   return true;
 }


//H code


//if (c1.size() != c2.size()) return false;
//list<int>::iterator it1 = c1.begin();
//vector<int>::iterator it2 = c2.begin();
//
//for (it1, it2; it1 != c1.end() && it2 != c2.end(); it1++, it2++)
//{
//    if (*it1 > *it2)
//    {
//        //swap the elements
//        int tmp = *it1;
//        *it1 = *it2;
//        *it2 = tmp;
//    }
//}
//return true;