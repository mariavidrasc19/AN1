// Copyright 2019 Luca Istrate, Danut Matei
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <utility>
#include <cassert>
#include "./aegraph.h"

std::string strip(std::string s) {
    // deletes whitespace from the beginning and end of the string
    s.erase(0, s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t")+1);
    return s;
}

std::pair<std::string, std::string> split_first(std::string s,
    char delimiter = ',') {
    // returns a pair that contains: <first_cut, rest_of_graph>

    int numOpen = 0;

    int len = s.size();
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c == delimiter && numOpen == 0)
            return std::make_pair(
                    strip(s.substr(0, i)), strip(s.substr(i+1, len)));
        if (c == '[')
            numOpen += 1;
        if (c == ']')
            numOpen -= 1;
    }

    return {strip(s), std::string()};
}


std::vector<std::string> split_level(std::string s, char delimiter = ',') {
    // splits 's' into separate entities (atoms, subgraphs)

    std::vector<std::string> result;
    auto snd = s;
    while (true) {
        auto p = split_first(snd, delimiter);
        auto fst = p.first;
        snd = p.second;

        result.push_back(fst);

        if (snd.empty())
            return result;
    }
}


int AEGraph::num_subgraphs() const {
    return subgraphs.size();
}


int AEGraph::num_atoms() const {
    return atoms.size();
}


int AEGraph::size() const {
    return num_atoms() + num_subgraphs();
}


bool AEGraph::operator<(const AEGraph& other) const {
    return this->repr() < other.repr();
}

bool AEGraph::operator==(const AEGraph& other) const {
    return this->repr() == other.repr();
}

bool AEGraph::operator!=(const AEGraph& other) const {
    return this->repr() != other.repr();
}

AEGraph AEGraph::operator[](const int index) const {
    // offers an easier way of accessing the nested graphs
    if (index < num_subgraphs()) {
        return subgraphs[index];
    }

    if (index < num_subgraphs() + num_atoms()) {
        return AEGraph('(' + atoms[index - num_subgraphs()] + ')');
    }

    return AEGraph("()");
}

std::ostream& operator<<(std::ostream &out, const AEGraph &g) {
    out << g.repr();
    return out;
}

AEGraph::AEGraph(std::string representation) {
    // constructor that creates an AEGraph structure from a
    // serialized representation
    char left_sep = representation[0];
    char right_sep = representation[representation.size() - 1];

    assert((left_sep == '(' && right_sep == ')')
        || (left_sep == '[' && right_sep == ']'));

    // if the left separator is '(' then the AEGraph is the entire
    // sheet of assertion
    if (left_sep == '(') {
        is_SA = true;
    } else {
        is_SA = false;
    }

    // eliminate the first pair of [] or ()
    representation = representation.substr(1, representation.size() - 2);

    // split the graph into separate elements
    auto v = split_level(representation);
    // add them to the corresponding vector
    for (auto s : v) {
        if (s[0] != '[') {
            atoms.push_back(s);
        } else {
            subgraphs.push_back(AEGraph(s));
        }
    }

    // also internally sort the new graph
    this->sort();
}

std::string AEGraph::repr() const {
    // returns the serialized representation of the AEGraph

    std::string left, right;
    if (is_SA) {
        left = '(';
        right = ')';
    } else {
        left = '[';
        right = ']';
    }

    std::string result;
    for (auto subgraph : subgraphs) {
        result += subgraph.repr() + ", ";
    }

    int len = atoms.size();
    if (len != 0) {
        for (int i = 0; i < len - 1; i++) {
            result += atoms[i] + ", ";
        }
        result += atoms[len - 1];
    } else {
        if (subgraphs.size() != 0)
            return left + result.substr(0, result.size() - 2) + right;
    }

    return left + result + right;
}


void AEGraph::sort() {
    std::sort(atoms.begin(), atoms.end());

    for (auto& sg : subgraphs) {
        sg.sort();
    }

    std::sort(subgraphs.begin(), subgraphs.end());
}

bool AEGraph::contains(const std::string other) const {
    // checks if an atom is in a graph
    if (find(atoms.begin(), atoms.end(), other) != atoms.end())
        return true;

    for (const auto& sg : subgraphs)
        if (sg.contains(other))
            return true;

    return false;
}

