#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <algorithm>
	using namespace std;


class Property
{
public:
    Property(const string& name) //note: we don't lightly copy strings in C++
      : m_name(name) {}
    virtual ~Property() {}
    virtual void pls() {cout << "nah" << endl;}
private:
    string m_name;
};

template< typename T >
class TypedProperty : public Property
{
public:
    TypedProperty (const string& name, const T& data)
      : Property(name), m_data(data) {};
      
      void pls() {
      	cout << m_data << endl;
      }
private:
    T m_data;
};

typedef vector< shared_ptr<Property> > property_list_type;

int main() {
	property_list_type what;
	// TypedProperty<int> yo("test", 5);
	vector<int> ayy;
	shared_ptr<Property> sp(new TypedProperty<string>("hello", "world"));
	shared_ptr<Property> sp2(new TypedProperty<vector<int>>("hello", 5));
	what.push_back(sp);
	what.push_back(sp2);
	what[1]->pls();
}