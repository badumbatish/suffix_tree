#pragma once
#include "includer.h"
#include <iostream>

struct sf_node {
    std::map<char,sf_node*> mp;
    size_t start;
    size_t length;

    ~sf_node() {
        for(auto i : mp) {
            delete i.second;
        }
    }

};


class suffix_tree {
private:
    
public:
    sf_node* root;

    suffix_tree() {
        root= new sf_node;
        //std::cout << root << std::endl;
    }
    void insert(const std::string& str);
        void insert(const std::string& str,size_t start,size_t end);

    bool search(const std::string& str);
        bool search(const std::string& str,size_t start, size_t end);

    bool search2(const std::string& str) {
        
    }

    void build_tree(const std::string& str);
        void build_trie(const std::string& str);
        void find_branch(sf_node* link, std::stack<sf_node*>& s);
        void compress_trie(std::stack<sf_node*>& s);
            void reduce(sf_node* head);
    
    ~suffix_tree() {
        delete root;
    }
};
