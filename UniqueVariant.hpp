#pragma once

#include <cstring>
#include <new>

namespace stilzdev
{
namespace detail
{

template <unsigned Positive, unsigned Negative, bool Test> struct Condition;

template <unsigned Positive, unsigned Negative> struct Condition<Positive, Negative, true> {
    static const unsigned value = Positive;
};

template <unsigned Positive, unsigned Negative> struct Condition<Positive, Negative, false> {
    static const unsigned value = Negative;
};

template <unsigned First, unsigned Second> struct StaticMax {
    static const unsigned value = Condition<First, Second, (First > Second)>::value;
};

// Purpose of EmptyBase: to provide common interface to empty types.
class EmptyBase { };

// Purpose of EmptyType: to provide an empty type that can be used as template parameter.
// Template non-type parameter is used to differentiate empty types.
template <unsigned Id> class EmptyType : private EmptyBase { };

// Purpose: To wrap arbitary type and bind a tag to it (kind of RTTI emulation, but compile-time).
class TypeWrapperBase {
    const int m_tagValue;
protected:
    explicit TypeWrapperBase(int tagValue) : m_tagValue(tagValue) { }
public:
    unsigned getTagValue() const { return m_tagValue; }
    virtual ~TypeWrapperBase() { }
};

} // namespace detail


// Purpose: A compile-time checking unique variant class that supports up to 100 types.
template <
    typename T1,
    typename T2 = detail::EmptyType<2>, typename T3 = detail::EmptyType<3>, typename T4 = detail::EmptyType<4>,
    typename T5 = detail::EmptyType<5>, typename T6 = detail::EmptyType<6>, typename T7 = detail::EmptyType<7>,
    typename T8 = detail::EmptyType<8>, typename T9 = detail::EmptyType<9>, typename T10 = detail::EmptyType<10>,
    typename T11 = detail::EmptyType<11>, typename T12 = detail::EmptyType<12>, typename T13 = detail::EmptyType<13>,
    typename T14 = detail::EmptyType<14>, typename T15 = detail::EmptyType<15>, typename T16 = detail::EmptyType<16>,
    typename T17 = detail::EmptyType<17>, typename T18 = detail::EmptyType<18>, typename T19 = detail::EmptyType<19>,
    typename T20 = detail::EmptyType<20>, typename T21 = detail::EmptyType<21>, typename T22 = detail::EmptyType<22>,
    typename T23 = detail::EmptyType<23>, typename T24 = detail::EmptyType<24>, typename T25 = detail::EmptyType<25>,
    typename T26 = detail::EmptyType<26>, typename T27 = detail::EmptyType<27>, typename T28 = detail::EmptyType<28>,
    typename T29 = detail::EmptyType<29>, typename T30 = detail::EmptyType<30>, typename T31 = detail::EmptyType<31>,
    typename T32 = detail::EmptyType<32>, typename T33 = detail::EmptyType<33>, typename T34 = detail::EmptyType<34>,
    typename T35 = detail::EmptyType<35>, typename T36 = detail::EmptyType<36>, typename T37 = detail::EmptyType<37>,
    typename T38 = detail::EmptyType<38>, typename T39 = detail::EmptyType<39>, typename T40 = detail::EmptyType<40>,
    typename T41 = detail::EmptyType<41>, typename T42 = detail::EmptyType<42>, typename T43 = detail::EmptyType<43>,
    typename T44 = detail::EmptyType<44>, typename T45 = detail::EmptyType<45>, typename T46 = detail::EmptyType<46>,
    typename T47 = detail::EmptyType<47>, typename T48 = detail::EmptyType<48>, typename T49 = detail::EmptyType<49>,
    typename T50 = detail::EmptyType<50>, typename T51 = detail::EmptyType<51>, typename T52 = detail::EmptyType<52>,
    typename T53 = detail::EmptyType<53>, typename T54 = detail::EmptyType<54>, typename T55 = detail::EmptyType<55>,
    typename T56 = detail::EmptyType<56>, typename T57 = detail::EmptyType<57>, typename T58 = detail::EmptyType<58>,
    typename T59 = detail::EmptyType<59>, typename T60 = detail::EmptyType<60>, typename T61 = detail::EmptyType<61>,
    typename T62 = detail::EmptyType<62>, typename T63 = detail::EmptyType<63>, typename T64 = detail::EmptyType<64>,
    typename T65 = detail::EmptyType<65>, typename T66 = detail::EmptyType<66>, typename T67 = detail::EmptyType<67>,
    typename T68 = detail::EmptyType<68>, typename T69 = detail::EmptyType<69>, typename T70 = detail::EmptyType<70>,
    typename T71 = detail::EmptyType<71>, typename T72 = detail::EmptyType<72>, typename T73 = detail::EmptyType<73>,
    typename T74 = detail::EmptyType<74>, typename T75 = detail::EmptyType<75>, typename T76 = detail::EmptyType<76>,
    typename T77 = detail::EmptyType<77>, typename T78 = detail::EmptyType<78>, typename T79 = detail::EmptyType<79>,
    typename T80 = detail::EmptyType<80>, typename T81 = detail::EmptyType<81>, typename T82 = detail::EmptyType<82>,
    typename T83 = detail::EmptyType<83>, typename T84 = detail::EmptyType<84>, typename T85 = detail::EmptyType<85>,
    typename T86 = detail::EmptyType<86>, typename T87 = detail::EmptyType<87>, typename T88 = detail::EmptyType<88>,
    typename T89 = detail::EmptyType<89>, typename T90 = detail::EmptyType<90>, typename T91 = detail::EmptyType<91>,
    typename T92 = detail::EmptyType<92>, typename T93 = detail::EmptyType<93>, typename T94 = detail::EmptyType<94>,
    typename T95 = detail::EmptyType<95>, typename T96 = detail::EmptyType<96>, typename T97 = detail::EmptyType<97>,
    typename T98 = detail::EmptyType<98>, typename T99 = detail::EmptyType<99>, typename T100 = detail::EmptyType<100>
>
class UniqueVariant
{
    // C++03 standard says (14.7.3/2):
    //     An explicit specialization shall be declared in the namespace of which the template is
    //     a member, or, for member templates, in the namespace of which the enclosing class or
    //     enclosing class template is a member. An explicit specialization of a member function,
    //     member class or static data member of a class template shall be declared in the namespace
    //     of which the class template is a member.
    // Thus, to avoid explicit specialization, implicit one is used. To achieve that non-type
    // template parameter is added (in this situation it is enum type).
    enum SingleValueEnum { DummyValue };
    template <typename Y, SingleValueEnum UNUSED> class TypeWrapper;

