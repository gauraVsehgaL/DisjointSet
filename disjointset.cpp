//Reference : https://www.geeksforgeeks.org/union-find-algorithm-set-2-union-by-rank/
//	Use Cases : Detect cycle in graph (two nodes of an edge should belong to the same set)
//				Two members belong to same set.

#include <vector>
#include <algorithm>
class DisjointSet
{
private:
	size_t Count;
	std::vector<size_t> Parent;
	std::vector<size_t> Rank;
public:
	DisjointSet(size_t N) :Count(N)
	{
		Parent.resize(Count);
		std::generate(Parent.begin(), Parent.end(), []() {static size_t i = 0; return i++; });	//Initially every element is a separate set.
		Rank.resize(Count, 1);	//Initially every set has a rank as 1.
	}

	size_t Find(size_t Member)
	{
		if (Parent[Member] == Member)
			return Member;
		auto ActualParent = Find(Parent[Member]);
		Parent[Member] = ActualParent;				//Path Compression(optimization number 1).
		return ActualParent;
	}

	void Union(size_t Member1, size_t Member2)
	{
		auto ParentMember1 = Find(Member1);
		auto ParentMember2 = Find(Member2);

		if (ParentMember1 == ParentMember2)
			return;			//Already have same representative.

		auto RankParent1 = Rank[ParentMember1];
		auto RankParent2 = Rank[ParentMember2];
		//	Union by Rank(Optimization number 2).
		if (RankParent1 < RankParent2)
			Parent[ParentMember1] = ParentMember2;
		else if (RankParent1 > RankParent2)
			Parent[ParentMember2] = ParentMember1;
		else
		{
			Parent[ParentMember1] = ParentMember2;
			Rank[ParentMember2]++;
		}
	}
};