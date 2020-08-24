#include <iostream>
#include "suffix_tree.h"
void YN(bool b) {
	if(b==true) std::cout << "Yes" << std::endl;
	else std::cout << "No" << std::endl;
}

int main() {
	suffix_tree t;
	std::string str="Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.$";
	t.build_tree(str);
	YN(t.search2("Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum"));

	/*
	std::string temp;
	t.dfs(t.root,temp);
	*/
	return 0;
}