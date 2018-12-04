main:
	g++ *.cpp -o main

treeNode.o: treeNode.cpp treeNode.h
	g++ treeNode.cpp treeNode.h -c

treeLeaf.o: treeLeaf.cpp treeLeaf.h
	g++ treeLeaf.cpp treeLeaf.h -c

B_Tree.o: B_Tree.cpp B_Tree.h
	g++ B_Tree.cpp B_Tree.h -c

