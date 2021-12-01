#include <map>
template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();
private:
	V m_valBegin;
	std::map<K,V> m_map;
public:
	// constructor associates whole range of K with val
	void interval_map(V const& val, std::map<K,V> map)
	{
		m_valBegin = val;
		m_map = map;
	}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign( K const& keyBegin, K const& keyEnd, V const& val ) 
	{
		if (keyBegin > keyEnd)
		{
			return 0
		}
		else
		{

		}
// INSERT YOUR SOLUTION HERE
	}

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};