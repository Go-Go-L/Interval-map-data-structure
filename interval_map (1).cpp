#include <map>
template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K,V> m_map;
public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
	: m_valBegin(val)
	{}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign( K const& keyBegin, K const& keyEnd, V const& val ) 
	{
		if ( keyEnd > keyBegin )					//check if the interval is non null.
		{
			m_map[keyBegin] = val;			                //keybegin is assigned "normally" to m_map with val
			m_map[keyEnd] = val;					//O(1)	
			auto before = m_map.lower_bound(keyEnd);	        //address to value of key immediately before keyEnd.
			auto after = m_map.upper_bound(keyBegin);		//address to value of key immediately after KeyBegin
			m_map[keyEnd] = before->second;                    //keyend has value of the interval that was there before 
                                                                  //assignment 
			auto end = m_map.find(keyEnd);
			auto beg = m_map.find(keyBegin);
			typename std::map<K,V>::iterator it, ite;  //iterators which will be used to delete pairs
			
			for (it = m_map.begin() ; it != m_map.end() ; it++)	//iterate through the whole map (O(N))
			{
				ite++;										//this iterator will always be one step in front of it. We use this to ensure canonicity
				if (it->first < end && it->first > beg)		//Eliminate pairs which key is between keybegin and keyend
				{	
					m_map.erase(it->first);
					continue;
				}
				if (it->second == ite->second)			//for canonicity e must erase consecutive pairs with the same value to "merge" these intervals.
														//Value type K accepts equal.
				{
					m_map.erase(it->first);
					continue;
				}
				
				
			}
		}
		else{}					//if interval is null, do not assign

	}
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};