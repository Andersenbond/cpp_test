module;

#include <iostream>
#include <vector>

export module dht_service;

class DHTNode 
{
public:
	DHTNode();

private:
	int m_id;

};

/** @brief Distributed Hash Table (DHT) Service class.
 * 
 * The class implements a distributed hash table, it uses 
 * consistent hashing to locate and store data items across
 * a network of nodes. 
 * 
 * @tparam T The type of elements to store in the table.
 *
 */
export template <typename T>
class DHTService
{
public:
	DHTService();
	DHTService(std::initializer_list list);

	T get();
	int set(const T&);
	bool del(int);
	bool update(int, const T&);


private:
	std::vector<DHTNode*> m_nodeList;
};
