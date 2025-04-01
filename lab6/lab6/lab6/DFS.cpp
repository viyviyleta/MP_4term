#include "DFS.h"
#include "algorithm"
#define NINF 0x80000000
#define INF  0x7fffffff
void DFS::init(const graph::AList& al)
{
	this->al = &al;
	this->c = new Color[this->al->n_vertex];
	this->d = new int[this->al->n_vertex];
	this->f = new int[this->al->n_vertex];
	this->p = new int[this->al->n_vertex];
	this->t = 0;
	for (int i = 0; i < this->al->n_vertex; i++)
	{
		this->c[i] = WHITE;
		this->d[i] = this->f[i] = 0;
		this->p[i] = NIL;
	};
	for (int i = 0; i < this->al->n_vertex; i++)
		if (this->c[i] == WHITE)
		{
			this->visit(i);
		}
};
DFS::DFS(const graph::AList& al) { this->init(al); };
DFS::DFS(const graph::AMatrix& am)
{
	this->init(*(new graph::AList(am)));
};
void DFS::visit(int u)
{
	this->c[u] = GRAY;
	this->d[u] = ++(this->t);

	std::vector<int> neighbors;
	for (int j = 0; j < this->al->size(u); j++)
		neighbors.push_back(this->al->get(u, j));

	std::sort(neighbors.rbegin(), neighbors.rend());

	for (int v : neighbors)
	{
		if (this->c[v] == WHITE)
		{
			this->p[v] = u;
			this->visit(v);
		}
	}

	this->c[u] = BLACK;
	this->f[u] = ++(this->t);

	this->topological_sort.push_back(u);
}


int DFS::get(int i)
{
	std::vector<std::pair<int, int>> order;
	for (int k = 0; k < this->al->n_vertex; k++)
		order.push_back({ this->f[k], k });

	std::sort(order.rbegin(), order.rend());

	return order[i].second;
}

