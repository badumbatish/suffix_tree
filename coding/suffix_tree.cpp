#include "suffix_tree.h"

void suffix_tree::insert(const std::string& str) {
    insert(str,0,str.length());
}

void suffix_tree::insert(const std::string& str,size_t start, size_t end) {
	assert(end-start<=str.length() && "Length of string is smaller than end-start, will possibly have undefined behavior");
	size_t i=start;
	sf_node *link=root;

	for(;i<end;i++) {
		if(link->mp[str[i]]==nullptr) link->mp[str[i]]=new sf_node;
		link=link->mp[str[i]];
	}
	link->start=start;
    link->length=end-start;

    return;
}

bool suffix_tree::search(const std::string& str) {
    return search(str,0,str.length());
}


bool suffix_tree::search(const std::string& str,size_t start, size_t end) {
	size_t i=start;
	sf_node *link=root;
	for(i=0;i<end;i++) {
		if(link->mp[str[i]]==nullptr) return false;
		link=link->mp[str[i]];
	}
    if(!(link->start==0 && link->length==0)) {
        return true;
    }
    return false;
}

void suffix_tree::build_trie(const std::string& str) {
    for(size_t i=0;i<str.length()-1;i++) {
        insert(str,i,str.length());
    }
    return;
}

void suffix_tree::build_tree(const std::string& str) {
    build_trie(str);
    std::stack<sf_node*> s;
    find_branch(root,s);
    compress_trie(s);

}

void suffix_tree::compress_trie(std::stack<sf_node*>& s) {
    sf_node* link = s.top();
    s.pop();
    for(auto i : link->mp) {
        reduce(i.second);
    }
}

void suffix_tree::find_branch(sf_node* head, std::stack<sf_node*>& s) {
    if(head->mp.size() > 1 ) s.push(head);
    for(auto i : head->mp) {
        find_branch(i.second,s);
    }
}

void suffix_tree::reduce(sf_node* head) {
    sf_node* link = head; 
    std::stack<sf_node*>  s;
    while(link->mp.size() != 1 ) {
        link=link->mp.begin()->second;
        s.push(link);
    }
    if(s.empty()) return;
    sf_node* tail;
    
    tail = s.top(); 
    s.pop();



    // Ensure to have head and tail
    // Release memory of nodes
    if(s.empty()) return;

    sf_node* dummyNode;
    while(!s.empty()) {
        dummyNode = s.top(); s.pop();
        delete dummyNode;
    }

    // Connect link and tail together
    head->mp.begin()->second = tail;
    return;
}