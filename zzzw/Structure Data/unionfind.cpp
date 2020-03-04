//并查集是一种描述集合之间关系的数据结构， 支持的操作有：1。查询a祖先 2.查询a和b的关系 3.合并集合 
#include <iostream>
#include <cstdio>
using namespace std;

int fam[10050];

//询问祖先
int anc(int x)
{
	if(fam[x] == x) return x;
	return fam[x] = anc(fam[x]);
}

//询问关系
int ask(int x, int y)
{
	return anc(x) == anc(y);
}

//合并
void uni(int x, int y)
{
		if(anc(x) != anc(y))	fam[anc(x)] = anc(y);
}

int main(int argc, char *argv[]) {

}