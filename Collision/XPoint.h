#pragma once


#include "Primitive.h"
#include "Barycentric.h"


namespace Collision_NS
{
  //
  //  Intersection primitive
  //


  struct XVert;
  struct XEdge;
  struct XFace;


  struct BadUpcast;


  struct XVert : public Vert, public BaryV
  {
    XVert( Vert v ) : Vert{ v } {}

    XEdge toXEdge( Edge ) const;
    XFace toXFace( Face ) const;
  };


  struct XEdge : public Edge, public BaryE
  {
    XEdge( Edge e, Int u, Int v ) : Edge{ e }, BaryE{ u, v } {}

    XFace toXFace( Face ) const;
  };


  struct XFace : public Face, public BaryF
  {
    XFace( Face f, Int a, Int b, Int c ) : Face{ f }, BaryF{ a, b, c } {}

    XFace toXFace( Face ) const;
  };


  struct BadUpcast : std::exception
  {
    BadUpcast( size_t from, size_t to ) : from{ from }, to{ to } {}

    virtual const char* what() const override { return "Upcast intersection primitive X to unrelated primitive Y"; }

    const size_t from;
    const size_t to;
  };


  const Math_NS::Vector3D point( const XVert& );
  const Math_NS::Vector3D point( const XEdge& );


  //
  //  Intersection point as a pair of two intersecting primitives
  //


  template <typename A, typename B>
  struct XPoint : std::pair<A, B> { using std::pair<A, B>::pair; };

  template <typename A, typename B>
  XPoint<A, B> makeXPoint( const A& a, const B& b ) { return std::make_pair( a, b ); }


  //
  //  Intersection point id
  //


  struct XPointID : std::pair<size_t, size_t> { using std::pair<size_t, size_t>::pair; };

  inline XPointID makeXPointID( size_t a, size_t b ) { return std::make_pair( a, b ); }

  template <typename A, typename B>
  XPointID makeXPointID( const A& a, const B& b ) { return makeXPointID( id( a ), id( b ) ); }

  template <typename A, typename B>
  XPointID makeXPointID( const XPoint<A, B>& p ) { return makeXPointID( p.first, p.second ); }


  template <typename A, typename B>
  bool operator < ( const XPoint<A, B>& l, const XPoint<A, B>& r ) { return makeXPointID( l ) < makeXPointID( r ); }

  template <typename A, typename B>
  bool operator == ( const XPoint<A, B>& l, const XPoint<A, B>& r ) { return makeXPointID( l ) == makeXPointID( r ); }

  //
  //  Intersection point coordinates in global space
  //


  Math_NS::Vector3D point( const XVert&, const XVert& );
  Math_NS::Vector3D point( const XVert&, const XEdge& );
  Math_NS::Vector3D point( const XVert&, const XFace& );
  Math_NS::Vector3D point( const XEdge&, const XVert& );
  Math_NS::Vector3D point( const XEdge&, const XEdge& );
  Math_NS::Vector3D point( const XEdge&, const XFace& );
  Math_NS::Vector3D point( const XFace&, const XVert& );
  Math_NS::Vector3D point( const XFace&, const XEdge& );


  template <typename A, typename B>
  Math_NS::Vector3D point( const XPoint<A, B>& p ) { return point( p.first, p.second ); }
}
