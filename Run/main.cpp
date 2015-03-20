#include <iostream>
#include "..\Collision\Collider.h"
#include "..\IO\STL.h"
#include "..\IO\Mesh.h"
#include "..\QEdge\Utils.h"
#include <chrono>


void main() try
{
  auto t0 = std::chrono::high_resolution_clock::now();

  QEdge_NS::Shape a = IO_NS::readSTL( L"box.stl" );
  QEdge_NS::Shape b = IO_NS::readSTL( L"triple torus.stl" );

  auto fa = QEdge_NS::allFaces( a );
  auto fb = QEdge_NS::allFaces( b );
  auto ea = QEdge_NS::allEdges( a );
  auto eb = QEdge_NS::allEdges( b );

  Collision_NS::Collider collider;

  for( auto pa : fa ) for( auto pb : eb ) collider( Collision_NS::Face( pa ), Collision_NS::Edge( pb ) );
  for( auto pa : ea ) for( auto pb : fb ) collider( Collision_NS::Edge( pa ), Collision_NS::Face( pb ) );

  IO_NS::writeMesh( collider.graph(), L"box box intersection.mesh" );

  auto t1 = std::chrono::high_resolution_clock::now();

  std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>( t1 - t0 ).count() << " ms" << std::endl;
}
catch( const std::exception& e )
{
  std::cout << e.what() << std::endl;
}
catch( ... )
{
  std::cout << "(unknown error)" << std::endl;
}