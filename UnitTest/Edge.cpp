#include "stdafx.h"
#include "CppUnitTest.h"
#include <set>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{
  TEST_CLASS( Edge )
  {
  public:

    TEST_METHOD( Label )
    {
      QEdge_NS::Shape s;

      {
        QEdge_NS::Edge e = s.makeEdge();

        label( e, L"e" );

        Assert::AreEqual<std::wstring>( L"e.o", e.o()->tag() );
        Assert::AreEqual<std::wstring>( L"e.d", e.d()->tag() );
        Assert::AreEqual<std::wstring>( L"e.l", e.l()->tag() );
        Assert::AreEqual<std::wstring>( L"e.l", e.r()->tag() );
      }

      {
        QEdge_NS::Edge e = s.makeLoop();

        label( e, L"e" );

        Assert::AreEqual<std::wstring>( L"e.o", e.o()->tag() );
        Assert::AreEqual<std::wstring>( L"e.o", e.d()->tag() );
        Assert::AreEqual<std::wstring>( L"e.l", e.l()->tag() );
        Assert::AreEqual<std::wstring>( L"e.r", e.r()->tag() );
      }
    }

    TEST_METHOD( EmptyEdge )
    {
      QEdge_NS::Edge e;
      Assert::IsFalse( e );

      QEdge_NS::Edge c = e;
      Assert::IsFalse( c );

      Assert::IsFalse( c = e );
    }

    TEST_METHOD( NonEmptyEdge )
    {
      QEdge_NS::Shape s;

      QEdge_NS::Edge e = s.makeEdge();

      Assert::IsTrue( e );

      QEdge_NS::Edge c = e;
      Assert::IsTrue( c );

      Assert::IsTrue( c = e );
    }
    
    TEST_METHOD( EdgeNavigation )
    {
      QEdge_NS::Shape s;
      QEdge_NS::Edge e = s.makeEdge();

      label( e, L"edge" );

      Assert::AreEqual( e, e.oNext(), L"oNext" );
      Assert::AreEqual( e, e.oPrev(), L"oPrev" );
      Assert::AreEqual( e, e.dNext(), L"dNext" );
      Assert::AreEqual( e, e.dPrev(), L"dPrev" );

      Assert::AreNotEqual( e, e.sym(), L"sym" );
      Assert::AreEqual( e, e.sym().sym(), L"sym^2" );

      Assert::AreEqual( e.sym(), e.lNext(), L"lNext" );
      Assert::AreEqual( e.sym(), e.lPrev(), L"lPrev" );
      Assert::AreEqual( e.sym(), e.rNext(), L"rNext" );
      Assert::AreEqual( e.sym(), e.rPrev(), L"rPrev" );
    }

    TEST_METHOD( LoopNavigation )
    {
      QEdge_NS::Shape s;
      QEdge_NS::Edge e = s.makeLoop();

      label( e, L"loop" );

      Assert::AreEqual( e.sym(), e.oNext(), L"oNext" );
      Assert::AreEqual( e.sym(), e.oPrev(), L"oPrev" );
      Assert::AreEqual( e.sym(), e.dNext(), L"dNext" );
      Assert::AreEqual( e.sym(), e.dPrev(), L"dPrev" );

      Assert::AreNotEqual( e, e.sym(), L"sym" );
      Assert::AreEqual( e, e.sym().sym(), L"sym^2" );

      Assert::AreEqual( e, e.lNext(), L"lNext" );
      Assert::AreEqual( e, e.lPrev(), L"lPrev" );
      Assert::AreEqual( e, e.rNext(), L"rNext" );
      Assert::AreEqual( e, e.rPrev(), L"rPrev" );
    }

    TEST_METHOD( EdgeCtor )
    {
      QEdge_NS::Shape s;
      QEdge_NS::Edge e = s.makeLoop();

      label( e );

      {
        QEdge_NS::Edge c = e;
        Assert::AreEqual( e, c );
      }

      {
        QEdge_NS::Edge c;

        Assert::AreNotEqual( e, c );
        c = e;
        Assert::AreEqual( e, c );
      }
    }


    TEST_METHOD( Id )
    {
      QEdge_NS::Shape s;

      auto e = s.makeEdge();

      Assert::AreEqual( e.id(), e.id() );
      Assert::AreNotEqual( e.id(), e.sym().id() );

      Assert::AreEqual( e.l().id(), e.r().id() );
      Assert::AreNotEqual( e.o().id(), e.d().id() );

      std::set<size_t> all = 
      {
        e.id(), e.sym().id(),
        e.o().id(), e.d().id(),
        e.l().id(), e.r().id()
      };

      Assert::AreEqual( 5u, all.size() );
    }
  };
}