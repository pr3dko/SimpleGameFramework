#include "Graph.h"
#include "Math.h"
#include "Actor.h"
#include <algorithm>

namespace SGF
{
	bool WeightedGraph::findPath(Node* start, Node* goal)
	{
		// Reset g and set membership for every node
		for (auto node : graph_)
		{
			node->pathData_.g_ = 0.0f;
			node->pathData_.inOpenSet_ = false;
			node->pathData_.inClosedSet_ = false;
		}

		std::vector<Node*> openSet;

		Node* current = goal;
		current->pathData_.inClosedSet_ = true;

		do
		{
			for (Edge* edge : current->edges_)
			{
				Node* neighbour = edge->to_;

				if (!neighbour->pathData_.inClosedSet_)
				{
					if (!neighbour->pathData_.inOpenSet_)
					{
						neighbour->pathData_.parentEdge_ = edge;
						neighbour->pathData_.h_ = Math::Heuristic::euclideanDistance(neighbour->object_->getPosition(), start->object_->getPosition());
						neighbour->pathData_.g_ = edge->from_->pathData_.g_ + edge->weight_;
						neighbour->pathData_.f_ = neighbour->pathData_.g_ + neighbour->pathData_.h_;
						neighbour->pathData_.inOpenSet_ = true;
						openSet.emplace_back(neighbour);
					}
					else
					{
						float newG = edge->from_->pathData_.g_ + edge->weight_;
						if (newG < neighbour->pathData_.g_)
						{
							neighbour->pathData_.parentEdge_ = edge;
							neighbour->pathData_.g_ = newG;
							neighbour->pathData_.f_ = neighbour->pathData_.g_ + neighbour->pathData_.h_;
						}
					}
				}
			}

			if (openSet.empty())
			{
				break;
			}

			auto iter = std::min_element(openSet.begin(), openSet.end(),
				[=](Node* a, Node* b) {return a->pathData_.f_ < b->pathData_.f_; });

			current = *iter;
			openSet.erase(iter);
			current->pathData_.inOpenSet_ = false;
			current->pathData_.inClosedSet_ = true;
		} while (current != start);
		
		return current == start;
	}
}