    // Specialization of type wrapper for types T1..T100.
    // This is the exact place where explicit specialization is not possible.
#define TYPE_WRAPPER_SPEC(N)                                            \
    template <SingleValueEnum UNUSED>                                   \
    class TypeWrapper<T##N, UNUSED> : public detail::TypeWrapperBase    \
    {                                                                   \
    public:                                                             \
        static const unsigned TAG = N##u;                               \
        T##N value;                                                     \
        TypeWrapper<T##N, UNUSED>() : detail::TypeWrapperBase(TAG) { }  \
    };

#define TYPE_WRAPPER_SPECS(W1, W2, W3, W4, W5, W6, W7, W8, W9, W10)     \
    TYPE_WRAPPER_SPEC(W1) TYPE_WRAPPER_SPEC(W2) TYPE_WRAPPER_SPEC(W3)   \
    TYPE_WRAPPER_SPEC(W4) TYPE_WRAPPER_SPEC(W5) TYPE_WRAPPER_SPEC(W6)   \
    TYPE_WRAPPER_SPEC(W7) TYPE_WRAPPER_SPEC(W8) TYPE_WRAPPER_SPEC(W9)   \
    TYPE_WRAPPER_SPEC(W10)                                              \

    TYPE_WRAPPER_SPECS(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
    TYPE_WRAPPER_SPECS(11, 12, 13, 14, 15, 16, 17, 18, 19, 20)
    TYPE_WRAPPER_SPECS(21, 22, 23, 24, 25, 26, 27, 28, 29, 30)
    TYPE_WRAPPER_SPECS(31, 32, 33, 34, 35, 36, 37, 38, 39, 40)
    TYPE_WRAPPER_SPECS(41, 42, 43, 44, 45, 46, 47, 48, 49, 50)
    TYPE_WRAPPER_SPECS(51, 52, 53, 54, 55, 56, 57, 58, 59, 60)
    TYPE_WRAPPER_SPECS(61, 62, 63, 64, 65, 66, 67, 68, 69, 70)
    TYPE_WRAPPER_SPECS(71, 72, 73, 74, 75, 76, 77, 78, 79, 80)
    TYPE_WRAPPER_SPECS(81, 82, 83, 84, 85, 86, 87, 88, 89, 90)
    TYPE_WRAPPER_SPECS(91, 92, 93, 94, 95, 96, 97, 98, 99, 100)

#undef TYPE_WRAPPER_SPECS
#undef TYPE_WRAPPER_SPEC

    // Compile-time class to find greater type of two (using sizeof()).
    template <class A, class B> class GetGreaterOfSizeOfs {
    public:
        static const unsigned value = detail::StaticMax<sizeof(A), sizeof(B)>::value;
    };

    // Similar to above, but this compares a type (using sizeof()) and an unsigned number.
    template <unsigned A, class B> class GetGreaterOfUnsignedAndSizeOf {
    public:
        static const unsigned value = detail::StaticMax<A, sizeof(B)>::value;
    };

#define COMPILE_TIME_MAX_10(N1, N2, N3, N4, N5, N6, N7, N8, N9, N10)        \
    GetGreaterOfUnsignedAndSizeOf<                                          \
        GetGreaterOfUnsignedAndSizeOf<                                      \
            GetGreaterOfUnsignedAndSizeOf<                                  \
                GetGreaterOfUnsignedAndSizeOf<                              \
                    GetGreaterOfUnsignedAndSizeOf<                          \
                        GetGreaterOfUnsignedAndSizeOf<                      \
                            GetGreaterOfUnsignedAndSizeOf<                  \
                                GetGreaterOfUnsignedAndSizeOf<              \
                                    GetGreaterOfSizeOfs<                    \
                                        TypeWrapper<T##N1, DummyValue>,     \
                                        TypeWrapper<T##N2, DummyValue>      \
                                    >::value,                               \
                                    TypeWrapper<T##N3, DummyValue>          \
                                >::value,                                   \
                                TypeWrapper<T##N4, DummyValue>              \
                            >::value,                                       \
                            TypeWrapper<T##N5, DummyValue>                  \
                        >::value,                                           \
                        TypeWrapper<T##N6, DummyValue>                      \
                    >::value,                                               \
                    TypeWrapper<T##N7, DummyValue>                          \
                >::value,                                                   \
                TypeWrapper<T##N8, DummyValue>                              \
            >::value,                                                       \
            TypeWrapper<T##N9, DummyValue>                                  \
        >::value,                                                           \
        TypeWrapper<T##N10, DummyValue>                                     \
    >::value

    // Compute the bigger type out of T1..T100.
    static const unsigned BIGGEST_STRUCT_SIZE =
        detail::StaticMax<
            detail::StaticMax<
                detail::StaticMax<
                    detail::StaticMax<
                        detail::StaticMax<
                            detail::StaticMax<
                                detail::StaticMax<
                                    detail::StaticMax<
                                        detail::StaticMax<
                                            COMPILE_TIME_MAX_10(1, 2, 3, 4, 5, 6, 7, 8, 9, 10),
                                            COMPILE_TIME_MAX_10(11, 12, 13, 14, 15, 16, 17, 18, 19, 20)
                                        >::value,
                                        COMPILE_TIME_MAX_10(21, 22, 23, 24, 25, 26, 27, 28, 29, 30)
                                    >::value,
                                    COMPILE_TIME_MAX_10(31, 32, 33, 34, 35, 36, 37, 38, 39, 40)
                                >::value,
                                COMPILE_TIME_MAX_10(41, 42, 43, 44, 45, 46, 47, 48, 49, 50)
                            >::value,
                            COMPILE_TIME_MAX_10(51, 52, 53, 54, 55, 56, 57, 58, 59, 60)
                        >::value,
                        COMPILE_TIME_MAX_10(61, 62, 63, 64, 65, 66, 67, 68, 69, 70)
                    >::value,
                    COMPILE_TIME_MAX_10(71, 72, 73, 74, 75, 76, 77, 78, 79, 80)
                >::value,
                COMPILE_TIME_MAX_10(81, 82, 83, 84, 85, 86, 87, 88, 89, 90)
            >::value,
            COMPILE_TIME_MAX_10(91, 92, 93, 94, 95, 96, 97, 98, 99, 100)
        >::value;

#undef COMPILE_TIME_MAX_10

public:
    UniqueVariant<
        T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24,
        T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46,
        T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57, T58, T59, T60, T61, T62, T63, T64, T65, T66, T67, T68,
        T69, T70, T71, T72, T73, T74, T75, T76, T77, T78, T79, T80, T81, T82, T83, T84, T85, T86, T87, T88, T89, T90,
        T91, T92, T93, T94, T95, T96, T97, T98, T99, T100>() {
        m_ptr = static_cast<detail::TypeWrapperBase*> (::operator new (BIGGEST_STRUCT_SIZE));
        m_isVariantInitialized = false;
    }

    template <typename U> U & acquire() {
        if (!m_isVariantInitialized) {
            m_ptr = static_cast<detail::TypeWrapperBase*>(new (m_ptr) TypeWrapper<U, m_unused>);
            m_isVariantInitialized = true;
        }
        else if (m_ptr->getTagValue() != TypeWrapper<U, m_unused>::TAG) {
            m_ptr->~TypeWrapperBase();
            m_ptr = static_cast<detail::TypeWrapperBase*>(new (m_ptr) TypeWrapper<U, m_unused>);
        }
        return (static_cast<TypeWrapper<U, m_unused>*>(m_ptr))->value;
    }

    ~UniqueVariant() {
        if (m_isVariantInitialized)
            delete m_ptr;
        else
            ::operator delete (m_ptr);
    }

private:
    bool m_isVariantInitialized;
    detail::TypeWrapperBase * m_ptr;
    static const SingleValueEnum m_unused = DummyValue;
};

} // namespace stilzdev

