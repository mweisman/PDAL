/*=============================================================================
    Copyright (C) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <boost/detail/lightweight_test.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/type_traits/is_same.hpp>
#include <string>

#if !defined(FUSION_AT)
#define FUSION_AT at_c
#endif

#if !defined(FUSION_SIZE)
#define FUSION_SIZE pdalboost::fusion::result_of::size
#endif

template <typename S1, typename S2>
struct is_same
{
};

struct test_intrinsics1
{
    // test at, begin, end, next, prior, advance, size, deref, etc.

    typedef pdalboost::fusion::FUSION_SEQUENCE<int, float, bool, char> sequence;
    typedef pdalboost::mpl::begin<sequence>::type first;
    typedef pdalboost::mpl::next<first>::type second;
    typedef pdalboost::mpl::next<second>::type third;
    typedef pdalboost::mpl::next<third>::type fourth;
    typedef pdalboost::mpl::end<sequence>::type last;

    BOOST_STATIC_ASSERT((pdalboost::is_same<
        pdalboost::mpl::deref<first>::type, int>::value));

    BOOST_STATIC_ASSERT((pdalboost::is_same<
        pdalboost::mpl::deref<second>::type, float>::value));

    BOOST_STATIC_ASSERT((pdalboost::is_same<
        pdalboost::mpl::deref<third>::type, bool>::value));

    BOOST_STATIC_ASSERT((pdalboost::is_same<
        pdalboost::mpl::deref<fourth>::type, char>::value));

    BOOST_STATIC_ASSERT((pdalboost::is_same<
        pdalboost::mpl::at_c<sequence, 2>::type, bool>::value));

    BOOST_STATIC_ASSERT((pdalboost::is_same<
        pdalboost::mpl::front<sequence>::type, int>::value));

    BOOST_STATIC_ASSERT((pdalboost::is_same<
        pdalboost::mpl::deref<
            pdalboost::mpl::advance_c<second, 2>::type>::type, char>::value));

    BOOST_STATIC_ASSERT((pdalboost::mpl::size<sequence>::value == 4));
    BOOST_STATIC_ASSERT(!(pdalboost::mpl::empty<sequence>::value));
    BOOST_STATIC_ASSERT((pdalboost::mpl::distance<second, fourth>::value == 2));

#if !defined(FUSION_FORWARD_ONLY) // list has no back/prev

    typedef pdalboost::mpl::prior<last>::type fourth_;
    typedef pdalboost::mpl::prior<fourth_>::type third_;
    typedef pdalboost::mpl::prior<third_>::type second_;
    typedef pdalboost::mpl::prior<second_>::type first_;

    BOOST_STATIC_ASSERT((pdalboost::is_same<
        pdalboost::mpl::deref<first_>::type, int>::value));

    BOOST_STATIC_ASSERT((pdalboost::is_same<
        pdalboost::mpl::deref<second_>::type, float>::value));

    BOOST_STATIC_ASSERT((pdalboost::is_same<
        pdalboost::mpl::deref<third_>::type, bool>::value));

    BOOST_STATIC_ASSERT((pdalboost::is_same<
        pdalboost::mpl::deref<fourth_>::type, char>::value));

    BOOST_STATIC_ASSERT((pdalboost::is_same<
        pdalboost::mpl::back<sequence>::type, char>::value));

#endif
};

struct test_intrinsics2
{
    typedef pdalboost::fusion::FUSION_SEQUENCE<> seq0;

#if !defined(FUSION_FORWARD_ONLY) // list has no back/prev

    typedef pdalboost::fusion::FUSION_SEQUENCE<int> target1;
    typedef pdalboost::mpl::push_back<seq0, int>::type seq1;
    BOOST_STATIC_ASSERT((pdalboost::mpl::equal<seq1, target1>::value));

    typedef pdalboost::fusion::FUSION_SEQUENCE<int, double> target2;
    typedef pdalboost::mpl::push_back<seq1, double>::type seq2;
    BOOST_STATIC_ASSERT((pdalboost::mpl::equal<seq2, target2>::value));

#endif

    typedef pdalboost::fusion::FUSION_SEQUENCE<int> target3;
    typedef pdalboost::mpl::push_front<seq0, int>::type seq3;
    BOOST_STATIC_ASSERT((pdalboost::mpl::equal<seq3, target3>::value));

    typedef pdalboost::fusion::FUSION_SEQUENCE<double, int> target4;
    typedef pdalboost::mpl::push_front<seq3, double>::type seq4;
    BOOST_STATIC_ASSERT((pdalboost::mpl::equal<seq4, target4>::value));
};

void
test()
{
    using namespace pdalboost::fusion;

    {   // testing const sequences

        const FUSION_SEQUENCE<int, float> t1(5, 3.3f);
        BOOST_TEST(FUSION_AT<0>(t1) == 5);
        BOOST_TEST(FUSION_AT<1>(t1) == 3.3f);
    }

    {   // testing at<N> works with MPL integral constants
        const FUSION_SEQUENCE<int, char> t1(101, 'z');
        BOOST_TEST(pdalboost::fusion::at<pdalboost::mpl::int_<0> >(t1) == 101);
        BOOST_TEST(pdalboost::fusion::at<pdalboost::mpl::int_<1> >(t1) == 'z');
        // explicitly try something other than mpl::int_
        BOOST_TEST((pdalboost::fusion::at<pdalboost::mpl::integral_c<long, 0> >(t1) == 101));
        BOOST_TEST((pdalboost::fusion::at<pdalboost::mpl::integral_c<long, 1> >(t1) == 'z'));
    }

    {   // testing size & empty

        typedef FUSION_SEQUENCE<int, float, double> t1;
        typedef FUSION_SEQUENCE<> t2;

        BOOST_STATIC_ASSERT(FUSION_SIZE<t1>::value == 3);
        BOOST_STATIC_ASSERT(FUSION_SIZE<t2>::value == 0);
        BOOST_STATIC_ASSERT(!pdalboost::fusion::result_of::empty<t1>::value);
        BOOST_STATIC_ASSERT(pdalboost::fusion::result_of::empty<t2>::value);
    }

    {   // testing front & back

        typedef FUSION_SEQUENCE<int, float, std::string> tup;
        tup t(1, 2.2f, "Kimpo");

        BOOST_TEST(front(t) == 1);
#if !defined(FUSION_FORWARD_ONLY) // list has no back
        BOOST_TEST(back(t) == "Kimpo");
#endif
    }

    {   // testing is_sequence

        typedef FUSION_SEQUENCE<int, float, double> t1;
        typedef FUSION_SEQUENCE<> t2;
        typedef FUSION_SEQUENCE<char> t3;

        BOOST_STATIC_ASSERT(traits::is_sequence<t1>::value);
        BOOST_STATIC_ASSERT(traits::is_sequence<t2>::value);
        BOOST_STATIC_ASSERT(traits::is_sequence<t3>::value);
        BOOST_STATIC_ASSERT(!traits::is_sequence<int>::value);
        BOOST_STATIC_ASSERT(!traits::is_sequence<char>::value);
    }

    {   // testing mpl compatibility

        // test begin, end, next, prior, advance, size, deref, etc.
        //~ typedef FUSION_SEQUENCE<int, float, bool, char> tuple_type;
        //~ test_intrinsics1<tuple_type> test1;
        //~ (void)test1; // prevent unused variable warning

        // test an algorithm
        typedef FUSION_SEQUENCE<int, float, double> t1;
        typedef pdalboost::mpl::find<t1, float>::type iter;
        typedef pdalboost::mpl::deref<iter>::type type;
        BOOST_STATIC_ASSERT((pdalboost::is_same<type, float>::value));

    }
}
