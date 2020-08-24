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
    std::cout << i << std::endl;
    if(!(link->start==0 && link->length==0)) {
        return true;
    }
    return false;
}

void suffix_tree::build_trie(const std::string& str) {
    for(size_t i=0;i<str.length();i++) {
        //std::cout << i << " " << str.length() << std::endl;
        insert(str,i,str.length());
    }
    return;
}

void suffix_tree::build_tree(const std::string& str) {
    this->str=str;
    build_trie(str);
    std::stack<sf_node*> s;
    find_branch(root,s);
    compress_trie(s);

}

void suffix_tree::compress_trie(std::stack<sf_node*>& s) {
    //std::cout << s.size() << std::endl;
    sf_node* link;
    while(!s.empty()) {
        link = s.top();
        s.pop();
        // link is a, an(a), n(a)
        //std::cout << link->mp.begin()->first << std::endl;
        for(auto it=link->mp.begin();it!=link->mp.end();it++) {
            reduce(it->second);
        }
    }

}

void suffix_tree::find_branch(sf_node* head, std::stack<sf_node*>& s) {
    if(head->mp.size() > 1) s.push(head);
    for(auto i : head->mp) {
        find_branch(i.second,s);
    }
}

bool suffix_tree::search2(const std::string& str) {
    size_t i=0;
    sf_node* link=root;
    sf_node* prev = link;
    while(i<str.length()) {
        for(;;) {
            if(!i<str.length()) return true;

            if(link->mp[str[i]]) {
                prev=link;
                link=link->mp[str[i]];
                i++;
            }
            else break;
        }
        if(prev->mp.empty()) return false;
        else {
            size_t start=link->mp.begin()->second->start;
            size_t length=link->mp.begin()->second->length;
            for(;i<str.length() && start<start+length;) {
                if(str[i]==this->str[start]) {
                    start++;
                    i++;
                }
                else return false;
            }
        }
    }
    return true;
}


void suffix_tree::reduce(sf_node* &head) {
    sf_node* link = head; 
    std::stack<sf_node*>  s;
    while(link->mp.size() == 1 ) {
        link=link->mp.begin()->second;
        s.push(link);
    }
    
    
    if(s.empty()) return;
    //s.pop();
    sf_node* tail;
    if(s.empty()) return;
    tail = s.top(); 
    s.pop();
    if(s.empty()) return;
    link= s.top();
    s.pop();
    link->mp.begin()->second=nullptr;

    
    
    delete head;
    // Connect link and tail together
    head= tail;
    return;
}