#pragma once
#include <vector>
#include <stdint.h>

namespace SGF
{
	class Actor;

	class WeightedGraph
	{
		struct Node;
		struct Edge
		{
			Node* from_;
			Node* to_;
			float weight_;
		};

		struct Node
		{
			Actor* object_;
			std::vector<Edge*> edges_;
			struct Pathdata
			{
				Edge* parentEdge_ = nullptr;
				float h_ = 0.0f;
				float g_ = 0.0f;
				float f_ = 0.0f;
				bool inOpenSet_ = false;
				bool inClosedSet_ = false;
			} pathData_;
		};

	public:
		bool findPath(Node* start, Node* goal);
		void resize(size_t newSize) { graph_.resize(newSize); }

	private:
		std::vector<Node*> graph_;
	};
}