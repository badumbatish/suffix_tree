#include <iostream>
#include "suffix_tree.h"
void YN(bool b) {
	if(b==true) std::cout << "Yes" << std::endl;
	else std::cout << "No" << std::endl;
}

int main() {
	suffix_tree t;
	std::string str="panamabananas$";
	t.build_tree(str);
	std::string temp="";
	t.dfs(t.root,temp);
	/*
	std::stack<sf_node*> s;
	t.find_branch(t.root,s);
	while(!s.empty()) {
		sf_node* link = s.top();
		s.pop();
		for(auto i : link->mp ) {
			std::cout << i.first <<  " ";
		}
		std::cout << std::endl;
	}
	*/
	return 0;
}