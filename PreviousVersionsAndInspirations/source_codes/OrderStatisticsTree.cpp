#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
//null_mapped_type instead of null_type in older versions

int main()
{
  ordered_set X;
  for(int i=1;i<=10;i++)
    X.insert(i); // insert element
  
  cout<< X.order_of_key(7)<<endl; // result: 6 (number of keys less than 7)
  cout<< *X.find_by_order(6)<<endl; // result: 7 (6th element (0-based))
  
  X.erase(8); // remove element
  return 0;
}