bool AEGraph::contains(const AEGraph& other) const {
    // checks if a subgraph is in a graph
    if (find(subgraphs.begin(), subgraphs.end(), other) != subgraphs.end())
        return true;

    for (const auto& sg : subgraphs)
        if (sg.contains(other))
            return true;

    return false;
}

std::vector<std::vector<int>> AEGraph::get_paths_to(const std::string other)
    const {
    // returns all paths in the tree that lead to an atom like <other>
    std::vector<std::vector<int>> paths;

    int len_atoms = num_atoms();
    int len_subgraphs = num_subgraphs();

    for (int i = 0; i < len_atoms; i++) {
        if (atoms[i] == other && size() > 1) {
            paths.push_back({i + len_subgraphs});
        }
    }

    for (int i = 0; i < len_subgraphs; i++) {
        if (subgraphs[i].contains(other)) {
            auto r = subgraphs[i].get_paths_to(other);
            for (auto& v : r)
                v.insert(v.begin(), i);
            copy(r.begin(), r.end(), back_inserter(paths));
        }
    }

    return paths;
}

std::vector<std::vector<int>> AEGraph::get_paths_to(const AEGraph& other)
    const {
    // returns all paths in the tree that lead to a subgraph like <other>
    std::vector<std::vector<int>> paths;
    int len_subgraphs = num_subgraphs();

    for (int i = 0; i < len_subgraphs; i++) {
        if (subgraphs[i] == other && size() > 1) {
            paths.push_back({i});
        } else {
            auto r = subgraphs[i].get_paths_to(other);
            for (auto& v : r)
                v.insert(v.begin(), i);
            copy(r.begin(), r.end(), back_inserter(paths));
        }
    }
    return paths;
}

std::vector<std::vector<int>> AEGraph::possible_double_cuts() const {
    // este similara cu functia get_paths_to din schelet
    // doar ca la fiecare nod se verifica daca are doar un fiu
    // subgraf si nici un atom
    std::vector<std::vector<int>> paths;
    int n = num_subgraphs();

    for (int i = 0; i < n; i++) {
    	if (subgraphs[i].size() == 1 && subgraphs[i].num_subgraphs() == 1) {
    		paths.push_back({i});
    	}
    	auto r = subgraphs[i].possible_double_cuts();
    	for (auto& v : r) {
    		v.insert(v.begin(), i);
    	}
    	copy(r.begin(), r.end(), back_inserter(paths));
    }
    return paths;
}

AEGraph AEGraph::double_cut(std::vector<int> where) const {
    // elimina dublu-negarile stergand nodul
    // care are doar un subgraf-cupil si nici un atom-copil
    // a = graful curent
    // ind = primul element al vectorului where
    std::string x = repr();
    auto a = AEGraph(x);
    auto ind = where.begin();

    if (*ind != -1) {
        int index = *ind;
        // ultimul element din path este facut -1
        if (where.size() == 1) {
            *ind = -1;
        } else {
            where.erase(ind);
        }
        auto aux = subgraphs[index].double_cut(where);
        a.subgraphs.erase(a.subgraphs.begin() + index);
        std::string s = aux.repr();
        if (s[0] != '[') {
            s.erase(s.begin(), s.begin() + 1);
            s.erase(s.end() - 1, s.end());
            a.atoms.push_back(s);
            x = a.repr();
        } else {
            a.subgraphs.push_back(aux);
            x = a.repr();
        }
    } else {
        x.erase(x.begin(), x.begin() + 2);
        x.erase(x.end() - 2, x.end());
    }
    // ne asiguram ca atomii sunt si ei in paranteza
    if (x[0] != '[' && x[0] != '(') {
        x.insert(x.begin(), '(');
        x.insert(x.end(), ')');
    }
    return AEGraph(x);
}


std::vector<std::vector<int>> AEGraph::possible_erasures(int level) const {
    // path va fi matricea ce contiine drumurile
    // catre nodurile ce pot fi sterse
    std::vector<std::vector<int>> path;
    if (repr() == "()") {
        return {};
    }
    int len_subgraphs = subgraphs.size();

    for (int i = 0; i < len_subgraphs; i++) {
		auto r = subgraphs[i].possible_erasures(level + 1);
		for (auto& v : r) {
			v.insert(v.begin(), i);
		}
		copy(r.begin(), r.end(), back_inserter(path));
	}
    // doar nodurile de pe nivel par pot fi sterse
	if ((level + 2) % 2 == 1) {
		if (this->size() == 1 && !is_SA) {
			return path;
		}
		for (int i = 0; i < len_subgraphs; i++) {
			path.push_back({i});
		}
		int len_atoms = atoms.size();
		for (int i  = 0; i < len_atoms; i++) {
			path.push_back({len_subgraphs + i});
		}
	}
	return path;
}


