#pragma once
#include "includer.h"
#include <iostream>

struct sf_node {
    std::map<char,sf_node*> mp;
    size_t start;
    size_t length;

    ~sf_node() {
        for(auto i : mp) {
            //std::cout << "YES "<< std::endl;
            delete i.second;
        }
    }

};


class suffix_tree {
private:
    
public:
    sf_node* root;
    std::string str;
    suffix_tree() {
        root= new sf_node;
        //std::cout << root << std::endl;
    }
    void insert(const std::string& str);
        void insert(const std::string& str,size_t start,size_t end);

    bool search(const std::string& str);
        bool search(const std::string& str,size_t start, size_t end);

    bool search2(const std::string& str);

    void build_tree(const std::string& str);
        void build_trie(const std::string& str);
        void find_branch(sf_node* link, std::stack<sf_node*>& s);
        void compress_trie(std::stack<sf_node*>& s);
            void reduce(sf_node* &head);
    

    void dfs(sf_node* node, std::string& str) {
        sf_node* link = node;
        for(auto it : link->mp){
            //std::cout << it->first << std::endl;
            str.push_back(it.first);
            if(!(it.second->start == it.second->length && it.second->start==0)) {
                //print(this->str,it.second->start,it.second->length);
                std::cout << str << " ";
            }
            dfs(it.second,str);
            str.pop_back();
            }
        return;
    }   

    void print(std::string& str,size_t start, size_t end) {
        for(size_t i=start;i<start+end;i++) {
            std::cout << str[i];
        }
        std::cout << std::endl;
    }

    ~suffix_tree() {
        delete root;
    }
};
