#include <vector>
#include <algorithm>
#include <iterator>
#include <initializer_list>
#include <functional>

template<class T, class Cmp = std::greater<T>>
class set_list {
	std::vector<T> st;

	public:
	class iterator : public std::iterator<std::input_iterator_tag, T> {
		typename std::vector<T>::iterator p;
		friend class set_list<T, Cmp>;

		typename std::vector<T>::iterator get_container_iterator() { return p; }

		public:
		iterator(const typename std::vector<T>::iterator _p) : p(_p) {}
		iterator(const iterator& mit) : p(mit.p) {}
		iterator& operator++() {++p;return *this;}
		iterator operator++(int) {iterator tmp(*this); operator++(); return tmp;}
		iterator operator+(int mv) {while(mv--) operator++(); return *this;}
		iterator& operator--() {--p;return *this;}
		iterator operator--(int) {iterator tmp(*this); operator--(); return tmp;}
		iterator operator-(int mv) {while(mv--) operator--(); return *this;}
		unsigned int operator-(const iterator mit) {return p - mit.p; }
		bool operator==(const iterator& rhs) const {return p==rhs.p;}
		bool operator!=(const iterator& rhs) const {return p!=rhs.p;}
		T& operator*() {return *p;}
	};

	iterator begin() { return iterator(st.begin()); }
	iterator end()   { return iterator(st.end()); }
	iterator cbegin() const noexcept { return iterator(st.begin()); }
	iterator cend()   const noexcept { return iterator(st.end()); }

	set_list<T, Cmp> operator=(const set_list<T, Cmp> slt) {
		this->st = slt.st;
		return *this;
	}
	
	unsigned int size() { return st.size(); }
	bool empty() { return st.empty(); }
	void rebuild(const std::vector<T> vt) {
		st.clear();
		std::sort(vt.begin(), vt.end(), Cmp());
		for(auto& i : vt) {
			auto it = std::lower_bound(st.begin(), st.end(), i, Cmp());
			if(it == st.end())
				st.push_back(i);
		}
	}
	void clear() { st.clear(); }
	void repair() { this->rebuild(st); }

	set_list() {}
	set_list(const std::vector<T>& vt) {
		rebuild(vt);
	}
	set_list(const std::vector<T> vt) {
		rebuild(vt);
	}
	set_list(std::initializer_list<T> inlst) {
		std::vector<T> vt(inlst);
		rebuild(vt);
	}

	T& operator[](unsigned int I) { return st[I]; }
	T& at(unsigned int I) { return st.at(I); }
	T& front() { return st.front(); }
	T& back() { return st.back(); }

	bool insert(T val) {
		auto it = std::lower_bound(st.begin(), st.end(), val, Cmp());
		if(it != st.end() && *it == val)
			return false;
		st.insert(it, val);
		return true;
	}
	void push_back(T val) {
		st.push_back(val);
	}
	void push_front(T val) {
		st.insert(st.begin(), val);
	}
	bool erase(T val) {
		auto it = std::lower_bound(st.begin(), st.end(), val, Cmp());
		if(it == st.end())
			return false;
		st.erase(it);
		return true;
	}
	void erase(iterator it) {
		st.erase(it.get_container_iterator());
	}
	void pop_back() {
		st.pop_back();
	}
	void pop_front() {
		st.erase(st.begin());
	}

	bool operator==(const set_list<T, Cmp> C) {
		return this->st == C.st;
	}
	bool operator!=(const set_list<T, Cmp> C) {
		return this->st != C.st;
	}
	bool operator<(const set_list<T, Cmp> C) {
		return this->st < C.st;
	}
	bool operator>(const set_list<T, Cmp> C) {
		return this->st > C.st;
	}
	bool operator<=(const set_list<T, Cmp> C) {
		return this->st <= C.st;
	}
	bool operator>=(const set_list<T, Cmp> C) {
		return this->st >= C.st;
	}

	unsigned int find(T tar) {
		auto it = std::lower_bound(st.begin(), st.end(), tar, Cmp());
		return it - st.begin();
	}
	iterator lower_bound(T tar) {
		auto it = std::lower_bound(st.begin(), st.end(), tar, Cmp());
		return iterator(it);
	}
	iterator upper_bound(T tar) {
		auto it = std::upper_bound(st.begin(), st.end(), tar, Cmp());
		return iterator(it);
	}

	void discretization(T val) {
		Cmp comper;
		for(unsigned int i = 0, eost = st.size(); i < eost; ++i) {
			st[i] = val;
			auto tmp = val; tmp++;
			if(comper(val, tmp))
				++val;
			else
				--val;
		}
	}

	std::vector<T> data() {
		return st;
	}

	set_list<T, Cmp> operator&(set_list<T, Cmp> slt) {
		set_list<T, Cmp> ret;
		for(auto& i : *this) {
			if(slt.find(i) != slt.size())
				ret.push_back(i);
		}
		ret.repair();
		return ret;
	}
	set_list<T, Cmp> operator&=(set_list<T, Cmp> slt) {
		set_list<T, Cmp> ret;
		for(auto& i : *this) {
			if(slt.find(i) != slt.size())
				ret.push_back(i);
		}
		ret.repair();
		*this = ret;
		return *this;;
	}
	set_list<T, Cmp> operator|(set_list<T, Cmp> slt) {
		set_list<T, Cmp> ret;
		for(auto& i : *this)
			ret.push_back(i);
		for(auto& i : slt)
			ret.push_back(i);
		ret.repair();
		return ret;
	}
	set_list<T, Cmp> operator|=(set_list<T, Cmp> slt) {
		for(auto& i : slt)
			this->push_back(i);
		this->repair();
		return *this;
	}
};

int main() {}