AEGraph AEGraph::erase(std::vector<int> where) const {
    // sterge atomul/subgraful daca acesta poate fi sters
    std::string x = repr();
    auto a = AEGraph(x);
    auto ind = where.begin();
    int index = *ind;
    if (where.size() > 1) {
        where.erase(ind);
        auto aux = subgraphs[index].erase(where);
        a.subgraphs.erase(a.subgraphs.begin() + index);
        std::string s = aux.repr();
        if (s[0] != '[') {
            s.erase(s.begin(), s.begin() + 1);
            s.erase(s.end() - 1, s.end());
            a.atoms.push_back(s);
            x = a.repr();
        } else {
            a.subgraphs.push_back(aux);
            x = a.repr();
        }
    } else {
        int num = num_subgraphs();
        if (index >= num) {
            a.atoms.erase(a.atoms.begin() + index - num);
        } else {
            a.subgraphs.erase(a.subgraphs.begin() + index);
        }
        x = a.repr();
    }

    if (x[0] != '[' && x[0] != '(') {
        x.insert(x.begin(), '(');
        x.insert(x.end(), ')');
    }
    return AEGraph(x);
}

std::vector<std::vector<int>> AEGraph::possible_deiterations() const {
    // returneaza in matricea path toate drumurile
    // ce duc la deiterari posibile
    std::vector<std::vector<int>> path;

    int n = subgraphs.size();
    for (int i = 0; i < n; i++) {
    	auto r = get_paths_to(subgraphs[i]);
    	auto index = r.begin();
    	int x = 0;

    	for (auto it = r.begin(); it != r.end(); it++) {
    		if (it->size() == 1) {
    			index = it;
    			x++;
    		}
    	}
    	if (x == 1) {
    		r.erase(index);
    	}
    	copy(r.begin(), r.end(), back_inserter(path));
    	r = subgraphs[i].possible_deiterations();
    	for (auto& v : r) {
    		v.insert(v.begin(), i);
    	}
    	copy(r.begin(), r.end(), back_inserter(path));
    }
    n = atoms.size();
    for (int i = 0; i < n; i++) {
    	auto r = get_paths_to(atoms[i]);
    	auto index = r.begin();
    	int x = 0;
    	for (auto it = r.begin(); it != r.end(); it++) {
    		if (it->size() == 1) {
    			index = it;
    			x++;
    		}
    	}
    	if (x == 1) {
    		r.erase(index);
    	}
    	copy(r.begin(), r.end(), back_inserter(path));
    }
    for (auto i = path.begin(); i != path.end(); i++) {
    	path.erase(std::remove(i + 1, path.end(), *i), path.end());
    }
    return path;
}

AEGraph AEGraph::deiterate(std::vector<int> where) const {
    // deitereaza atomii/subgrafurile daca acesta pot fi sterse
    std::string x = repr();
    auto a = AEGraph(x);
    auto ind = where.begin();
    int index = *ind;
    if (where.size() > 1) {
        where.erase(ind);
        auto aux = subgraphs[index].deiterate(where);
        a.subgraphs.erase(a.subgraphs.begin() + index);
        std::string s = aux.repr();
        if (s[0] != '[') {
            s.erase(s.begin(), s.begin() + 1);
            s.erase(s.end() - 1, s.end());
            a.atoms.push_back(s);
            x = a.repr();
        } else {
            a.subgraphs.push_back(aux);
            x = a.repr();
        }
    } else {
        int num = num_subgraphs();
        if (index >= num) {
            a.atoms.erase(a.atoms.begin() + index - num);
        } else {
            a.subgraphs.erase(a.subgraphs.begin() + index);
        }
        x = a.repr();
    }

    if (x[0] != '[' && x[0] != '(') {
        x.insert(x.begin(), '(');
        x.insert(x.end(), ')');
    }
    return AEGraph(x);
}

