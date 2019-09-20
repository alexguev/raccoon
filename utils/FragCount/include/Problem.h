#pragma once

#include "Mesh.h"
#include "Cluster.h"
#include "ProblemDefinition.h"

class Problem
{
public:
  Problem(const char * filename);
  ~Problem()
  {
    delete _mesh;
    delete _all;
    delete _unclassified;
    delete _intact;
    delete _broken;
    for (size_t i = 0; i < _clusters.size(); i++)
      delete _clusters[i];
  }
  void plotDamage();
  void plotBoundaryElems();
  void classifyAllTimes();
  void PCA();
  int numTimeSteps() { return _mesh->numTimeSteps(); }
  void goToTimeStep(int step)
  {
    _clusters_pending_update = _mesh->readDamageAtStep(step);
    _step = step;
  }
  void reinitClusters();
  void dessociateBroken();
  void associateBroken();
  void decluster();
  void statistics();
  void reclassify();
  void classify();

protected:
private:
  Mesh * _mesh;

  /// number of elements
  size_t _num_elems;

  /// all elems
  Cluster * _all;

  /// queue: unclassified elements
  Cluster * _unclassified;

  /// queue: good unclassified elements
  Cluster * _intact;

  /// queue: bad elements
  Cluster * _broken;

  /// vector of classified Clusters
  std::vector<Cluster *> _clusters;

  /// vector of boundary Clusters
  std::vector<Cluster *> _boundary_clusters;

  /// Clusters pending update after damage changed
  std::set<size_t> _clusters_pending_update;

  /// number of Clusters
  size_t _num_fragments;

  /// mean
  double _mean;

  /// std
  double _sigma;

  /// step
  int _step;
};